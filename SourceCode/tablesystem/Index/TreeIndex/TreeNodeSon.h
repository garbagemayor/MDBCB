#ifndef TREE_NODE_SON_H
#define TREE_NODE_SON_H

/**
 *  B+树索引，节点的子节点列表的元素，大小20B
 *  没有任何操作
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
