#ifndef BYTE_BUF_BASE_H_
#define BYTE_BUF_BASE_H_

#include "utils/pagedef.h"
#include <iostream>

typedef unsigned char Byte;
typedef unsigned char * ByteBufType;
typedef unsigned long long uint64;

///�������Զ����Ƶķ�ʽд��ByteBufType�У�����ָ��ǰ��
/*
 *  @������:writeArrayToByte
 *  @����buf:д��ĵط�
 *  @����writeLen:д��ĳ���
 *  @����data:��Ҫд�������ָ��
 *  @����dataLen:������Ч���ֵĳ��ȣ�Ĭ��2^31 - 1
 *  ����:��data��ǰmin(writeLen, dataLen)�ֽ�д��buf�����writeLen > dataLen����0����䣬����bufǰ��writeLen�ֽ�
 */
void writeArrayToByte(ByteBufType & buf, int writeLen, ByteBufType data, int dataLen = (~0u >> 1)) {
    for (int i = 0; i < writeLen; i ++) {
        buf[i] = i < dataLen ? data[i] : 0;
    }
    buf += writeLen;
}

/*
 *  @������:writeNumberToByte
 *  @����buf:д��ĵط�
 *  @����length:д��ĳ��ȣ�������1,2,4,8
 *  @����num:��Ҫд�������
 *  ����:����num�Զ����Ƶ���ʽд��buf
 *  ע��:����Ҫ��ת��Ϊ��ͬ���ȵ��޷������ٴ�
 */
void writeNumberToByte(ByteBufType & buf, int length, uint64 num) {
    for (int i = 0; i < length; i ++) {
        buf[i] = ((ByteBufType) &num) [i];
    }
    buf += length;
}

/*
 *  @������:writeFloatToByte
 *  @����buf:д��ĵط�
 *  @����length:д��ĳ��ȣ�������4,8
 *  @����num:��Ҫд�������
 *  ����:������num�Զ����Ƶ���ʽд��buf
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

///�������Զ����Ƶķ�ʽ��ByteBufType�ж�����������ָ��ǰ��
/*
 *  @������:readByteToArray
 *  @����buf:�����ݵĵط�
 *  @����readLen:��ȡ�ĳ���
 *  @����data:��ȡ��д��ĵط�
 *  &����dataLen:д��λ����Ч���ֵĳ��ȣ�Ĭ��2^31 - 1
 *  ����:��buf��ȡmin(readLen, dataLen)�ֽ�д��data������bufǰ��readLen���ֽ�
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
 *  @������:readByteToNumber
 *  @����buf:�����ݵĵط�
 *  @����length:��ȡ�ĳ��ȣ�������1,2,4,8
 *  @����ֵ:��ȡ�Ľ��
 *  ����:��ȡlength��Byte��ת��Ϊ�������ͣ�����bufǰ��length���ֽ�
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
 *  @������:readByteToFloat
 *  @����buf:�����ݵĵط�
 *  @����length:��ȡ�ĳ��ȣ�������4,8
 *  @����ֵ:��ȡ�Ľ��
 *  ����:��ȡlength��Byte��ת��Ϊ���������ͣ�����bufǰ��length���ֽ�
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
