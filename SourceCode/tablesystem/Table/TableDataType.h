#ifndef TABLE_DATA_TYPE_H_
#define TABLE_DATA_TYPE_H_

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

#endif // TABLE_DATA_TYPE_H_

