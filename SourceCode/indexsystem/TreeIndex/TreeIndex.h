#ifndef TREE_INDEX_H_
#define TREE_INDEX_H_

#include "../BaseIndex/BaseIndex.h"

/*
 *  B+������������������̳С�
 *  �Խڵ�ļ�¼��ʹ��ҳ��š�
 */
template <typename KeyType>
class TreeIndex 
    : public BaseIndex {
    
protected:
    //���ڵ���
    int rootPageId;
    //ͷ�ڵ���
    int headPageId;
    
    
public:
    //���캯��
    TreeIndex(TableManager * tableManager_, char * colName)
        : BaseIndex(tableManager_, colName) {
        indexType = IndexType.treeIndex;
        
        
    }
    
}

#endif // TREE_INDEX_H_
