#ifndef BUF_PAGE_MANAGER_H_
#define BUF_PAGE_MANAGER_H_

#include "../utils/pagedef.h"
#include "../fileio/FileManager.h"

#include <utility>
#include <vector>
#include <map>

/**
 *  �ҵ�BufPageManager��������
 */
class BufPageManager {
    
public:
    FileManager * fileManager;
    
private:
    //index��ˮ����
    int indexNow;
    //��(fileId, pageId)��index��ӳ���ϵ
    std::map < std::pair < int, int >, int > indexMap;
    //��index��fileId��ӳ���ϵ
    std::map < int, int > fileIdMap;
    //��index��pageId��ӳ���ϵ
    std::map < int, int > pageIdMap;
    //��index��dirtyFlag��ӳ���ϵ
    std::map < int, bool> dirtyMap;
    //��index��buffer��ӳ���ϵ
    std::map < int, BufType> bufMap;
    
public:
    /*
     *  @���캯��
     */
    BufPageManager(FileManager * fm) {
        fileManager = fm;
        indexNow = 0;
    }
    
    /*
     *  @��������
     */
    ~BufPageManager() {
        for (std::map < int, BufType > :: iterator ite = bufMap.begin(); ite != bufMap.end(); ite ++) {
            delete ite -> second;
        }
        bufMap.clear();
    }
    
public:
    ///��ͨ����
    /*
     *  @������:getIndex
     *  ����:��fileId��pageId��ȡindex
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
     *  @������:fetchPage
     *  ����:���ڻ�������û�е�ҳ�棬�������ص�����������
     */
    BufType fetchPage(int fileId, int pageId, int & index) {
        //����index
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
        //���ڴ棬�����ܲ��ܶ�����һ���ļ�����������ը
        BufType buf = new uint [PAGE_SIZE >> 2];
        fileManager -> readPage(fileId, pageId, (BufType) buf, 0);
        bufMap[index] = buf;
    }
    
    /*
     *  @������:getPage
     *  ����:�ҵ�����ҳ�棬�Ҳ��������¿�һ��
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
	 * @������access
	 * ����:���index����Ļ���ҳ�汻���ʹ���Ϊ�滻�㷨�ṩ��Ϣ
	 */
	void access(int index) {
	}
	
    /*
     *  @������:markDirty
     *  ����:�����
     */
    void markDirty(int index) {
        if (dirtyMap.find(index) != dirtyMap.end()) {
            dirtyMap[index] = true;
            access(index);
        }
    }
    
	/*
	 * @������release
	 * ����:��index����Ļ���ҳ��黹��������������ڹ黹ǰ������ҳ���е����ݲ����д��
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
	 * @������writeBack
	 * ����:��index����Ļ���ҳ��黹��������������ڹ黹ǰ������ҳ���е�������Ҫ������ҳ��Ǿ����Ƿ�д����Ӧ���ļ�ҳ����
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
