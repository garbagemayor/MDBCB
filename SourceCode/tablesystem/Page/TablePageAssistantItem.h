#ifndef TABLE_PAGE_ASSISTANT_ITEM_H
#define TABLE_PAGE_ASSISTANT_ITEM_H

#include "../../filesystem/ByteBufBase.h"
#include "../../filesystem/OneFileManager.h"
#include "TablePage.h"

/**
 *  表页助手的每一页，方便表页助手使用
 *  存储格式：slotLen(2B) assiOffset(4B) ...(assiSize*2B)
 */
class TablePageAssistantItem {
    
private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //这一页的页管理器
    TablePage * curPage;
    //页码偏移量
    int assiOffset;
    //容量，是长度的一半
    int assiSize;
    //偏移量存储的数据内容
    ByteBufType assiData;
    
public:
    /*
     *  @构造函数
     *  @参数oneFileManager:单文件管理器
     *  功能:创建第一个助手页，占据表的第0页的所有剩余空间
    TablePageAssistantItem(TablePage * curPage_) {
        //空指针报错
        if (curPage_ == NULL) {
            std::cout << "TablePageAssistantItem(NULL) error 1" << std::endl;
            return;
        }
        //基本信息们
        oneFileManager = curPage -> getOneFileManager();
        curPage = curPage_;
        curPage -> markDirty();
        assiOffset = 0;
        int assiSlotLen = curPage -> getPageHeader() -> getFreeCnt() - 2;
        assiSize = (assiSlotLen - 6) / 2;
        //页中的事情
        int assiSlotId = curPage -> createSlot(assiSlotLen);
        assiData = curPage -> getSlot(assiSlotId);
        memset(assiData, 0, sizeof(Byte) * assiSlotLen);
        ByteBufType assiData_ = assiData;
        writeNumberToByte(assiData_, 2, assiSlotLen);
        writeNumberToByte(assiData_, 4, assiOffset);
    }
     */
    
    /*
     *  @构造函数
     *  @lastAssistant:上一个助手页
     *  功能:创建下一个助手页
     */
    TablePageAssistantItem(TablePageAssistantItem * lastAssistant) {
        //空指针报错
        if (lastAssistant == NULL) {
            std::cout << "TablePageAssistantItem(NULL) error 2" << std::endl;
            return;
        }
        //基本信息，从上一个助手页计算出来，并把两页在页头连接起来
        oneFileManager = lastAssistant -> oneFileManager;
        curPage = new TablePage(oneFileManager);
        curPage -> getPageHeader() -> setObjId(2);
        lastAssistant -> curPage -> markDirty();
        curPage -> markDirty();
        lastAssistant -> curPage -> getPageHeader() -> setNextPageId(curPage -> getPageId());
        curPage -> getPageHeader() -> setPrevPageId(lastAssistant -> curPage -> getPageId());
        assiOffset = lastAssistant -> assiOffset + lastAssistant -> assiSize;
        int assiSlotLen = curPage -> getPageHeader() -> getFreeCnt() - 2;
        assiSize = (assiSlotLen - 6) / 2;
        //页中的事情
        int assiSlotId = curPage -> createSlot(assiSlotLen);
        assiData = curPage -> getSlot(assiSlotId);
        memset(assiData, 0, sizeof(Byte) * assiSlotLen);
        ByteBufType assiData_ = assiData;
        writeNumberToByte(assiData_, 2, assiSlotLen);
        writeNumberToByte(assiData_, 4, assiOffset);
    }
    
