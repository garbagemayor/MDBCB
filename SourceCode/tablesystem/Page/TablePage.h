#ifndef TABLE_PAGE_H
#define TABLE_PAGE_H

#include "../../filesystem/OneFileManager.h"
#include "TablePageHeader.h"
#include "TablePageFooter.h"

#include <cstring>

/**
 *  数据表的一页，到处都在调用
 *  
 */
class TablePage {
    
private:
    ///基本信息
    //单文件管理器
    OneFileManager * oneFileManager;
    //页编号
    int pageId;
    //是否脏（与缓存页管理器中的页面相比）
    bool dirtyFlag;
    
private:
    ///读取的信息
    //页内数据
    ByteBufType pageData;
    //页头
    TablePageHeader * header;
    //页尾
    TablePageFooter * footer;
    
public:
    /*
     *  @构造函数
     *  @参数oneFileManager_:单文件管理器
     *  功能:新建一个空的页面，并给他们设置页头页脚
     */
    TablePage(OneFileManager * oneFileManager_) {
        oneFileManager = oneFileManager_;
        header = NULL;
        footer = NULL;
        dirtyFlag = true;
        //新建一个页面
        pageData = oneFileManager -> getNewPage(pageId);
        //设置页头的信息
        header = new TablePageHeader();
        header -> pageId = pageId;
        header -> oneFileManager = oneFileManager;
        header -> pageData = pageData;
        header -> writeBackToBuffer();
        //设置页脚的信息
        footer = new TablePageFooter();
        footer -> pageId = pageId;
        footer -> oneFileManager = oneFileManager;
        footer -> pageData = pageData;
        footer -> writeBackToBuffer();
    }
    
    /*
     *  @构造函数
     *  @参数oneFileManager:单文件管理器
     *  @参数pageId:页编号
     *  功能:读取已有页面并抓取页头页脚信息，如果原本不存在这一页就报错
     */
    TablePage(OneFileManager * oneFileManager_, int pageId_) {
        oneFileManager = oneFileManager_;
        pageId = pageId_;
        //这一页是否存在
        if (pageId < 0 || pageId >= oneFileManager -> getPageCount()) {
            std::cout << "TablePage() error" << std::endl;
            return;
        }
        //读取这一页的页头页脚
        dirtyFlag = false;
        pageData = oneFileManager -> getPage(pageId);
        header = new TablePageHeader(oneFileManager, pageData);
        footer = new TablePageFooter(oneFileManager, pageData, header -> pageId, header -> slotCnt);
    }
    
    /*
     *  @析构函数
     *  功能:写回到文件并释放
     */
    ~TablePage() {
        if (header != NULL) {
            delete header;
        }
        if (footer != NULL) {
            delete footer;
        }
        writeBackToFile();
    }
    
public:
    ///基本get函数
    /*
     *  @函数名:getOneFileManager
     *  功能:获取单文件管理器的指针
     */
    OneFileManager * getOneFileManager() {
        return oneFileManager;
    }
    
    /*
     *  @函数名:getPageId
     *  功能:获取页编号
     */
    int getPageId() {
        return pageId;
    }
    
    /*
     *  @函数名:isDirty
     *  功能:返回是否脏
     */
    bool isDirty() {
        return dirtyFlag;
    }
    
    /*
     *  @函数名:getPageHeader
     *  功能:返回页头类的指针
     */
    TablePageHeader * getPageHeader() {
        return header;
    }
    
    /*
     *  @函数名:getPageFooter
     *  功能:返回页脚类的指针
     */
    TablePageFooter * getPageFooter() {
        return footer;
    }
    
    /*
     *  @函数名:getSlot
     *  @参数slotId:槽的编号
     *  功能:获取一个原有槽的数据
     *  返回值:成功返回数据指针，失败报错并返回NULL
     */
    ByteBufType getSlot(int slotId) {
        if (slotId < 0 || slotId >= header -> slotCnt) {
            std::cout << "TablePage::getSlot(" << slotId << ") error" << std::endl;
            return NULL;
        }
        int offset = footer -> slotOffset[slotId];
        return pageData + offset;
    }
    
public:
    ///基本set函数
    /*
     *  @函数名:markDirty
     *  功能:标记脏
     */
    void markDirty() {
        dirtyFlag = true;
    }
    

public:
    ///普通函数
    /*
     *  @函数名:writeBackToFile
     *  功能:如果脏，就写回到文件中去
     */
    void writeBackToFile() {
        if (header -> isDirty()) {
            dirtyFlag = true;
            header -> writeBackToBuffer();
        }
        if (footer -> isDirty()) {
            dirtyFlag = true;
            footer -> writeBackToBuffer();
        }
        if (dirtyFlag) {
            oneFileManager -> markDirty(pageId);
        }
        oneFileManager -> writeBack(pageId);
        dirtyFlag = false;
    }
    
    /*
     *  @函数名:createSlot
     *  @参数slotLen:待写入的数据长度
     *  功能:新建一个固定大小的槽，并返回槽编号，失败返回-1
     */
    int createSlot(int slotLen) {
        if (header -> freeCnt < slotLen + 2) {
            std::cout << "TablePage::createSlot(" << slotLen << ") error" << std::endl;
            return -1;
        }
        dirtyFlag = true;
        footer -> markDirty();
        footer -> slotCnt ++;
        footer -> slotOffset.push_back(header -> freeData);
        footer -> writeBackToBuffer();
        header -> markDirty();
        header -> slotCnt ++;
        header -> freeData += slotLen;
        header -> freeCnt -= slotLen + 2;
        header -> writeBackToBuffer();
        return header -> slotCnt - 1;
    }
};

#endif // TABLE_PAGE_H
