#ifndef TABLE_COLUMN_H_
#define TABLE_COLUMN_H_

#include "../../filesystem/ByteBufBase.h"
#include "TableDataType.h"

#include <cstring>
#include <string>

/**
 *  列信息类
 *  存储表头信息时，每个列信息都这样存储：
 *  colLen(2B) flag(2B) type(1B) nameLen(1B) name(_B)
 *  默认值和自动赋值，目前没有set函数，因为不支持这两垃圾玩意
 *  “互不相同”的列一定有索引，优先选择Hash索引
 *  “主键” = “非NULL” + “互不相同”
 */
class TableColumn {

private:
    static const int f_hasVariableLength = 1 << 0;
    static const int f_isUnique = 1 << 1;
    static const int f_allowNull = 1 << 2;
    static const int f_hasDefault = 1 << 3;
    static const int f_isAutomatic = 1 << 4;
    static const int f_isPrimaryKey = 1 << 5;
    static const int f_hasTreeIndex = 1 << 6;
    static const int f_hasHashIndex = 1 << 7;

private:
    //列名称
    std::string name;
    //列类型
    TableDataType type;
    //定长列数据的长度，变长列数据的最大长度
    int length;
    /*
     *  其他信息
     *  flag >> 0 & 1:      hasVariableLength   是否是变长数据
     *  flag >> 1 & 1:      isUnique            是否要求互不相同
     *  flag >> 2 & 1:      allowNull           是否允许空值NULL
     *  flag >> 3 & 1:      hasDefault          是否有默认值
     *  flag >> 4 & 1:      isAutomatic         是否自动填入数值
     *  flag >> 5 & 1:      isPrimaryKey        是否是主键
     *  flag >> 6 & 1:      hasTreeIndex        是否有B+树索引
     *  flag >> 7 & 1:      hasHashIndex        是否有Hash索引
     */
    int flag;
    //是否可以修改
    bool modifiable;
    
public:
    /*
     *  @构造函数
     *  功能:新建一个空的列信息，但是列不能为空，默认flag全是0
     */
    TableColumn() {
        name = "";
        type = TableDataType::t_error;
        length = 0;
        flag = 0;
        modifiable = true;
    }
    
    /*
     *  @指针拷贝构造函数
     *  功能:复制一份一模一样的
     */
    TableColumn(TableColumn * tableColumn) {
        //空指针报错
        if (tableColumn == NULL) {
            std::cout << "TableColumn(NULL) error" << std::endl;
            return;
        }
        name = tableColumn -> name;
        type = tableColumn -> type;
        length = tableColumn -> length;
        flag = tableColumn -> flag;
        if (type == TableDataType::t_string) {
            flag |= f_hasVariableLength;
        }
        modifiable = tableColumn -> modifiable;
    }

    /*
     *  @析构函数
     */
    ~TableColumn() {
    }
    
public:
    ///基本get函数
    /*
     *  函数名:getName
     *  功能:获取列名
     */
    std::string getName() {
        return name;
    }
    
    /*
     *  函数名:getDataType
     *  功能:获取列数据的类型
     */
    TableDataType getDataType() {
        return type;
    }
    
    /*
     *  函数名:getDataLength
     *  功能:获取（定长）列数据的长度，或（变长）列数据的最大长度
     */
    int getDataLength() {
        return length;
    }
    
    /*
     *  @函数名:hasVariableLength
     *  功能:返回是否是变长数据
     */
    bool hasVariableLength() {
        return (flag & f_hasVariableLength) != 0;
    }
    
    /*
     *  @函数名:isUnique
     *  功能:返回是否必须互不相同
     */
    bool isUnique() {
        return (flag & f_isUnique) != 0;
    }
    
    /*
     *  @函数名:allowNull
     *  功能:返回是否允许NULL
     */
    bool allowNull() {
        return (flag & f_allowNull) != 0;
    }
    
