#ifndef HASH_KEY_CELL_H
#define HASH_KEY_CELL_H

#include "../../../filesystem/ByteBufBase.h"

/**
 *  Hash��������Ŀ��ÿ����Ŀ��С16B
 *  �洢��ʽ��key(8B) keyPageId(4B) keySlotId(4B)
 */
class HashKeyCell {
    
private:
    uint64 key;
    int keyPageId;
    int keySlotId;
    
public:
    /*
     *  @���캯��
     *  ����:ȫ����ʼ��Ϊ0
     */
    HashKeyCell() {
        key = 0;
        keyPageId = 0;
        keySlotId = 0;
    }
    
    /*
     *  @���캯��
     *  ����:��key��ص���������ֵ
     */
    HashKeyCell(int key_, int keyPageId_, int keySlotId_) {
        key = key_;
        keyPageId = keyPageId_;
        keySlotId = keySlotId_;
    }
    
    /*
     *  @���캯��
     *  ����:���ݼ�ֵָ�룬����һ��һģһ���ĳ���
     */
    HashKeyCell(HashKeyCell * keyCell) {
        key = keyCell -> key;
        keyPageId = keyCell -> keyPageId;
        keySlotId = keyCell -> keySlotId;
    }
    
    /*
     *  @��������
     */
    ~HashKeyCell() {
    }

public:
    ///��ͨ����
    /*
     *  @������:writeAsByte
     *  ����:����Ŀ��Ϣת��Ϊ���������ݣ�д��Ŀ���ַ�����ƶ�Ŀ���ַ
     */
    void writeAsByte(ByteBufType & buf) {
        writeNumberToByte(buf, 8, key);
        writeNumberToByte(buf, 4, keyPageId);
        writeNumberToByte(buf, 4, keySlotId);
    }
    
    /*
     *  @������:readFromByte
     *  ����:�Ӷ��������ݶ�ȡ�õ�Ԫ����Ϣ
     */
    void readFromByte(ByteBufType & data) {
        key = readByteToNumber(data, 8);
        keyPageId = readByteToNumber(data, 4);
        keySlotId = readByteToNumber(data, 4);
    }
    
    /*
     *  @������:replaceKey
     *  ����:�滻��ֵ����ʵ����ȫ���滻
     */
    void replaceKey(HashKeyCell * keyCell) {
        key = keyCell -> key;
        keyPageId = keyCell -> keyPageId;
        keySlotId = keyCell -> keySlotId;
    }
    
    /*
     *  @������:isEqualTo
     *  ����:�ж�Hashֵ���
     */
    bool isEqualTo(HashKeyCell * keyCell) {
        if (key != keyCell -> key) {
            return false;
        }
        if (keyPageId != keyCell -> keyPageId) {
            return false;
        }
        if (keySlotId != keyCell -> keySlotId) {
            return false;
        }
        return true;
    }
    
    friend class HashClassifier;
    friend class HashBucket;
    friend class HashIterator;
    friend class HashIndex;
};

#endif // HASH_KEY_CELL_H
