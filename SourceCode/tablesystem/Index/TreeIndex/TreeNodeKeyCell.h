#ifndef TREE_NODE_KEY_CELL_H
#define TREE_NODE_KEY_CELL_H

#include "../../../filesystem/ByteBufBase.h"

/**
 *  B+�������ļ�ֵ��ÿ����ֵ��С20B
 *  �洢��ʽ��key(8B) keyPageId(4B) keySlotId(4B) sonPageId(4B)
 */
class TreeNodeKeyCell {
    
private:
    uint64 key;
    int keyPageId;
    int keySlotId;
    int sonPageId;
    
public:
    /*
     *  @���캯��
     *  ����:ȫ����ʼ��Ϊ0
     */
    TreeNodeKeyCell() {
        key = 0;
        keyPageId = 0;
        keySlotId = 0;
        sonPageId = 0;
    }
    
    /*
     *  @���캯��
     *  ����:��key��ص���������ֵ
     */
    TreeNodeKeyCell(int key_, int keyPageId_, int keySlotId_) {
        key = key_;
        keyPageId = keyPageId_;
        keySlotId = keySlotId_;
        sonPageId = 0;
    }
    
    /*
     *  @���캯��
     *  ����:���ݼ�ֵָ�룬����һ��һģһ���ĳ���
     */
    TreeNodeKeyCell(TreeNodeKeyCell * keyCell) {
        key = keyCell -> key;
        keyPageId = keyCell -> keyPageId;
        keySlotId = keyCell -> keySlotId;
        sonPageId = keyCell -> sonPageId;
    }
    
    /*
     *  @��������
     */
    ~TreeNodeKeyCell() {
    }
    
public:
    ///��ͨ����
    /*
     *  @������:writeAsByte
     *  ����:��Ԫ�ص���Ϣת��Ϊ���������ݣ�д��Ŀ���ַ�����ƶ�Ŀ���ַ
     */
    void writeAsByte(ByteBufType & buf) {
        writeNumberToByte(buf, 8, key);
        writeNumberToByte(buf, 4, keyPageId);
        writeNumberToByte(buf, 4, keySlotId);
        writeNumberToByte(buf, 4, sonPageId);
    }
    
    /*
     *  @������:readFromByte
     *  ����:�Ӷ��������ݶ�ȡ�õ�Ԫ����Ϣ
     */
    void readFromByte(ByteBufType & data) {
        key = readByteToNumber(data, 8);
        keyPageId = readByteToNumber(data, 4);
        keySlotId = readByteToNumber(data, 4);
        sonPageId = readByteToNumber(data, 4);
    }
    
    /*
     *  @������:replaceKey
     *  ����:�滻��ֵ�������滻�ӽڵ���
     */
    void replaceKey(TreeNodeKeyCell * keyCell) {
        key = keyCell -> key;
        keyPageId = keyCell -> keyPageId;
        keySlotId = keyCell -> keySlotId;
    }
    
    /*
     *  @������:replaceSon
     *  ����:�滻�ӽڵ���
     */
    void replaceSon(int sonPageId_) {
        sonPageId = sonPageId_;
    }
    
    /*
     *  @������:isEqualTo
     *  ����:�ж����
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
     *  @������:isLessThan
     *  ����:�ж��Ƿ����С
     */
    bool isLessThan(TreeNodeKeyCell * keyCell, bool (* cmpKeyCell) (uint64, uint64)) {
        //�ȱ���ֵ��С
        if (key != keyCell -> key) {
            if (cmpKeyCell == NULL) {
                return key < keyCell -> key;
            } else {
                return (* cmpKeyCell) (key, keyCell -> key);
            }
        }
        //��ֵ��ͬ���ͱ�ҳ��źͲ۱��
        if (keyPageId != keyCell -> keyPageId) {
            return keyPageId < keyCell -> keyPageId;
        }
        if (keySlotId != keyCell -> keySlotId) {
            return keySlotId < keyCell -> keySlotId;
        }
        //ȫ����Ȳ���������
        return false;
    }
    
    /*
     *  @������:isGreaterThan
     *  ����:�ж��Ƿ������
     */
    bool isGreaterThan(TreeNodeKeyCell * keyCell, bool (* cmpKeyCell) (uint64, uint64)) {
        //����Ƚ�
        return keyCell -> isLessThan(this, cmpKeyCell);
    }
    
    friend class TreeNode;
    friend class TreeIndex;
};

#endif // TREE_NODE_KEY_CELL_H
