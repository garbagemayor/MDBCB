#ifndef TABLE_ROW_H
#define TABLE_ROW_H

#include "../../filesystem/ByteBufBase.h"
#include "TableHeader.h"
#include "TableGrid.h"

#include <string>
#include <vector>

/**
 *  数据行类，在内存中存储一行的数据，由单个数据表类Table调用
 *  保持永远可修改，但要记录是否脏
 *  在文件中的存储按照如下格式：
 *  槽长度slotLen(2B) 状态位tagAB(2B) 
 *  定长部分大小fSize(2B) 定长部分列数fNCol(2B) 定长数据(fsize-4B) NULL位图(ceil(fNCol/8)B)
 *  变长列数vNCol(2B) 偏移数组vOffset(vNCol*2B) 变长数据(若干B)
 */
class TableRow {
    
public:
    //表头格式
    TableHeader * tableHeader;
    //状态位flagAB
    int flagAB;
    //数据内容
    std::vector<TableGrid *> gridList;
    //是否脏
    bool dirtyFlag;
    
public:
    /*
     *  @构造函数
     *  @参数tableHeader_:数据表的表头，描述了数据行的逻辑格式
     *  功能:创建一个新数据行
     */
    TableRow(TableHeader * tableHeader_) {
        //空指针报错
        if (tableHeader_ == NULL) {
            std::cout << "TableRow(NULL) error" << std::endl;
            return;
        }
        //数据行仍然可以修改报错
        if (tableHeader_ -> isModifiable()) {
            std::cout << "TableRow(...) error" << std::endl;
            tableHeader = NULL;
            return;
        }
        //根据表头的格式，创建一个合理全是NULL的行
        tableHeader = tableHeader_;
        dirtyFlag = true;
        gridList.resize(tableHeader -> getNCol());
        for (int i = 0; i < gridList.size(); i ++) {
            gridList[i] = new TableGrid(tableHeader -> getColumnById(i));
        }
    }
    
    /*
     *  @构造函数
     *  @参数tableHeader_:数据表的表头，描述了数据行的逻辑格式
     *  @参数slotData_:表头的槽数据，从中读取表头
     *  功能:从槽中读取一个数据行
     */
    TableRow(TableHeader * tableHeader_, ByteBufType slotData_) {
        readFromByteBuffer(slotData_);
        dirtyFlag = false;
    }
    
    /*
     *  析构函数
     *  功能:释放内存空间前，检查如果脏就写回
     */
    ~TableRow() {
        writeBackToBuffer();
        if (rowData != NULL) {
            delete rowData;
        }
    }
    
public:
    ///基本get函数
    
    
    
    
    
    
public:
    ///基本set函数
    
    
    
    
    
    
    
    
    

public:
    ///普通函数
    /*
     *  @函数名:writeBackToBuffer
     *  功能:如果脏就写回到缓存管理器中去
     */
    void writeBackToBuffer() {
        //脏标记合并
        for (int i = 0; i < (int) gridList.size(); i ++) {
            if (gridList[i] -> isDirty()) {
                dirtyFlag = true;
                break;
            }
        }
        //不脏返回
        if (!dirtyFlag) {
            return;
        }
        //写回
        
        
        
        
        
        
        
        
    }
    
    
public:
    ///其他函数
    /*
     *  @函数名:getPossibleSize
     *  @参数tableHeader:一个表头类
     *  @参数flag:如果是0就是求最小，是1就是求最大
     *  功能:计算数据行的最大/最小的大小。
     */
    static int getPossibleSize(TableHeader * tableHeader, int flag) {
        
        
        
        
    }
    
    
    
    
    
    
    
    
    
    
    
};

#endif // TABLE_ROW_H
