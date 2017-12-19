#ifndef ONE_FILE_MANAGER_H_
#define ONE_FILE_MANAGER_H_

#include "fileio/FileManager.h"
#include "bufmanager/BufPageManager.h"
#include "ByteBufBase.h"

#include <string>
#include <map>

/**
 *  单文件管理器。
 *  原有的文件管理器和缓存页管理器都没有记录某个文件内一共有多少页，以及一些其他信息，因此需要封装。
 *  调用这个类的时候，对页的操作都使用页编号。
 *  每次调用bufPageManager的hash去获取页在缓存管理器里面的编号非常慢，于是在这个类里面稍微优化了一下。
 */
class OneFileManager {
    
private:
    //文件名
    std::string fileName;
    //文件编号
    int fileId;
    //页数统计
    int pageCnt;
    //缓存页管理器
    BufPageManager * bufPageManager;
    
protected:
    //页面在缓存页管理器里面的编号，要与hash里面的同步添加和删除
    std::map<int, int> indexMap;
    
public:
    /*
     *  @构造函数
     *  功能:创建一个单文件管理器，指定文件名
     */
    OneFileManager(BufPageManager * bufPageManager_, std::string fileName_, bool isNewFile = false) {
        fileName = fileName_;
        bufPageManager = bufPageManager_;
        if (isNewFile) {
            bufPageManager -> fileManager -> createFile(fileName.c_str());
            pageCnt = 0;
        } else {
            pageCnt = bufPageManager -> fileManager -> getFileSize(fileName.c_str()) / PAGE_SIZE;
        }
        if (bufPageManager -> fileManager -> openFile(fileName.c_str(), fileId) == false) {
            std::cout << "OneFileManager(bufPageManager, " << fileName_ << ", " << isNewFile << ") error" << std::endl;
            return;
        }
    }
    
    /*
     *  @析构函数
     *  功能:把打开过的页全都关掉
     */
    ~OneFileManager() {
        close();
    }
public:
    ///基本get函数
    /*
     *  @函数名:getPageCnt
     *  功能:返回这个文件的页数
     */
    int getPageCnt() {
        return pageCnt;
    }
    
public:
    ///普通函数（对文件内的页进行操作的函数）
    /*
     *  @函数名:getPageCount
     *  功能:获取当前文件共有多少页
     */
    int getPageCount() {
        return pageCnt;
    }
    
    /*
     *  @函数名:getPage
     *  功能:根据页编号，返回页数据
     */
    ByteBufType getPage(int pageId) {
        int index;
        BufType data = bufPageManager -> getPage(fileId, pageId, index);
        indexMap[pageId] = index;
        return (ByteBufType) data;
    }
    
    /*
     *  @函数名:getNewPage
     *  功能:创建一个新的页，返回页数据，并同时获取页编号
     */
    ByteBufType getNewPage(int & pageId) {
        pageId = pageCnt;
        pageCnt ++;
        int index;
        BufType data = bufPageManager -> getPage(fileId, pageId, index);
        indexMap[pageId] = index;
        return (ByteBufType) data;
    }
    
    /*
     *  @函数名getNewPage
     *  功能:创建一个新的页，返回页数据
     */
    ByteBufType getNewPage() {
        int pageId;
        return getNewPage(pageId);
    }
    
    /*
     *  @函数名:access
     *  功能:由页编号标记一个页被访问过，让替换算法尽量不要替换它
     */
    void access(int pageId) {
        int index = getPageIndex(pageId, false);
        if (index == -1) {
            std::cout << "OneFileManager.access() error" << std::endl;
            return;
        }
        bufPageManager -> access(index);
    }
    
    /*
     *  @函数名:markDirty
     *  功能:标记脏页
     */
    void markDirty(int pageId) {
        int index = getPageIndex(pageId, false);
        if (index == -1) {
            std::cout << "OneFileManager.markDirty() error" << std::endl;
            return;
        }
        bufPageManager -> markDirty(index);
    }
    
    /*
     *  @函数名:release
     *  功能:由页编号释放一个页面，这个页面必须是干净的
     */
    void release(int pageId) {
        int index = getPageIndex(pageId, true);
        if (index == -1) {
            std::cout << "OneFileManagerwriteBack.release() error" << std::endl;
            return;
        }
        bufPageManager -> release(index);
    }
    
    /*
     *  @函数名:writeBack
     *  功能:由页编号来写回一个修改完成的页面，自动选择是直接释放还是写回再释放
     */
    void writeBack(int pageId) {
        int index = getPageIndex(pageId, true);
        if (index == -1) {
            std::cout << "OneFileManager.writeBack() error" << std::endl;
            return;
        }
        bufPageManager -> writeBack(index);
    }
    
    /*
     *  @函数名:close
     *  功能:关闭这个文件，把打开的所有页都写回
     */
    void close() {
        for (std::map<int, int>::iterator ite = indexMap.begin(); ite != indexMap.end(); ite ++) {
            bufPageManager -> writeBack(ite -> first);
        }
        indexMap.clear();
    }
    
protected:
    ///其他函数
    /*
     *  @函数名:
     *  功能:由页编号获取缓存页管理器中的编号，并可以顺便删除
     */
    int getPageIndex(int pageId, bool eraseFlag) {
        int index = -1;
        if (indexMap.find(pageId) == indexMap.end()) {
            index = bufPageManager -> hash -> findIndex(fileId, pageId);
        } else {
            index = indexMap[pageId];
            if (eraseFlag) {
                indexMap.erase(pageId);
            }
        }
        return index;
    }
};


#endif // ONE_FILE_MANAGER_H_
