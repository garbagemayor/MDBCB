#ifndef HASH_KEY_CELL_H
#define HASH_KEY_CELL_H

#include "../../../filesystem/ByteBufBase.h"

/**
 *  Hash索引的条目，每个条目大小16B
 *  存储方式：key(8B) keyPageId(4B) keySlotId(4B)
 */
class HashKeyCell {
    
private:
    uint64 key;
    int keyPageId;
    int keySlotId;
    
public:
    /*
     *  @构造函数
     *  功能:全部初始化为0
     */
    HashKeyCell() {
        key = 0;
        keyPageId = 0;
        keySlotId = 0;
    }
    
    /*
     *  @构造函数
     *  功能:给key相关的三个数赋值
     */
    HashKeyCell(uint64 key_, int keyPageId_, int keySlotId_) {
        key = key_;
        keyPageId = keyPageId_;
        keySlotId = keySlotId_;
    }
    
    /*
     *  @构造函数
     *  功能:根据键值指针，复制一个一模一样的出来
     */
    HashKeyCell(HashKeyCell * keyCell) {
        key = keyCell -> key;
        keyPageId = keyCell -> keyPageId;
        keySlotId = keyCell -> keySlotId;
    }
    
    /*
     *  @析构函数
     */
    ~HashKeyCell() {
    }

public:
    ///普通函数
    /*
     *  @函数名:writeAsByte
     *  功能:把条目信息转化为二进制数据，写入目标地址，并移动目标地址
     */
    void writeAsByte(ByteBufType & buf) {
        writeNumberToByte(buf, 8, key);
        writeNumberToByte(buf, 4, keyPageId);
        writeNumberToByte(buf, 4, keySlotId);
    }
    
    /*
     *  @函数名:readFromByte
     *  功能:从二进制数据读取得到元素信息
     */
    void readFromByte(ByteBufType & data) {
        key = readByteToNumber(data, 8);
        keyPageId = readByteToNumber(data, 4);
        keySlotId = readByteToNumber(data, 4);
    }
    
    /*
     *  @函数名:replaceKey
     *  功能:替换键值，其实就是全部替换
     */
    void replaceKey(HashKeyCell * keyCell) {
        key = keyCell -> key;
        keyPageId = keyCell -> keyPageId;
        keySlotId = keyCell -> keySlotId;
    }
    
    /*
     *  @函数名:isEqualTo
     *  功能:判断Hash值相等
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
