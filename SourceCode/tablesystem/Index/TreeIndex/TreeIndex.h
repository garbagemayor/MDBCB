#ifndef TREE_INDEX_H_
#define TREE_INDEX_H_

#include "../BaseIndex.h"

/**
 *  B+树索引，从索引基类继承，由索引管理器IndexManager来管理。
 *  对节点的记录都使用页编号。 
 */
class TreeIndex 
    : public BaseIndex {
    
protected:
    //根节点编号
    int rootPageId;
    //头节点编号
    int headPageId;
    
public:
    /*
     *  @构造函数
     *  功能:先调用BaseIndex的构造函数，然后记录基本信息
     */
    TreeIndex(BufPageManager * bufPageManager_, std::string tableName, TableColumn * tableColumn_)
        : BaseIndex(bufPageManager_, tableName, tableColumn_) {
        //空指针报错
        if (bufPageManager_ == NULL || tableColumn_ == NULL) {
            std::cout << "TreeIndex(..., " << tableName_ << ", ...) error" << std::endl;
            return;
        }
        //基本信息
        indexStructure = IndexStructure.in_treeIndex;
        rootPageId = 0;
        headPageId = 0;
        //一开始有一个空的根节点
        ///TODO
        
    }
    
    /*
     *  @析构函数
     */
    ~TableIndex(){
    }
    
public:
    ///基本get函数
    
    
    
public:
    ///
    
    
    
public:
    ///普通函数
    
    
    
    
    
    
    
    
    
    
    
    
    
}

#endif // TREE_INDEX_H_
