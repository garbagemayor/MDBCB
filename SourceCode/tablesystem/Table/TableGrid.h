#ifndef TABLE_GRID_H
#define TABLE_GRID_H

#include "../../filesystem/ByteBufBase.h"
#include "TableColumn.h"

/**
 *  数据格类，在内存中存储一个格子的数据，由TableRow来调用
 *  保持永远可修改，但要记录是否脏
 */
class TableGrid {

private:
    //这一格所在的列的信息
    TableColumn * tableColumn;
    //是否是NULL
    bool nullFlag;
    //二进制形式下数据的长度
    int length;
    //二进制形式下的数据内容
    ByteBufType data;
    //是否脏
    bool dirtyFlag;

public:
    /*
     *  @构造函数
     *  @参数tableColumn_:所在列的信息
     *  功能:新建一个空的格子，里面是NULL
     */
    TableGrid(TableColumn * tableColumn_) {
        //空指针报错
        if (tableColumn_ == NULL) {
            std::cout << "TableGrid(NULL) error" << std::endl;
            return;
        }
        tableColumn = tableColumn_;
        nullFlag = true;
        length = 0;
        data = NULL;
        dirtyFlag = true;
    }
    
    ~TableGrid() {
        if (dirtyFlag) {
            std::cout << "~TableGrid() error" << std::endl;
        }
        if (data != NULL) {
            delete [] data;
        }
    }

public:
    ///基本get函数
    /*
     *  @函数名:getTableColumn
     *  功能:返回列信息指针
     */
    TableColumn * getTableColumn() {
        return tableColumn;
    }
    
    /*
     *  @函数名:isNull
     *  功能:返回是否是空值
     */
    bool isNull() {
        return nullFlag;
    }
    
    /*
     *  @函数名:getDataLength
     *  功能:返回数据长度
     */
    int getDataLength() {
        return length;
    }
    
