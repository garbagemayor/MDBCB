#ifndef TABLE_COLUMN_H_
#define TABLE_COLUMN_H_

#include "../../filesystem/ByteBufBase.h"
#include "TableDataType.h"

#include <string>

/**
 *  列信息类，只能由表头类TableHeader创建
 *  存储表头信息时，每个列信息都这样存储：
 *  colLen(2B) offset(2B) type(1B) dataLen(1B) nameLen(2B) name(4*_B)
 */
class TableColumn {

public:
    //列名称
    std::string name;
    //列数据的偏移量
    int offset;
    //列类型
    TableDataType type;
    //列数据的自身长度
    int length;
    /*
     *  其他信息
     *  flag >> 1 & 1:      hasVariableLength   是否是变长数据
     *  flag >> 2 & 1:      isUnique            是否要求互不相同
     *  flag >> 3 & 1:      allowNull           是否允许空值NULL
     *  flag >> 4 & 1:      hasDefault          是否有默认值
     *  flag >> 5 & 1:      automatic           是否自动填入数值
     *  flag >> 6 & 1:      
     */
    int flag;

private:
    TableColumn() {
        name = "";
        offset = 0;
        type = TableDataType::t_error;
        length = 0;
        flag = 0;
    }
    ///其他构造函数

public:
    ~TableColumn() {
    }
    
public:
    ///其他函数
    /*
     *  函数名:getSizeInSlot
     *  功能:存储表头信息的时候，这一列的列信息占多少字节
     */
    int getSizeInSlot() {
        return 8 + ((name.length() + 3) & ~3);
    }
    
    /*
     *  函数名:writeAsByte
     *  参数buf:转化的目标地址
     *  功能:把列信息转化为二进制数据，写入目标地址，并移动目标地址
     *  返回值:写入数据的长度
     */
    int writeAsByte(ByteBufType & buf) {
        int sz = getSizeInSlot();
        int nameLen = name.length();
        writeNumberToByte(buf, 2, sz);
        writeNumberToByte(buf, 2, offset);
        writeNumberToByte(buf, 1, type);
        writeNumberToByte(buf, 1, length);
        writeNumberToByte(buf, 2, (nameLen + 3 ) & ~3);
        writeArrayToByte(buf, ((nameLen + 3) & ~3), (ByteBufType) name.c_str(), nameLen);
        return sz;
    }
    
    void readFromByteBuffer(ByteBufType & colData) {
        ByteBufType colData_ = colData;
        int sz = readByteToNumber(colData, 2);
        offset = readByteToNumber(colData, 2);
        type = (TableDataType) readByteToNumber(colData, 1);
        length = readByteToNumber(colData, 1);
        int nameLen = readByteToNumber(colData, 2);
        static char name_[MAX_NAME_LENGTH + 4];
        readByteToArray(colData, nameLen, (ByteBufType) name_, MAX_NAME_LENGTH);
        name = name_;
        //长度纠错
        if (colData - colData_ != sz) {
            std::cout << "TableColumn.readFromByteBuffer() error" << std::endl;
            return;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    friend class TableHeader;
};

#endif // TABLE_COLUMN_H_