    /*
     *  @函数名:hasDefault
     *  功能:返回是否拥有默认值
     */
    bool hasDefault() {
        return (flag & f_hasDefault) != 0;
    }
    
    /*
     *  @函数名:isAutomatic
     *  功能:返回是否可以自动赋值
     */
    bool isAutomatic() {
        return (flag & f_isAutomatic) != 0;
    }
    
    /*
     *  @函数名:isPrimaryKey
     *  功能:返回是否可以自动赋值
     */
    bool isPrimaryKey() {
        return (flag & f_isPrimaryKey) != 0;
    }
    
    /*
     *  @函数名:hasTreeIndex
     *  功能:返回是否拥有B+树索引
     */
    bool hasTreeIndex() {
        return (flag & f_hasTreeIndex) != 0;
    }
    
    /*
     *  @函数名:hasHashIndex
     *  功能:返回是否拥有Hash索引
     */
    bool hasHashIndex() {
        return (flag & f_hasHashIndex) != 0;
    }
    
    /*
     *  函数名:getSizeInSlot
     *  功能:存储表头信息的时候，这一列的列信息占多少字节
     */
    int getSizeInSlot() {
        return 6 + name.length();
    }
    
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
            std::cout << "TableColumn.setConstant() error" << std::endl;
            return;
        }
        //没有列名报错
        if (name == "") {
            std::cout << "TableColumn.setConstant() error" << std::endl;
            return;
        }
        //没有数据类型报错
        if (type == TableDataType::t_error) {
            std::cout << "TableColumn.setConstant() error" << std::endl;
            return;
        }
        //主键 = 主键标记 + 非NULL + 互不相同 + B+树索引 的逻辑错误
        if (isPrimaryKey() && (allowNull() || !isUnique() || !hasTreeIndex())) {
            std::cout << "TableColumn.setConstant() error" << std::endl;
            return;
        }
        //互不相同 = 互不相同标记 + B+树索引 逻辑错误
        if (isUnique() && ! hasTreeIndex()) {
            std::cout << "TableColumn.setConstant() error" << std::endl;
            return;
        }
        //设为常量
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
            std::cout << "TableColumn.setName(" << name_ << ") error" << std::endl;
            return;
        }
        if (name != "") {
            std::cout << "TableColumn.setName(" << name_ << ") error" << std::endl;
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
            std::cout << "TableColumn.setName(" << name_ << ") error" << std::endl;
            return;
        }
    }
    
    /*
     *  @函数名:setType
     *  @参数type_:要设置数据类型
     *  功能:设置数据类型，必须是合法类型
     */
    void setType(TableDataType type_) {
        //不可修改报错
        if (!modifiable) {
            std::cout << "TableColumn.setType(" << type_ << ") error" << std::endl;
            return;
        }
        if (type != TableDataType::t_error) {
            std::cout << "TableColumn.setType(" << type_ << ") error" << std::endl;
            return;
        }
        //类型不合法报错
        if (type_ < t_bool || type_ > t_lob) {
            std::cout << "TableColumn.setType(" << type_ << ") error" << std::endl;
            return;
        }
        type = type_;
        length = getDataTypeMaxLength(type);
    }
    
    /*
     *  @函数名:setUnique
     *  功能:设置为必须互不相同，要强制拥有索引
     */
    void setUnique(bool f) {
        //不可修改报错
        if (!modifiable) {
            std::cout << "TableColumn.setUnique(" << f << ") error" << std::endl;
            return;
        }
        if (f) {
            flag |= f_isUnique;
            if (!hasVariableLength()) {
                flag |= f_hasTreeIndex;
            } else {
                flag |= f_hasHashIndex;
            }
        } else {
            flag &= ~f_isUnique;
        }
    }
    
    /*
     *  @函数名:setAllowNull
     *  功能:设置为允许NULL
     */
    void setAllowNull(bool f) {
        //不可修改报错
        if (!modifiable) {
            std::cout << "TableColumn.setAllowNull(" << f << ") error" << std::endl;
            return;
        }
        if (f) {
            flag |= f_allowNull;
        } else {
            flag &= ~f_allowNull;
        }
    }
    
    /*
     *  @函数名:setPrimaryKey
     *  功能:设置为主键，主键不能NULL而且还要互不相同
     */
    void setPrimaryKey(bool f) {
        //不可修改报错
        if (!modifiable) {
            std::cout << "TableColumn.setPrimaryKey(" << f << ") error" << std::endl;
            return;
        }
        if (f) {
            flag |= f_isPrimaryKey;
            flag &= ~f_allowNull;
            flag |= f_isUnique;
            if (!hasVariableLength()) {
                flag |= f_hasTreeIndex;
            } else {
                flag |= f_hasHashIndex;
            }
        } else {
            flag &= ~f_isPrimaryKey;
        }
    }
    
    /*
     *  @函数名:setHasTreeIndex
     *  功能:设置为有B+树索引
     */
    void setHasTreeIndex(bool f) {
        //变长数据报错
        if (hasVariableLength()) {
            std::cout << "TableColumn.setHasTreeIndex(" << f << ") error" << std::endl;
            return;
        }
        if (f) {
            flag |= f_hasTreeIndex;
        } else {
            flag &= ~f_hasTreeIndex;
        }
    }
    
    /*
     *  @函数名:setHasHashIndex
     *  功能:设置为有Hash索引
     */
    void setHasHashIndex(bool f) {
        if (f) {
            flag |= f_hasHashIndex;
        } else {
            flag &= ~f_hasHashIndex;
        }
    }
    
