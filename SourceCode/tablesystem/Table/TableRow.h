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
 *  槽长度slotLen(2B) 状态位flagAB(2B) 
 *  定长部分大小fSize(2B) 定长部分列数fNCol(2B) 定长数据(fsizeB) NULL位图(ceil(fNCol/8)B)
 *  变长列数vNCol(2B) 偏移数组vOffset(vNCol*2B) 变长数据(vSizeB)
 *  变长数据的NULL位图是vOffset的值为0，变长列偏移数组是基于槽起点计算
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
        for (int i = 0; i < (int) gridList.size(); i ++) {
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
        //根据表头的格式和二进制数据内容，读取数据行
        tableHeader = tableHeader_;
        readFromByteBuffer(slotData_);
        dirtyFlag = false;
    }
    
    /*
     *  析构函数
     *  功能:释放内存空间前，检查如果脏就写回
     */
    ~TableRow() {
        writeBackToBuffer();
        for (int i = 0; i < (int) gridList.size(); i ++) {
            delete gridList[i];
        }
        gridList.clear();
    }
    
public:
    ///基本get函数
    /*
     *  @函数名:getTableHeader
     *  功能:返回表头信息
     */
    TableHeader * getTableHeader() {
        return tableHeader;
    }
    
    /*
     *  @函数名:getFlagAB
     *  功能:返回状态位
     */
    int getFlagAB() {
        return flagAB;
    }
    
    /*
     *  @函数名:getGridById
     *  @参数id:数据格的逻辑位置
     *  功能:用数据格的逻辑位置获取数据格信息，如果不存在就报错
     */
    TableGrid * getGridById(int id) {
        if (id < 0 || id >= (int) gridList.size()) {
            std::cout << "TableRow.getGridById(" << id << ") error" << std::endl;
            return NULL;
        }
        return gridList[id];
    }
    
    /*
     *  @函数名:getGridByName
     *  @参数columnName:数据列的名称
     *  功能:用数据列的名称获取数据格信息，如果不存在就报错
     */
    TableGrid * getGridByName(std::string columnName) {
        for (int i = 0; i < (int) gridList.size(); i ++) {
            if (tableHeader -> getColumnById(i) -> getName() == columnName) {
                return gridList[i];
            }
        }
        if (true) {
            std::cout << "TableRow.getGridByName(" << columnName << ") error" << std::endl;
            return NULL;
        }
    }
    
    /*
     *  @函数名:getSizeInSlot
     *  功能:获取表头需要占据的槽的大小
     */
    int getSizeInSlot() {
        int fNCol = 0;
        int fSize = 0;
        int vNCol = 0;
        int vSize = 0;
        for (int i = 0; i < (int) gridList.size(); i ++) {
            if (!tableHeader -> getColumnById(i) -> hasVariableLength()) {
                fNCol += 1;
                fSize += gridList[i] -> getDataLength();
            } else {
                vNCol += 1;
                vSize += gridList[i] -> getDataLength();
            }
        }
        return 8 + fSize + ((fNCol + 7) >> 3) + 2 + vNCol * 2 + vSize;
    }
    
    /*
     *  @函数名:canMeetNullRequirement
     *  功能:检查每格的NULL情况是否符合表头的要求，
     */
    bool canMeetNullRequirement() {
        for (int i = 0; i < (int) gridList; i ++) {
            if (gridList[i] -> isNull() && !tableHeader -> getColumnById(i) -> allowNull()) {
                return false;
            }
        }
        return true;
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
     *  @函数名:
     *
     */
    
    
    
    
    
    
    
    

public:
    ///普通函数
    /*
     *  @函数名:toByteBuffer
     *  功能:把数据行信息转化为可以写入的二进制数据，行的大小如果超过一页就报错
     *  返回值:成功转化后的数据指针，失败返回NULL
     *  注意:不要去闲的蛋疼去清理这片内存，这个数组是static的，程序结束时自动清理
     */
    ByteBufType toByteBuffer() {
        //计算各项参数
        int fNCol = 0;
        int fSize = 0;
        int vNCol = 0;
        int vSize = 0;
        for (int i = 0; i < (int) gridList.size(); i ++) {
            if (!tableHeader -> getColumnById(i) -> hasVariableLength()) {
                fNCol += 1;
                fSize += gridList[i] -> getDataLength();
            } else {
                vNCol += 1;
                vSize += gridList[i] -> getDataLength();
            }
        }
        //总长度超标报错
        int slotLen = 8 + fSize + ((fNCol + 7) >> 3) + 2 + vNCol * 2 + vSize;
        if (slotLen > PAGE_SIZE - PAGE_HEADER_SIZE) {
            std::cout << "TableRow.toByteBuffer() error" << std::endl;
            return NULL;
        }
        //定义一堆临时使用的东西
        static Byte buf[PAGE_SIZE];
        memset(buf, 0, sizeof(Byte) * PAGE_SIZE);
        static Byte nullMap[8];
        memset(nullMap, 0, sizeof(Byte) * 8);
        ByteBufType curBuf = buf;
        //开始写入
        writeNumberToByte(curBuf, 2, slotLen);
        writeNumberToByte(curBuf, 2, flagAB);
        writeNumberToByte(curBuf, 2, fSize);
        writeNumberToByte(curBuf, 2, fNCol);
        for (int i = 0; i < fNCol; i ++) {
            writeArrayToByte(curBuf, gridList[i] -> getDataLength(), gridList[i] -> getDataPointer());
            nullMap[i >> 3] |= 1 << (i & 7);
        }
        writeArrayToByte(curBuf, ((fNCol + 7) >> 3), nullMap);
        writeNumberToByte(curBuf, 2, vNCol);
        int vOffset = 8 + fSize + ((fNCol + 7) >> 3) + 2 + vNCol * 2;
        for (int i = fNCol; i < fNCol + vNCol; i ++) {
            writeNumberToByte(curBuf, 2, vOffset);
            vOffset += gridList[i] -> getDataLength();
        }
        for (int i = fNCol; i < fNCol + vNCol; i ++) {
            writeArrayToByte(curBuf, gridList[i] -> getDataLength(), gridList[i] -> getDataPointer());
        }
        //写完之后检查长度报错
        if (curBuf - buf != slotLen) {
            std::cout << "TableRow.toByteBuffer() error" << std::endl;
            return NULL;
        }
        return buf;
    }
    
    /*
     *  @函数名:readFromByteBuffer
     *  功能:从槽中的二进制数据读取得到完整的数据行
     */
    void readFromByteBuffer(ByteBufType slotData) {
        ByteBufType slotData_ = slotData;
        
        
        
        
    }
    
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
        //空指针报错
        if (tableHeader == NULL || (flag != 0 && flag != 1)) {
            std::cout << "TableRow::getPossibleSize(..., " << flag << ") error" << std::endl;
            return 0;
        }
        //计算长度范围
        int maxSlotLen = 0;
        int minSlotLen = 0;
        for (int i = 0; i < tableHeader -> getNCol(); i ++) {
            
        }
        //正常返回或报错
        if (flag == 0) {
            return minSlotLen;
        } else {
            return maxSlotLen;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
};

#endif // TABLE_ROW_H
