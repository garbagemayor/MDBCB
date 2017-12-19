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

/*
 *  @������:getDataTypeLength
 *  ����:�������ͷ������͵ĳ��ȣ��䳤���ͷ���0��
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
 *  @������:getDataTypeMaxLength
 *  ����:�������ͷ������͵ĳ��ȣ��䳤���ͷ�����󳤶ȡ�
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