    /*
     *  @构造函数
     *  @参数oneFileManager_:单文件管理器
     *  @参数pageId_:页编号
     *  功能:创建第0页的助手页，或者读取第pageId_页的助手页
     */
    TablePageAssistantItem(OneFileManager * oneFileManager_, int pageId_) {
        //空指针报错
        if (oneFileManager_ == NULL) {
            std::cout << "TablePageAssistantItem(NULL) error 3" << std::endl;
            return;
        }
        //基本信息，从上一个助手页计算出来，并把两页在页头连接起来
        oneFileManager = oneFileManager_;
        curPage = new TablePage(oneFileManager, pageId_);
        curPage -> getPageHeader() -> setObjId(2);
        if (pageId_ == 0 && curPage -> getPageHeader() -> getFreeCnt() > 6) {
            //第0页没有建立过表页助手，就在第0页新建助手
            curPage -> markDirty();
            assiOffset = 0;
            int assiSlotLen = curPage -> getPageHeader() -> getFreeCnt() - 2;
            assiSize = (assiSlotLen - 6) / 2;
            int assiSlotId = curPage -> createSlot(assiSlotLen);
            assiData = curPage -> getSlot(assiSlotId);
            memset(assiData, 0, sizeof(Byte) * assiSlotLen);
            ByteBufType assiData_ = assiData;
            writeNumberToByte(assiData_, 2, assiSlotLen);
            writeNumberToByte(assiData_, 4, assiOffset);
        } else {
            //这一页已经建立过表页助手，就读取助手
            int assiSlotId = pageId_ == 0 ? 1 : 0;
            assiData = curPage -> getSlot(assiSlotId);
            ByteBufType assiData_ = assiData;
            int assiSlotLen = readByteToNumber(assiData_, 2);
            assiOffset = readByteToNumber(assiData_, 4);
            assiSize = (assiSlotLen - 6) / 2;
        }
    }
    
    ~TablePageAssistantItem() {
        delete curPage;
    }
    
public:
    ///基本get函数
    /*
     *  @函数名:getPageId
     *  功能:返回这个助手所在的页编号
     */
    int getPageId() {
        return curPage -> getPageId();
    }
    
    /*
     *  @函数名:getAssiBegin
     *  功能:返回这个助手管理的起始页编号
     */
    int getAssiBegin() {
        return assiOffset;
    }
    
    /*
     *  @函数名:getAssiEnd
     *  功能:返回这个助手管理的最后一页的下一页编号
     */
    int getAssiEnd() {
        return assiOffset + assiSize;
    }
    
    /*
     *  @函数名:getFreeCnt
     *  @参数pageId:查询的页编号
     *  功能:查询一页的空闲空间，查不到就报错并返回-1
     */
    int getFreeCnt(int pageId) {
        //查不到报错
        if (pageId < assiOffset || assiOffset + assiSize <= pageId) {
            std::cout << "TablePageAssistantItem.getFreeCnt(" << pageId << ") error" << std::endl;
            return -1;
        }
        //查询
        ByteBufType tmpBuf = assiData + 6 + (pageId - assiOffset) * 2;
        int tmpCnt = readByteToNumber(tmpBuf, 2);
        return tmpCnt;
    }
    
    /*
     *  @函数名:getNextPageId
     *  功能:查询下一个助手的页编号
     */
    int getNextPageId() {
        return curPage -> getPageHeader() -> getNextPageId(); 
    }
    
public:
    ///基本set函数
    /*
     *  @函数名:setFreeCnt
     *  @参数pageId:修改的页编号
     *  @参数pageFreeCnt:修改后的空闲空间
     *  功能:修改一页的空闲空间，不能修改就报错，不检查修改后的值
     */
    void setFreeCnt(int pageId, int pageFreeCnt) {
        //查不到报错
        if (pageId < assiOffset || assiOffset + assiSize <= pageId) {
            std::cout << "TablePageAssistantItem.setFreeCnt(" << pageId << ", " << pageFreeCnt << ") error" << std::endl;
            return ;
        }
        //修改
        curPage -> markDirty();
        ByteBufType tmpBuf = assiData + 6 + (pageId - assiOffset) * 2;
        writeNumberToByte(tmpBuf, 2, pageFreeCnt);
    }
    
    friend class TablePageAssistant;
};

#endif // TABLE_PAGE_ASSISTANT_ITEM_H
