#ifndef TREE_NODE_SON_H
#define TREE_NODE_SON_H

/**
 *  B+���������ڵ���ӽڵ��б��Ԫ�أ���С20B
 *  û���κβ���
 */
class TreeNodeSon {
    
private:
    uint64 key;
    int keyPageId;
    int keySlotId;
    int sonPageId;
    
public:
    TreeNodeSon() {
        key = 0;
        keyPageId = 0;
        keySlotId = 0;
        sonPageId = 0;
    }
    ~TreeNodeSon() {
    }
    
public:
    friend class TableNode;
};

#endif // TREE_NODE_SON_H
