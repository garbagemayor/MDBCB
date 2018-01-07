#ifndef TREE_NODE_KEY_CELL_H
#define TREE_NODE_KEY_CELL_H

#include "../../../filesystem/ByteBufBase.h"

/**
 *  B+树索引的键值，每个键值大小20B
 *  存储方式：key(8B) keyPageId(4B) keySlotId(4B) sonPageId(4B)
 */
class TreeNodeKeyCell {
    
private:
    uint64 key;
    int keyPageId;
    int keySlotId;
    int sonPageId;
    
public:
    /*
     *  @构造函数
     *  功能:全都初始化为0
     */
    TreeNodeKeyCell() {
        key = 0;
        keyPageId = 0;
        keySlotId = 0;
        sonPageId = 0;
    }
    
    /*
     *  @构造函数
     *  功能:给key相关的三个数赋值
     */
    TreeNodeKeyCell(int key_, int keyPageId_, int keySlotId_) {
        key = key_;
        keyPageId = keyPageId_;
        keySlotId = keySlotId_;
        sonPageId = 0;
    }
    
    /*
     *  @构造函数
     *  功能:根据键值指针，复制一个一模一样的出来
     */
    TreeNodeKeyCell(TreeNodeKeyCell * keyCell) {
        key = keyCell -> key;
        keyPageId = keyCell -> keyPageId;
        keySlotId = keyCell -> keySlotId;
        sonPageId = keyCell -> sonPageId;
    }
    
    /*
     *  @析构函数
     */
    ~TreeNodeKeyCell() {
    }
    
public:
    ///基本get函数
    uint64 getKey() {
        return key;
    }
    
    int getKeyPageId() {
        return keyPageId;
    }
    
    int getKeySlotId() {
        return keySlotId;
    }
    
public:
    ///普通函数
    /*
     *  @函数名:writeAsByte
     *  功能:把元素的信息转化为二进制数据，写入目标地址，并移动目标地址
     */
    void writeAsByte(ByteBufType & buf) {
        writeNumberToByte(buf, 8, key);
        writeNumberToByte(buf, 4, keyPageId);
        writeNumberToByte(buf, 4, keySlotId);
        writeNumberToByte(buf, 4, sonPageId);
    }
    
    /*
     *  @函数名:readFromByte
     *  功能:从二进制数据读取得到元素信息
     */
    void readFromByte(ByteBufType & data) {
        key = readByteToNumber(data, 8);
        keyPageId = readByteToNumber(data, 4);
        keySlotId = readByteToNumber(data, 4);
        sonPageId = readByteToNumber(data, 4);
    }
    
    /*
     *  @函数名:replaceKey
     *  功能:替换键值，但不替换子节点编号
     */
    void replaceKey(TreeNodeKeyCell * keyCell) {
        key = keyCell -> key;
        keyPageId = keyCell -> keyPageId;
        keySlotId = keyCell -> keySlotId;
    }
    
    /*
     *  @函数名:replaceSon
     *  功能:替换子节点编号
     */
    void replaceSon(int sonPageId_) {
        sonPageId = sonPageId_;
    }
    
    /*
     *  @函数名:isEqualTo
     *  功能:判断相等
     */
    bool isEqualTo(TreeNodeKeyCell * keyCell) {
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
    
    /*
     *  @函数名:isLessThan
     *  功能:判断是否比它小
     */
    bool isLessThan(TreeNodeKeyCell * keyCell, bool (* cmpKeyCell) (uint64, uint64)) {
        //先比数值大小
        if (key != keyCell -> key) {
            if (cmpKeyCell == NULL) {
                return key < keyCell -> key;
            } else {
                return (* cmpKeyCell) (key, keyCell -> key);
            }
        }
        //数值相同，就比页编号和槽编号
        if (keyPageId != keyCell -> keyPageId) {
            return keyPageId < keyCell -> keyPageId;
        }
        if (keySlotId != keyCell -> keySlotId) {
            return keySlotId < keyCell -> keySlotId;
        }
        //全都相等才是真的相等
        return false;
    }
    
    /*
     *  @函数名:isGreaterThan
     *  功能:判断是否比它大
     */
    bool isGreaterThan(TreeNodeKeyCell * keyCell, bool (* cmpKeyCell) (uint64, uint64)) {
        //反向比较
        return keyCell -> isLessThan(this, cmpKeyCell);
    }
    
    friend class TreeNode;
    friend class TreeIndex;
};

#endif // TREE_NODE_KEY_CELL_H
