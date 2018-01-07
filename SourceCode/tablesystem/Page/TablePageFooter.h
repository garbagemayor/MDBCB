#ifndef TABLE_PAGE_FOOTER_H_
#define TABLE_PAGE_FOOTER_H_

#include "../../filesystem/OneFileManager.h"
#include <iostream>
#include <vector>

/**
 *  页脚类，只能由页类TablePage来调用。
 *  在一页的末尾，反向放置一个行偏移数组，short类型，表示这一页的第i个槽的起始位置；而行的定长部分长度、变长部分结束位置，存储在行本身里面。
 *  行偏移数组表示页中数据行的逻辑顺序。
 */
class TablePageFooter {
    
private:
    ///基本信息
    //单文件管理器
    OneFileManager * oneFileManager;
    //这一页完整的数据内容
    ByteBufType pageData;
    //是否脏（与缓存页管理器中的页面相比）
    bool dirtyFlag;
    
private:
    ///从页头抄来的信息
    //页编号
    int pageId;
    //槽数量
    int slotCnt;
    
private:
    ///页脚内存储的信息
    //行偏移数组
    std::vector < short > slotOffset;
    
public:
    /*
     *  @构造函数
     *  @参数pageId_:这一页的编号（默认0），也可以创建后再来赋值
     *  功能:给一个新的页新建一个页脚，创建后必须手动给oneFileManager和pageData赋值
     */
    TablePageFooter(int pageId_ = 0) {
        oneFileManager = NULL;
        pageData = NULL;
        dirtyFlag = true;
        pageId = pageId_;
        slotCnt = 0;
        slotOffset.clear();
    }
    
    /*
	 *  @构造函数
	 *  @参数oneFileManager_:单文件管理器
	 *  @参数pageData_:该页的全部数据的指针
     *  @参数pageId_:这一页的编号（默认0），也可以创建后再来赋值
	 *  @参数slotCnt_:该页的槽数量，TablePage从PageHeader里面获取之后传进来
     *  功能:读取已有页的页脚
     */
    TablePageFooter(OneFileManager * oneFileManager_, ByteBufType pageData_, int pageId_, int slotCnt_) {
        //基本信息
        oneFileManager = oneFileManager_;
        pageData = pageData_;
        dirtyFlag = false;
        pageId = pageId_;
        slotCnt = slotCnt_;
        //页脚内的信息
        slotOffset.clear();
        slotOffset.resize(slotCnt);
        for (int i = 0; i < slotCnt; i ++) {
            short tmpOffset = ((short *) pageData) [(PAGE_SIZE >> 1) - 1 - i];
            slotOffset[i] = tmpOffset;
        }
    }

    /*
	 * @析构函数
	 * 功能:如果页脚信息有修改，就把信息重新写回去
     */
    ~TablePageFooter() {
        writeBackToBuffer();
    }

public:
    ///基本get函数
    /*
     *  @函数名:getSlotCnt
     *  功能:获取槽数量
     */
    int getSlotCnt() {
        return slotCnt;
    }
    
    /*
     *  @函数名:getSlotOffset
     *  功能:获取槽的偏移量
     */
    int getSlotOffset(int slotId) {
        return slotOffset[slotId];
    }
    
    /*
     *  @函数名:getSizeInSlot
     *  功能:获取页脚在存储文件中占的大小，单位字节
     */
    int getSizeInSlot() {
        return slotCnt << 1;
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
     *  @函数名:markDirty
     *  功能:标记脏
     */
    void markDirty() {
        dirtyFlag = true;
    }
    
    /*
     *  @函数名:addSlot
     *  @参数offset:新槽的偏移量
     *  功能:新增一个槽
     */
    void addSlot(int offset) {
        //先标记脏
        dirtyFlag = true;
        slotCnt += 1;
        slotOffset.push_back(offset);
    }
    
    /*
     *  @函数名:removeSlot
     *  功能:删除一个行
     */
    void removeSlot(int slotId) {
        //不存在这个槽报错
        if (slotId < 0 || slotId >= (int) slotOffset.size()) {
            std::cout << "TablePageFooter.removeSlot(" << slotId << ") error 1" << std::endl;
            return;
        }
        //已删除报错
        if (slotOffset[slotId] < 0) {
            std::cout << "TablePageFooter.removeSlot(" << slotId << ") error 2" << std::endl;
            return;
        }
        dirtyFlag = true;
        slotOffset[slotId] = - slotOffset[slotId];
    }
    
public:
    ///普通函数
    /*
     *  @函数名:writeBackToBuffer
     *  功能:写回缓存中，把缓存中这一页标记为脏，把当前类标记为干净
     */
    void writeBackToBuffer() {
        if (dirtyFlag) {
            oneFileManager -> markDirty(pageId);
            for (int i = 0; i < slotCnt; i ++) {
                ((short *) pageData) [(PAGE_SIZE >> 1) - 1 - i] = slotOffset[i];
            }
        }
        dirtyFlag = false;
    }
    
    /*
     *  @函数名:print
     *  功能:打印出来，用来调试
     */
    void print() {
        std::cout << "TablePageFooter.print() {" << std::endl;
        std::cout << "    slotCnt = " << slotCnt << std::endl;
        for (int i = 0; i < slotCnt; i ++) {
            std::cout << "    slotOffset[" << i << "] = " << slotOffset[i] << std::endl;
        }
        std::cout << "}" << std::endl;
    }
    
    friend class TablePageHeader;
    friend class TablePage;
};

#endif // TABLE_PAGE_FOOTER_H_
