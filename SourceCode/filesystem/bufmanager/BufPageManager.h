#ifndef BUF_PAGE_MANAGER_H_
#define BUF_PAGE_MANAGER_H_

#include "../utils/pagedef.h"
#include "../fileio/FileManager.h"

#include <utility>
#include <vector>
#include <map>

/**
 *  我的BufPageManager，更靠谱
 */
class BufPageManager {
    
public:
    FileManager * fileManager;
    
private:
    //index流水发放
    int indexNow;
    //从(fileId, pageId)到index的映射关系
    std::map < std::pair < int, int >, int > indexMap;
    //从index到fileId的映射关系
    std::map < int, int > fileIdMap;
    //从index到pageId的映射关系
    std::map < int, int > pageIdMap;
    //从index到dirtyFlag的映射关系
    std::map < int, bool> dirtyMap;
    //从index到buffer的映射关系
    std::map < int, BufType> bufMap;
    
public:
    /*
     *  @构造函数
     */
    BufPageManager(FileManager * fm) {
        fileManager = fm;
        indexNow = 0;
    }
    
    /*
     *  @析构函数
     */
    ~BufPageManager() {
        for (std::map < int, BufType > :: iterator ite = bufMap.begin(); ite != bufMap.end(); ite ++) {
            delete ite -> second;
        }
        bufMap.clear();
    }
    
public:
    ///普通函数
    /*
     *  @函数名:getIndex
     *  功能:用fileId和pageId获取index
     */
    int getIndex(int fileId, int pageId) {
        /*
        std::cout << "BufPageManager.getIndex(" << fileId << ", " << pageId << ") " << std::endl;
        for (std::map < std::pair < int, int >, int > :: iterator ite = indexMap.begin(); ite != indexMap.end(); ite ++) {
            std::cout << "    (" << ite -> first.first << ", " << ite -> first.second << ") -> " << ite -> second << std::endl;
        }
        std::cout << std::endl;
        */
        if (indexMap.find(make_pair(fileId, pageId)) == indexMap.end()) {
            return -1;
        } else {
            return indexMap[make_pair(fileId, pageId)];
        }
    }
    
    /* 
     *  @函数名:fetchPage
     *  功能:对于缓存里面没有的页面，把它加载到缓存里面来
     */
    BufType fetchPage(int fileId, int pageId, int & index) {
        //发放index
        index = ++ indexNow;
        //std::cout << "BufPageManager.fetchPage() fileId = " << fileId << " pageId = " << pageId << " index = " << index << std::endl;
        indexMap[make_pair(fileId, pageId)] = index;
        /*
        std::cout << "BufPageManager.getIndex(" << fileId << ", " << pageId << ") " << std::endl;
        for (std::map < std::pair < int, int >, int > :: iterator ite = indexMap.begin(); ite != indexMap.end(); ite ++) {
            std::cout << "    (" << ite -> first.first << ", " << ite -> first.second << ") -> " << ite -> second << std::endl;
        }
        std::cout << std::endl;
        */
        fileIdMap[index] = fileId;
        pageIdMap[index] = pageId;
        dirtyMap[index] = false;
        //开内存，不管能不能读都读一下文件，反正不会炸
        BufType buf = new uint [PAGE_SIZE >> 2];
        fileManager -> readPage(fileId, pageId, (BufType) buf, 0);
        bufMap[index] = buf;
    }
    
    /*
     *  @函数名:getPage
     *  功能:找到缓存页面，找不到就再新开一个
     */
    BufType getPage(int fileId, int pageId, int & index) {
        index = getIndex(fileId, pageId);
        if (index == -1){
            return fetchPage(fileId, pageId, index);
        } else {
            return bufMap[index];
        }
    }
    
	/*
	 * @函数名access
	 * 功能:标记index代表的缓存页面被访问过，为替换算法提供信息
	 */
	void access(int index) {
	}
	
    /*
     *  @函数名:markDirty
     *  功能:标记脏
     */
    void markDirty(int index) {
        if (dirtyMap.find(index) != dirtyMap.end()) {
            dirtyMap[index] = true;
            access(index);
        }
    }
    
	/*
	 * @函数名release
	 * 功能:将index代表的缓存页面归还给缓存管理器，在归还前，缓存页面中的数据不标记写回
	 */
	void release(int index) {
	    if (dirtyMap.find(index) != dirtyMap.end()) {
            indexMap.erase(make_pair(fileIdMap[index], pageIdMap[index]));
            fileIdMap.erase(index);
            pageIdMap.erase(index);
            dirtyMap.erase(index);
            delete bufMap[index];
            bufMap.erase(index);
	    }
	}
	
	/*
	 * @函数名writeBack
	 * 功能:将index代表的缓存页面归还给缓存管理器，在归还前，缓存页面中的数据需要根据脏页标记决定是否写到对应的文件页面中
	 */
	void writeBack(int index) {
	    if (dirtyMap.find(index) != dirtyMap.end()) {
            if (dirtyMap[index]) {
                fileManager -> writePage(fileIdMap[index], pageIdMap[index], (BufType) bufMap[index], 0);
                dirtyMap[index] = false;
            }
	    }
	}
};

#endif // BUF_PAGE_MANAGER_H_
