#ifndef TABLE_DATA_TYPE_H_
#define TABLE_DATA_TYPE_H_

#include "../../filesystem/ByteBufBase.h"

#include <iostream>

/**
 *  支持的数据类型
 *  其中，bool占满1个字节，long是64位整数，
 *  string是0~256字节变长字符串，
 *  lob是任意大小二进制串，但作为8字节定长数据存放
 */
 
#define MAX_STRING_LENGTH 256

enum TableDataType {
    t_error = 0,
    t_bool = 1,
    t_char = 2,
    t_short = 3,
    t_int = 4,
    t_long = 5,
    t_float = 6,
    t_double = 7,
    t_string = 8,
    t_lob = 9,
    t_null,//只在Filter里使用
};

/*
 *  @函数名:getSuperType
 *  功能:获取更大的类型
 */
TableDataType getSuperType(TableDataType type) {
    TableDataType reType = TableDataType::t_error;
    switch (type) {
    case TableDataType::t_bool:
    case TableDataType::t_char:
    case TableDataType::t_short:
    case TableDataType::t_int:
    case TableDataType::t_long:
    case TableDataType::t_lob:
        reType = TableDataType::t_long;
        break;
    case TableDataType::t_float:
    case TableDataType::t_double:
        reType = TableDataType::t_double;
        break;
    case TableDataType::t_string:
        reType = TableDataType::t_string;
        break;
    default:
        reType = TableDataType::t_error;
    }
    return reType;
}

bool cmpError(uint64, uint64);
bool cmpBool(uint64, uint64);
bool cmpChar(uint64, uint64);
bool cmpShort(uint64, uint64);
bool cmpInt(uint64, uint64);
bool cmpLong(uint64, uint64);
bool cmpFloat(uint64, uint64);
bool cmpDouble(uint64, uint64);

bool (* cmpFunctionList[]) (uint64, uint64) = {
    cmpError,
    cmpBool,
    cmpChar,
    cmpShort,
    cmpInt,
    cmpLong,
    cmpFloat,
    cmpDouble,
    cmpError,//string
    cmpError,//lob
};

/*
 *  @函数名:getDataTypeLength
 *  功能:定长类型返回类型的长度，变长类型返回0。
 */
int getDataTypeLength(TableDataType type) {
    switch (type) {
    case t_error:
    case t_string:
        return 0;
    case t_bool:
    case t_char:
        return 1;
    case t_short:
        return 2;
    case t_int:
    case t_float:
        return 4;
    case t_long:
    case t_double:
    case t_lob:
        return 8;
    default:
        return 0;
    }
}

/*
 *  @函数名:getDataTypeMaxLength
 *  功能:定长类型返回类型的长度，变长类型返回最大长度。
 */
int getDataTypeMaxLength(TableDataType type) {
    switch (type) {
    case t_error:
        return 0;
    case t_bool:
    case t_char:
        return 1;
    case t_short:
        return 2;
    case t_int:
    case t_float:
        return 4;
    case t_long:
    case t_double:
    case t_lob:
        return 8;
    case t_string:
        return 256;
    default:
        return 0;
    }
}

///各个类型比大小的函数，整数全都是以无符号的形式比大小，浮点数才有符号一说
/*
 *  @函数名cmpError
 *  功能:报错
 */
bool cmpError(uint64 a, uint64 b) {
    std::cout << "TableDataType.cmpError(" << a << ", " << b << ")" << std::endl;
    return false;
}
/*
 *  @函数名cmpBool
 *  功能:比大小
 */
bool cmpBool(uint64 a, uint64 b) {
    a = a != 0;
    b = b != 0;
    return a < b;
}

/*
 *  @函数名cmpChar
 *  功能:比大小
 */
bool cmpChar(uint64 a, uint64 b) {
    unsigned char a_ = a;
    unsigned char b_ = b;
    return a_ < b_;
}

/*
 *  @函数名cmpShort
 *  功能:比大小
 */
bool cmpShort(uint64 a, uint64 b) {
    unsigned short a_ = a;
    unsigned short b_ = b;
    return a_ < b_;
}

/*
 *  @函数名cmpInt
 *  功能:比大小
 */
bool cmpInt(uint64 a, uint64 b) {
    unsigned int a_ = a;
    unsigned int b_ = b;
    return a_ < b_;
}

/*
 *  @函数名cmpLong
 *  功能:比大小
 */
bool cmpLong(uint64 a, uint64 b) {
    return a < b;
}

/*
 *  @函数名cmpFloat
 *  功能:比大小
 */
bool cmpFloat(uint64 a, uint64 b) {
    float a_ = * (float *) & a;
    float b_ = * (float *) & b;
    return a_ < b_;
}

/*
 *  @函数名cmpDouble
 *  功能:比大小
 */
bool cmpDouble(uint64 a, uint64 b) {
    double a_ = * (double *) & a;
    double b_ = * (double *) & b;
    return a_ < b_;
}

#endif // TABLE_DATA_TYPE_H_

