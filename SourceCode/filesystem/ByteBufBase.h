#ifndef BYTE_BUF_BASE_H_
#define BYTE_BUF_BASE_H_

#include "utils/pagedef.h"
#include <iostream>

typedef unsigned char Byte;
typedef unsigned char * ByteBufType;
typedef unsigned long long uint64;

///把数据以二进制的方式写入ByteBufType中，并把指针前移
/*
 *  @函数名:writeArrayToByte
 *  @参数buf:写入的地方
 *  @参数writeLen:写入的长度
 *  @参数data:需要写入的数据指针
 *  @参数dataLen:数据有效部分的长度，默认2^31 - 1
 *  功能:将data的前min(writeLen, dataLen)字节写入buf，如果writeLen > dataLen就用0来填充，并将buf前移writeLen字节
 */
void writeArrayToByte(ByteBufType & buf, int writeLen, ByteBufType data, int dataLen = (~0u >> 1)) {
    for (int i = 0; i < writeLen; i ++) {
        buf[i] = i < dataLen ? data[i] : 0;
    }
    buf += writeLen;
}

/*
 *  @函数名:writeNumberToByte
 *  @参数buf:写入的地方
 *  @参数length:写入的长度，可以是1,2,4,8
 *  @参数num:需要写入的数据
 *  功能:整数num以二进制的形式写入buf
 *  注意:负数要先转换为相同精度的无符号数再传
 */
void writeNumberToByte(ByteBufType & buf, int length, uint64 num) {
    for (int i = 0; i < length; i ++) {
        buf[i] = ((ByteBufType) &num) [i];
    }
    buf += length;
}

/*
 *  @函数名:writeFloatToByte
 *  @参数buf:写入的地方
 *  @参数length:写入的长度，可以是4,8
 *  @参数num:需要写入的数据
 *  功能:浮点数num以二进制的形式写入buf
 */
void writeFloatToByte(ByteBufType & buf, int length, double num) {
    if (length == 4) {
        float tmp_num = num;
        writeArrayToByte(buf, length, (ByteBufType) &tmp_num);
    } else if (length == 8) {
        writeArrayToByte(buf, length, (ByteBufType) &num);
    } else {
        std::cout << "writeFloatToByte(...) error" << std::endl;
    }
}

///把数据以二进制的方式从ByteBufType中读出来，并把指针前移
/*
 *  @函数名:readByteToArray
 *  @参数buf:读数据的地方
 *  @参数readLen:读取的长度
 *  @参数data:读取后写入的地方
 *  &参数dataLen:写入位置有效部分的长度，默认2^31 - 1
 *  功能:从buf读取min(readLen, dataLen)字节写入data，并把buf前移readLen个字节
 */
void readByteToArray(ByteBufType & buf, int readLen, ByteBufType data, int dataLen) {
    for (int i = 0; i < readLen; i ++) {
        if (i < dataLen) {
            data[i] = buf[i];
        }
    }
    buf += readLen;
}

/*
 *  @函数名:readByteToNumber
 *  @参数buf:读数据的地方
 *  @参数length:读取的长度，可以是1,2,4,8
 *  @返回值:读取的结果
 *  功能:读取length个Byte，转化为整数类型，并把buf前移length个字节
 */
uint64 readByteToNumber(ByteBufType & buf, int length) {
    uint64 num = 0;
    for (int i = 0; i < length; i ++) {
        ((ByteBufType) &num) [i] = buf[i];
    }
    buf += length;
    return num;
}

/*
 *  @函数名:readByteToFloat
 *  @参数buf:读数据的地方
 *  @参数length:读取的长度，可以是4,8
 *  @返回值:读取的结果
 *  功能:读取length个Byte，转化为浮点数类型，并把buf前移length个字节
 */
double readByteToFloat(ByteBufType & buf, int length) {
    static char tmp_buf[8 + 4];
    readByteToArray(buf, length, (ByteBufType) tmp_buf, length);
    if (length == 4) {
        return * (float *) tmp_buf;
    } else if (length == 8) {
        return * (double *) tmp_buf;
    } else {
        std::cout << "readByteToNumber(...) error" << std::endl;
        return 0;
    }
}

#endif // BYTE_BUF_BASE_H_
