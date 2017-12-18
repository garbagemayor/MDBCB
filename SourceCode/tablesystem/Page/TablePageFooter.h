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
    bool isDirty;
    
private:
    ///从页头抄来的信息
    //页编号
    int pageId;
    //槽数量
    int slotCnt;
    
private:
    ///页脚内存储的信息
    //行偏移数组
    std::vector<short> slotOffset;
    
public:
    /*
     *  @构造函数
     *  @参数pageId_:这一页的编号（默认0），也可以创建后再来赋值
     *  功能:给一个新的页新建一个页脚，创建后必须手动给oneFileManager和pageData赋值
     */
    TablePageFooter(int pageId_ = 0) {
        oneFileManager = NULL;
        pageData = NULL;
        isDirty = true;
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
        isDirty = false;
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
    ///TODO 其他
    /*
     *  @函数名:getSizeInSlot
     *  功能:获取页脚在存储文件中占的大小，单位字节
     */
    int getSizeInSlot() {
        return slotCnt << 1;
    }
    
    /*
     *  @函数名:writeBackToBuffer
     *  功能:写回缓存中，把缓存中这一页标记为脏，把当前类标记为干净
     */
    void writeBackToBuffer() {
        if (isDirty) {
            oneFileManager -> markDirty(pageId);
            for (int i = 0; i < slotCnt; i ++) {
                ((short *) pageData) [(PAGE_SIZE >> 1) - 1 - i] = slotOffset[i];
            }
        }
        isDirty = false;
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    friend class TablePageHeader;
    friend class TablePage;
};

#endif // TABLE_PAGE_FOOTER_H_
