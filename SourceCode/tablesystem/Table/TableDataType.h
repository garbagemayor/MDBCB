#ifndef TABLE_DATA_TYPE_H_
#define TABLE_DATA_TYPE_H_

/**
 *  ֧�ֵ���������
 *  ���У�boolռ��1���ֽڣ�long��64λ������string��0~256�ֽ��ַ�����lob�������С�����ƴ�
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