    /*
     *  @函数名:getDataPointer
     *  功能:返回指向数据格内的数据的指针
     */
    ByteBufType getDataPointer() {
        return data;
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
     *  @函数名:setNull
     *  功能:设置为NULL，标记脏
     */
    void setNull() {
        dirtyFlag = true;
        nullFlag = true;
    }
    
    /*
     *  @函数名:setDataValueNumber
     *  @参数data_:要写入的数值
     *  @参数length_:要写入数值的长度
     *  功能:设置bool, char, short, int, long以及对应的unsigned，还有lob类型的格子的值，并标记脏
     */
    void setDataValueNumber(uint64 num, int length_) {
        //数据类型错误报错
        if (tableColumn -> getDataType() != TableDataType::t_bool &&
            tableColumn -> getDataType() != TableDataType::t_char &&
            tableColumn -> getDataType() != TableDataType::t_short &&
            tableColumn -> getDataType() != TableDataType::t_int &&
            tableColumn -> getDataType() != TableDataType::t_long &&
            tableColumn -> getDataType() != TableDataType::t_lob) {
            std::cout << "TableGrid.setDataValueNumber(" << num << ", " << length_ << ") error" << std::endl;
            return;
        }
        //数据长度报错
        if (tableColumn -> getDataLength() != length_) {
            std::cout << "TableGrid.setDataValueNumber(" << num << ", " << length_ << ") error" << std::endl;
            return;
        }
        dirtyFlag = true;
        nullFlag = false;
        length = length_;
        if (data == NULL ) {
            data = new Byte [length];
        }
        memset(data, 0, sizeof(Byte) * length);
        ByteBufType data_ = data;
        writeNumberToByte(data_, length, num);
    }
    
    /*
     *  @函数名:setDataValueFloat
     *  @参数data_:要写入的数值
     *  @参数length_:要写入数值的长度
     *  功能:设置float, double类型的格子的值，并标记脏
     */
    void setDataValueFloat(double num, int length_) {
        //数据类型错误报错
        if (tableColumn -> getDataType() != TableDataType::t_float &&
            tableColumn -> getDataType() != TableDataType::t_double) {
            std::cout << "TableGrid.setDataValueFloat(" << num << ", " << length_ << ") error" << std::endl;
            return;
        }
        //数据长度报错
        if (tableColumn -> getDataLength() != length_) {
            std::cout << "TableGrid.setDataValueFloat(" << num << ", " << length_ << ") error" << std::endl;
            return;
        }
        dirtyFlag = true;
        nullFlag = false;
        length = length_;
        if (data == NULL ) {
            data = new Byte [length];
        }
        memset(data, 0, sizeof(Byte) * length);
        ByteBufType data_ = data;
        writeFloatToByte(data_, length, num);
    }
    
    /*
     *  @函数名:setDataValueArray
     *  功能:设置string格子的值，标记脏
     */
    void setDataValueArray(ByteBufType string_, int length_) {
        //数据类型错误报错
        if (tableColumn -> getDataType() != TableDataType::t_string) {
            std::cout << "TableGrid.setDataValueArray(..., " << length_ << ") error" << std::endl;
            return;
        }
        //数据长度报错
        if (length_ < 0 || length >= MAX_STRING_LENGTH) {
            std::cout << "TableGrid.setDataValueArray(..., " << length_ << ") error" << std::endl;
            return;
        }
        dirtyFlag = true;
        nullFlag = false;
        length = length_;
        if (data == NULL ) {
            data = new Byte [MAX_STRING_LENGTH];
        }
        memset(data, 0, sizeof(Byte) * MAX_STRING_LENGTH);
        ByteBufType data_ = data;
        writeArrayToByte(data_, length, string_, length_);
    }
    
public:
    ///普通函数
    /*
     *  @函数名:isEqualTo
     *  功能:判断两个格子里的数据相等
     *       特别的，当两个格子的列类型不同时报错返回false，当两个格子都是NULL时返回true，一个是NULL另一个不是时返回false
     *       lob不能比大小，报错
     */
    bool isEqualTo(TableGrid * grid) {
        //类型不同、LOB类型报错
        if (tableColumn -> getDataType() != grid -> tableColumn -> getDataType() ||
            tableColumn -> getDataType() == TableDataType::t_lob) {
            std::cout << "TableGrid.isEqualTo(...) error" << std::endl;
            return false;
        }
        //NULL情况
        if (nullFlag && grid -> nullFlag) {
            return true;
        }
        if (nullFlag || grid -> nullFlag) {
            return false;
        }
        //一般情况
        for (int i = 0; i < length; i ++) {
            if (data[i] != grid -> data[i]) {
                return false;
            }
        }
        return true;
    }
    
    /*
     *  @函数名:isLessThan
     *  功能:判断是否小于另一个格子里的数据
     *       特别的，当两个格子的列类型不同时报错返回false，NULL小于任何数值，相同类型的两个NULL相等
     *       bool, char, short, int, long, float, double读取后直接比大小，整数用uint64，浮点数用double
     *       string按字节从左到右比大小，lob不能比大小，报错
     *  注意:所有的整数比大小都是无符号比大小，坑的一匹
     */
    bool isLessThan(TableGrid * grid) {
        //类型不同、LOB类型报错
        if (tableColumn -> getDataType() != grid -> tableColumn -> getDataType() ||
            tableColumn -> getDataType() == TableDataType::t_lob) {
            std::cout << "TableGrid.isLessThan(...) error" << std::endl;
            return false;
        }
        //NULL情况
        if (nullFlag && grid -> nullFlag) {
            return false;
        }
        if (nullFlag || grid -> nullFlag) {
            return nullFlag;
        }
        //仍然NULL报错
        if (data == NULL || grid -> data == NULL) {
            std::cout << "TableGrid.isLessThan(...) error" << std::endl;
            return false;
        }
        //整数情况
        if (tableColumn -> getDataType() == TableDataType::t_bool ||
            tableColumn -> getDataType() == TableDataType::t_char ||
            tableColumn -> getDataType() == TableDataType::t_short ||
            tableColumn -> getDataType() == TableDataType::t_int ||
            tableColumn -> getDataType() == TableDataType::t_long) {
            ByteBufType data_;
            uint64 num_1 = readByteToNumber(data_ = data, tableColumn -> getDataLength());
            uint64 num_2 = readByteToNumber(data_ = data, grid -> tableColumn -> getDataLength());
            return num_1 < num_2;
        }
        //浮点数情况
        if (tableColumn -> getDataType() == TableDataType::t_float ||
            tableColumn -> getDataType() == TableDataType::t_double) {
            ByteBufType data_;
            double num_1 = readByteToNumber(data_ = data, tableColumn -> getDataLength());
            double num_2 = readByteToNumber(data_ = data, grid -> tableColumn -> getDataLength());
            return num_1 < num_2;
        }
        //字符串情况
        if (tableColumn -> getDataType() == TableDataType::t_string) {
            for (int i = 0; i < length && i < grid -> length; i ++) {
                if (data[i] != grid -> data[i]) {
                    return data[i] < grid -> data[i];
                }
            }
            return false;
        }
    }
    
    /*
     *  @函数名:isGreaterThan
     *  功能:判断是否大于另一个格子里的数据，其实是反向调用isLessThan
     */
    void isGreaterThan(TableGrid * grid) {
        return grid -> isLessThan(this);
    }
};

#endif // TABLE_GRID_H
