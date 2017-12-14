#ifndef TREE_INDEX_H_
#define TREE_INDEX_H_

#include "../BaseIndex/BaseIndex.h"

/*
 *  B+树索引，从索引基类继承。
 *  对节点的记录都使用页编号。
 */
template <typename KeyType>
class TreeIndex 
    : public BaseIndex {
    
protected:
    //根节点编号
    int rootPageId;
    //头节点编号
    int headPageId;
    
    
public:
    //构造函数
    TreeIndex(TableManager * tableManager_, char * colName)
        : BaseIndex(tableManager_, colName) {
        indexType = IndexType.treeIndex;
        
        
    }
    
}

#endif // TREE_INDEX_H_
