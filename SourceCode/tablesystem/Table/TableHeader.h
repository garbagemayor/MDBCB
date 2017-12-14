#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include "../../filesystem/ByteBufBase.h"
#include "../../filesystem/OneFileManager.h"
#include "TableColumn.h"

#include <string>
#include <vector>

/**
 *  表头类，由单个数据表类Table调用。
 *  存储表头信息时按照如下格式：
 *  slotLen(2B) nameLen(2B) nRow(4B) nCol(4B) name(4*_B) colList[i](4*_B)
 */
class TableHeader {
    
private:
    //数据表的名称
    std::string name;
    //数据表的行数
    int nRow;
    //每一列的信息
    std::vector<TableColumn *> colList;
    //是否可以修改
    bool modifiable;
    
public:
    /*
     *  @构造函数
     *  功能:新建一个空的表头，表头的内容以后再添加
     */
    TableHeader() {
        name = "";
        nRow = 0;
        colList.clear();
        modifiable = true;
    }
    
    /*
     *  @构造函数
     *  @参数slotData_:表头的槽数据，从中读取表头
     *  功能:从槽中读取数据表的表头
     */
    TableHeader(ByteBufType slotData_) {
        readFromByteBuffer(slotData_);
        modifiable = false;
    }
    
    ~TableHeader() {
    }
    
public:
    ///基本get函数
    //获取列数
    int nCol() {
        return colList.size();
    }
    
    //获取数据表名字
    std::string getName() {
        return name;
    }
    
    //获取表头需要占据的槽的大小
    int getSizeInSlot() {
        int sz = 12;
        sz += (name.length() + 3) & ~3;
        for (int i = 0; i < (int) colList.size(); i ++) {
            sz += colList[i] -> getSizeInSlot();
        }
        return sz;
    }
    
public:
    ///高级函数   
    /*
     *  @函数名:toByteBuffer
     *  功能:把表头信息转化为可以写入的二进制数据，表头大小如果超过一页就会报错
     *  返回值:成功转化后的数据指针，失败返回NULL
     *  注意:不要去闲的蛋疼去清理这片内存，这个数组是static的，程序结束时自动清理。
     */
    ByteBufType toByteBuffer() {
        int sz = getSizeInSlot();
        static Byte buf[PAGE_SIZE];
        ByteBufType curBuf = buf;
        if (sz > PAGE_SIZE - PAGE_HEADER_SIZE) {
            std::cout << "TableHeader.toByteBuffer() error" << std::endl;
            return NULL;
        }
        writeNumberToByte(curBuf, 2, sz);
        writeNumberToByte(curBuf, 2, name.length());
        writeNumberToByte(curBuf, 4, nRow);
        writeNumberToByte(curBuf, 4, nCol());
        writeArrayToByte(curBuf, ((name.length() + 3) & ~3), (ByteBufType) name.c_str(), name.length());
        for (int i = 0; i < (int) colList.size(); i ++) {
            colList[i] -> writeAsByte(curBuf);
        }
        return buf;
    }
    
    /*
     *  @函数名:readFromByteBuffer
     *  @参数slotData:读取来源
     *  功能:从槽中的二进制数据读取得到完整的表头信息
     */
    void readFromByteBuffer(ByteBufType slotData) {
        ByteBufType slotData_ = slotData;
        int sz = readByteToNumber(slotData, 2);
        int nameLen = readByteToNumber(slotData, 2);
        nRow = readByteToNumber(slotData, 4);
        int nCol = readByteToNumber(slotData, 4);
        static char name_[MAX_NAME_LENGTH + 4];
        memset(name_, 0, sizeof(name_));
        readByteToArray(slotData, nameLen, (ByteBufType) name_, MAX_NAME_LENGTH);
        name = name_;
        colList.clear();
        colList.resize(nCol);
        for (int i = 0; i < nCol; i ++) {
            colList[i] -> readFromByteBuffer(slotData);
        }
        //长度纠错
        if (slotData - slotData_ != sz) {
            std::cout << "TableHeader.readFromByteBuffer() error" << endl;
            return;
        }
    }
    
    
    
    
    
    
    
    
    //用列的逻辑位置获取列信息
    TableColumn * getColumnByLogicId(int id) {
        if (id < 0 || id > (int) colList.size()) {
            return NULL;
        }
        return colList[id];
    }
    
    //用数据的偏移量获取列信息
    TableColumn * getColumnByOffset(int offset) {
        for (int i = 0; i < (int) colList.size(); i ++) {
            if (colList[i] -> offset == offset) {
                return colList[i];
            }
        }
        return NULL;
    }
    
public:
    ///其他函数
    /*
     *  @函数名:isModifiable
     *  功能:是否可以修改
     */
    bool isModifiable() {
        return modifiable;
    }
    
    /*
     *  @函数名:initFinish
     *  功能:初始化结束后，就不能再进行任何修改
     */
    void initFinish() {
        modifiable = false;
    }
    
    /*
     *  @函数名:setName
     *  @参数name_:新名字
     *  功能:设置数据表名字，名字要符合c99命名规则，否则报错而且设置失败
     */
    void setName(std::string name_) {
        //不可修改报错
        if (!modifiable) {
            std::cout << "TableHeader.setName(" << name_ << ") error 1" << std::endl;
            return;
        }
        //检验命名合法
        bool isLegal = true;
        if (name_.length() > MAX_NAME_LENGTH) {
            isLegal = false;
        } else {
            for (int i = 0; i < (int) name_.length() && isLegal; i ++) {
                if ((name_[i] < 'A' || name_[i] > 'Z') &&
                    (name_[i] < 'a' || name_[i] > 'z') &&
                    (name_[i] < '0' || name_[i] > '9' || i == 0) &&
                    name_[i] != '_') {
                    isLegal = false;
                }
            }
        }
        //非法命名报错
        if (isLegal) {
            name = name_;
        } else {
            std::cout << "TableHeader.setName(" << name_ << ") error 2" << std::endl;
            return;
        }
    }
    
    /*
     *  @函数名:addColumn
     *  @参数tableColumn_:新列指针
     *  功能:添加一个新的列，新列的实例会被复制之后再添加，如果列数量或者总大小超标就不添加并报错
     */
    void addColumn(TableColumn * tableColumn) {
        //不可修改报错
        if (modifiable == false) {
            std::cout << "TableHeader.addcolumn(...) error 1" << std::endl;
            return;
        }
        //列数量过多报错
        if (colList.size() == MAX_COL_NUM) {
            std::cout << "TableHeader.addcolumn(...) error 2" << std::endl;
            return;
        }
        //总大小过大报错
        /** 
         TODO 计算总大小、拷贝构造函数
         **/
        //复制再添加
        TableColumn * column = new TableColumn(*tableColumn);
        colList.push_back(column);
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif // TABLEHEADER_H