public:
    ///高级函数
    /*
     *  函数名:writeAsByte
     *  参数buf:转化的目标地址
     *  功能:把列信息转化为二进制数据，写入目标地址，并移动目标地址
     */
    void writeAsByte(ByteBufType & buf) {
        ByteBufType curBuf = buf;
        int sz = getSizeInSlot();
        int nameLen = name.length();
        writeNumberToByte(curBuf, 2, sz);
        writeNumberToByte(curBuf, 2, flag);
        writeNumberToByte(curBuf, 1, type);
        writeNumberToByte(curBuf, 1, nameLen);
        writeArrayToByte(curBuf, nameLen, (ByteBufType) name.c_str(), nameLen);
        //长度报错
        if (curBuf - buf != sz) {
            std::cout << "TableColumn.writeAsByte(...) error" << std::endl;
            return;
        }
        buf = curBuf;
    }
    
    /*
     *  @函数名:readFromByte
     *  @参数slotData:读取来源
     *  功能:从二进制数据读取得到完整的表头信息
     */
    void readFromByte(ByteBufType & colData) {
        ByteBufType colData_ = colData;
        int sz = readByteToNumber(colData, 2);
        flag = readByteToNumber(colData, 2);
        type = (TableDataType) readByteToNumber(colData, 1);
        length = getDataTypeMaxLength(type);
        int nameLen = readByteToNumber(colData, 1);
        static char name_[MAX_NAME_LENGTH + 4];
        memset(name_, 0, sizeof(char) * (MAX_NAME_LENGTH + 4));
        readByteToArray(colData, nameLen, (ByteBufType) name_, MAX_NAME_LENGTH);
        name = name_;
        //长度纠错
        if (colData - colData_ != sz) {
            std::cout << "TableColumn.readFromByteBuffer() error" << std::endl;
            return;
        }
    }
    
    /*
     *  @函数名:isEqualTo
     *  功能:判断两个列头是相同的
     */
    bool isEqualTo(TableColumn * tableColumn) {
        if (name != tableColumn -> name) {
            return false;
        }
        if (type != tableColumn -> type) {
            return false;
        }
        if (flag != tableColumn -> flag) {
            return false;
        }
        return true;
    }
};

#endif // TABLE_COLUMN_H_
