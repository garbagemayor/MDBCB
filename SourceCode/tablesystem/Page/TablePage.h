#ifndef TABLE_PAGE_H
#define TABLE_PAGE_H

#include "../../filesystem/OneFileManager.h"
#include "TablePageHeader.h"
#include "TablePageFooter.h"

#include <cstring>

/**
 *  数据表的一页，由单个数据表类OneTableManager调用。
 *  
 */
class TablePage {
    
public:
    ///基本信息
    //单文件管理器
    OneFileManager * oneFileManager;
    //页编号
    int pageId;
    //是否脏（与缓存页管理器中的页面相比）
    bool isDirty;
    
public:
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
        isDirty = true;
        //新建一个页面
        int pageId;
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
        if (pageId < 0 || pageId >= oneFileManager -> pageCnt) {
            std::cout << "TablePage() error" << std::endl;
            return;
        }
        //读取这一页的页头页脚
        isDirty = false;
        pageData = oneFileManager -> getPage(pageId);
        header = new TablePageHeader(oneFileManager, pageData);
        footer = new TablePageFooter(oneFileManager, pageData, header -> pageId, header -> slotCnt);
    }
    
    /*
     *  @析构函数
     */
    ~TablePage() {
        writeBackToFile();
        if (header != NULL) {
            delete header;
        }
        if (footer != NULL) {
            delete footer;
        }
    }

public:
    ///各种功能的函数
    /*
     *  @函数名:writeBackToFile
     *  功能:如果脏，就写回到文件中去
     */
    void writeBackToFile() {
        if (isDirty) {
            oneFileManager -> markDirty(pageId);
        }
        oneFileManager -> writeBack(pageId);
        isDirty = false;
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
    
    /*
     *  @函数名:addSlot
     *  @参数slotLen:待写入的数据长度
     *  @参数slotData:待写入的数据内容，必须保证开头2字节等于slotLen
     *  功能:新建一个槽，把数据写进去。
     *  返回值:成功范围槽编号，失败报错并返回-1
     */
    int addSlot(int slotLen, ByteBufType slotData) {
        if (header -> freeCnt < slotLen + 2) {
            std::cout << "TablePage::addNewSlot(" << slotLen << ", <" << (int) slotData << ">) error" << std::endl;
            return -1;
        }
        isDirty = true;
        ByteBufType freeStart = pageData + header -> freeData;
        memcpy(freeStart, slotData, slotLen);
        footer -> isDirty = true;
        footer -> slotCnt ++;
        footer -> slotOffset.push_back(header -> freeData);
        footer -> writeBackToBuffer();
        header -> isDirty = true;
        header -> slotCnt ++;
        header -> freeData += slotLen;
        header -> freeCnt -= slotLen + 2;
        header -> writeBackToBuffer();
    }
    
    ///TODO 其他的各种功能的函数
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif // TABLE_PAGE_H
