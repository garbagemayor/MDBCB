#ifndef TABLEHEADER_H
#define TABLEHEADER_H

#include "../../filesystem/ByteBufBase.h"
#include "TableColumn.h"

#include <string>
#include <vector>

/**
 *  表头类，由单个数据表类Table调用。
 *  存储表头信息时按照如下格式：
 *  slotLen(2B) nRow(4B) nCol(4B) nameLen(1B) name(_B) colList[i](_B)
 *  创建数据表时先创建表头，创建完表头并锁定之后表头就不能再进行任何修改，数据表的结构显然是不允许修改的
 *  表头中的列自动按照定长在前变长在后的顺序排列，这个顺序就是行数据的顺序
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
    
    /*
     *  @析构函数
     */
    ~TableHeader() {
        for (int i = 0; i < (int) colList.size(); i ++) {
            delete colList[i];
        }
        colList.clear();
    }
    
public:
    ///基本get函数
    /*
     *  @函数名:getNRow
     *  功能:获取行数
     */
    int getNRow() {
        return nRow;
    }
    
    /*
     *  @函数名:getNCol
     *  功能:获取列数
     */
    int getNCol() {
        return colList.size();
    }
    
    /*
     *  @函数名:getConstantLengthNCol
     *  功能:获取定长列数
     */
    int getConstantLengthNCol() {
        int i = 0;
        for (int i = 0; i < (int) colList.size(); i ++) {
            if (colList[i] -> hasVariableLength()) {
                break;
            }
        }
        return i;
    }
    
    /*
     *  @函数名:getVariableLengthNCol
     *  功能:获取变长列数
     */
    int getVariableLengthNCol() {
        return getNCol() - getConstantLengthNCol();
    }
    
    /*
     *  @函数名:getName
     *  功能:获取数据表名字
     */
    std::string getName() {
        return name;
    }
    
    /*
     *  @函数名:getColumnById
     *  功能:用列的逻辑位置获取列信息，如果不存在就报错
     */
    TableColumn * getColumnById(int id) {
        if (id < 0 || id > (int) colList.size()) {
            std::cout << "TableHeader.getColumnById(" << id << ") error" << std::endl;
            return NULL;
        }
        return colList[id];
    }
    
    /*
     *  @函数名:getColumnByName
     *  功能:用列的名字位置获取列信息，如果不存在就报错
     */
    TableColumn * getColumnByName(std::string columnName) {
        for (int i = 0; i < (int) colList.size(); i ++) {
            if (colList[i] -> getName() == columnName) {
                return colList[i];
            }
        }
        if (true) {
            std::cout << "TableHeader.getColumnByName(" << columnName << ") error" << std::endl;
            return NULL;
        }
    }
    
    /*
     *  @函数名:getSizeInSlot
     *  功能:获取表头需要占据的槽的大小
     */
    int getSizeInSlot() {
        int sz = 12;
        sz += (name.length() + 3) & ~3;
        for (int i = 0; i < (int) colList.size(); i ++) {
            sz += colList[i] -> getSizeInSlot();
        }
        return sz;
    }
    
    /*
     *  @函数名:getPossibleMaxSize
     *  功能:计算数据行在可能的情况下的最大大小，这个函数在TableHeader.cpp文件中实现
     */
    int getPossibleMaxSize();
    
    /*
     *  @函数名:getPossibleMinSize
     *  功能:计算数据行在可能的情况下的最小大小，这个函数在TableHeader.cpp文件中实现
     */
    int getPossibleMinSize();
    
    /*
     *  @函数名:isModifiable
     *  功能:是否可以修改
     */
    bool isModifiable() {
        return modifiable;
    }
    
public:
    ///基本set函数
    /*
     *  @函数名:setConstant
     *  功能:初始化结束后设置为常量，就不能再进行任何修改
     */
    void setConstant() {
        //已经是常量报错
        if (!modifiable) {
            std::cout << "TableHeader.setConstant() error" << std::endl;
            return;
        }
        //没有表名报错
        if (name == "") {
            std::cout << "TableHeader.setConstant() error" << std::endl;
            return;
        }
        //没有数据列报错
        if (colList.size() == 0) {
            std::cout << "TableHeader.setConstant() error" << std::endl;
            return;
        }
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
     *  功能:添加一个新的列，新列的实例会被复制之后再添加
     *       如果添加后列数量太多就不添加并报错，但不检查添加后数据行可能的长度超标情况
     */
    void addColumn(TableColumn * tableColumn) {
        //不可修改报错
        if (modifiable == false) {
            std::cout << "TableHeader.addColumn(...) error 1" << std::endl;
            return;
        }
        //新列仍然可修改报错
        if (tableColumn -> isModifiable()) {
            std::cout << "TableHeader.addColumn(...) error 2" << std::endl;
            return;
        }
        //列数量过多报错
        if (colList.size() == MAX_COL_NUM) {
            std::cout << "TableHeader.addColumn(...) error 3" << std::endl;
            return;
        }
        //新列名字重复报错
        for (int i = 0; i < (int) colList.size(); i ++) {
            if (colList[i] -> getName() == tableColumn -> getName()) {
                std::cout << "TableHeader.addColumn(...) error 4" << std::endl;
            }
        }
        //复制再添加
        TableColumn * column = new TableColumn(tableColumn);
        if (column -> hasVariableLength()) {
            colList.push_back(column);
        } else {
            colList.resize(colList.size() + 1);
            for (int i = colList.size() - 2; i >= 0; i --) {
                if (colList[i] -> hasVariableLength()) {
                    colList[i + 1] = colList[i];
                } else {
                    colList[i] = column;
                    break;
                }
            }
        }
    }
    
public:
    ///普通函数   
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
        writeNumberToByte(curBuf, 4, nRow);
        writeNumberToByte(curBuf, 4, getNCol());
        writeNumberToByte(curBuf, 1, name.length());
        writeArrayToByte(curBuf, name.length(), (ByteBufType) name.c_str(), name.length());
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
        nRow = readByteToNumber(slotData, 4);
        int nCol = readByteToNumber(slotData, 4);
        int nameLen = readByteToNumber(slotData, 1);
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
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif // TABLEHEADER_H
