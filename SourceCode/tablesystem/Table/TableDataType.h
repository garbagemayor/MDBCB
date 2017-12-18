#ifndef TABLE_DATA_TYPE_H_
#define TABLE_DATA_TYPE_H_

/**
 *  支持的数据类型
 *  其中，bool占满1个字节，long是64位整数，string是0~256字节字符串，lob是任意大小二进制串
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
};

#endif // TABLE_DATA_TYPE_H_

