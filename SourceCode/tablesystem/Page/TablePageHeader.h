#ifndef TABLE_PAGE_HEADER_H_
#define TABLE_PAGE_HEADER_H_

#include "../../filesystem/OneFileManager.h"
#include <iostream>

/**
 *  页头类，只能由页类TablePage来调用。
 *  
 */
class TablePageHeader {
    
private:
    //页头大小，单位字节
    static const int SIZE = PAGE_HEADER_SIZE;
    
private:
    ///基本信息
    //单文件管理器
    OneFileManager * oneFileManager;
    //这一页完整的数据内容
    ByteBufType pageData;
    //是否脏（与缓存页管理器中的页面相比）
    bool dirtyFlag;
    
private:
    ///页头内存储的信息
    //[0]: 这一页在当前文件中的页号
    int pageId;
    //[1]: 如果这一页处于一个页链中，就是上一页的页号
    int nextPageId;
    //[2]: 如果这一页处于一个页链中，就是下一页的页号
    int prevPageId;
    //[3]: 该页所属对象的ID（表页1，表页助手2，B+树索引3，Hash索引4）
    int objId;
    //[4]: 用于该页变化和更新的日志序列号（即LSN）值（不知道是什么）
    int lsn;
    //[5]: 该也上槽（行）的总数
    int slotCnt;
    //[6]: 该页在索引中的级别（对于叶级别的来说该值总是0）
    int level;
    //[7]: 该页的索引ID（对于数据页来说该值总是0）
    int indexId;
    //[8]: 该页上第一个空闲空间的字节偏移量
    int freeData;
    //[9]: 行的固定长度部分的字节数
    int pminlen;
    //[10]: 该页上空闲字节的数目
    int freeCnt;
    //[11]: 由所有事务保留的字节数
    int reservedCnt;
    //[12]: 由最近启动的事物保留的字节数
    int xactreserved;
    //[13]: 每个扇区1位，用于检测使该页分裂的写
    int tornBits;
    //[14]: 一个两字节的位图，包含了有关该页的额外信息
    int flagBits;
    
public:
    /*
	 *  @构造函数
	 *  @参数pageId_:这一页的编号（默认0），也可以创建后再来赋值
	 *  功能:给一个新的页新建一个空的页头，创建后必须手动给oneFileManager和pageData赋值
     */
    TablePageHeader(int pageId_ = 0) {
        //基本信息
        oneFileManager = NULL;
        pageData = NULL;
        dirtyFlag = true;
        //页头内的信息
        pageId = pageId_;
        nextPageId = -1;
        prevPageId = -1;
        objId = 0;
        lsn = 0;
        slotCnt = 0;
        level = 0;
        indexId = 0;
        freeData = SIZE;
        pminlen = 0;
        freeCnt = PAGE_SIZE - SIZE - 0;
        reservedCnt = 0;
        xactreserved = 0;
        tornBits = 0;
        flagBits = 0;
    }
    
    /*
	 *  @构造函数
	 *  @参数oneFileManager_:单文件管理器
	 *  @参数pageData_:该页的全部数据的指针，BufType类型
	 *  功能:读取已有页的页头
     */
    TablePageHeader(OneFileManager * oneFileManager_, ByteBufType pageData_) {
        //基本信息
        oneFileManager = oneFileManager_;
        pageData = pageData_;
        dirtyFlag = false;
        //页头内的信息
        pageId = ((BufType) pageData) [0];
        nextPageId = ((BufType) pageData) [1];
        prevPageId = ((BufType) pageData) [2];
        objId = ((BufType) pageData) [3];
        lsn = ((BufType) pageData) [4];
        slotCnt = ((BufType) pageData) [5];
        level = ((BufType) pageData) [6];
        indexId = ((BufType) pageData) [7];
        freeData = ((BufType) pageData) [8];
        pminlen = ((BufType) pageData) [9];
        freeCnt = ((BufType) pageData) [10];
        reservedCnt = ((BufType) pageData) [11];
        xactreserved = ((BufType) pageData) [12];
        tornBits = ((BufType) pageData) [13];
        flagBits = ((BufType) pageData) [14];
    }

    /*
	 * @析构函数
	 * 功能:如果页头信息有修改，就把信息重新写回去
     */
    ~TablePageHeader() {
        writeBackToBuffer();
    }

public:
    ///基本get函数
    /*
     *  @函数名:getNextPageId
     *  功能:返回下一页的页编号
     */
    int getNextPageId() {
        return nextPageId;
    }
    
    /*
     *  @函数名:getPrevPageId
     *  功能:返回上一页的页编号
     */
    int getPrevPageId() {
        return prevPageId;
    }
    
    /*
     *  @函数名:getObjId
     *  功能:返回对象标识符
     */
    int getObjId() {
        return objId;
    }
    
    /*
     *  @函数名:getSlotCnt
     *  功能:获取这一页已有的槽数量
     */
    int getSlotCnt() {
        return slotCnt;
    }
    
    /*
     *  @函数名:getLevel
     *  功能:获取这一页在索引中的级别
     */
    int getLevel() {
        return level;
    }
    
    /*
     *  @函数名:getFreeData
     *  功能:获取空闲位置的起始的偏移量
     */
    int getFreeData() {
        return freeData;
    }
    
    /*
     *  @函数名:getFreeCnt
     *  功能:获取空闲字节数
     */
    int getFreeCnt() {
        return freeCnt;
    }
    
    /*
     *  @函数名:isDirty
     *  功能:返回是否脏
     */
    bool isDirty() {
        return dirtyFlag;
    }
    
public:
    ///基本set函数
    /*
     *  @函数名:setOneFileManager
     *  功能:设置单文件管理器
     */
    void setOneFileManager(OneFileManager * oneFileManager_) {
        dirtyFlag = true;
        oneFileManager = oneFileManager_;
    }
    
    /*
     *  @函数名:setPageData
     *  功能:设置页数据指针
     */
    void setPageData(ByteBufType pageData_) {
        dirtyFlag = true;
        pageData = pageData_;
    }
    
    /*
     *  @函数名:setNextPageId
     *  功能:设置下一页的编号
     */
    void setNextPageId(int nextPageId_) {
        dirtyFlag = true;
        nextPageId = nextPageId_;
    }
    
    /*
     *  @函数名:setPrevPageId
     *  功能:设置上一页的编号
     */
    void setPrevPageId(int prevPageId_) {
        dirtyFlag = true;
        prevPageId = prevPageId_;
    }
    
    /*
     *  @函数名:setObjId
     *  功能:设置对象标识符
     */
    void setObjId(int objId_) {
        dirtyFlag = true;
        objId = objId_;
    }
    
    /*
     *  @函数名:setSlotCnt
     *  功能:设置这一页的槽数量
     */
    void setSlotCnt(int slotCnt_) {
        dirtyFlag = true;
        slotCnt = slotCnt_;
    }
    
    /*
     *  @函数名:setLevel
     *  功能:设置这一页在索引中的级别
     */
    void setLevel(int level_) {
        dirtyFlag = true;
        level = level_;
    }
    
    /*
     *  @函数名:setIndexId
     *  功能:设置这一页的索引类型
     */
    void setIndexId(int indexId_) {
        dirtyFlag = true;
        indexId = indexId_;
    }
    
    /*
     *  @函数名:setFreeData
     *  功能:设置空闲位置的起始的偏移量
     */
    void setFreeData(int freeData_) {
        dirtyFlag = true;
        freeData = freeData_;
    }
    
    /*
     *  @函数名:setFreeCnt
     *  功能:设置空闲字节数的编号
     */
    void setFreeCnt(int freeCnt_) {
        dirtyFlag = true;
        freeCnt = freeCnt_;
    }
    
    /*
     *  @函数名:markDirty
     *  功能:标记脏
     */
    void markDirty() {
        dirtyFlag = true;
    }
    
public:
    ///其他函数
    //写回缓存中
    void writeBackToBuffer() {
        if (dirtyFlag) {
            oneFileManager -> markDirty(pageId);
            ((BufType) pageData) [0] = pageId;
            ((BufType) pageData) [1] = nextPageId;
            ((BufType) pageData) [2] = prevPageId;
            ((BufType) pageData) [3] = objId;
            ((BufType) pageData) [4] = lsn;
            ((BufType) pageData) [5] = slotCnt;
            ((BufType) pageData) [6] = level;
            ((BufType) pageData) [7] = indexId;
            ((BufType) pageData) [8] = freeData;
            ((BufType) pageData) [9] = pminlen;
            ((BufType) pageData) [10] = freeCnt;
            ((BufType) pageData) [11] = reservedCnt;
            ((BufType) pageData) [12] = xactreserved;
            ((BufType) pageData) [13] = tornBits;
            ((BufType) pageData) [14] = flagBits;
        }
        dirtyFlag = false;
    }
    
    friend class TablePageFooter;
    friend class TablePage;
};

#endif // TABLE_PAGE_HEADER_H_
