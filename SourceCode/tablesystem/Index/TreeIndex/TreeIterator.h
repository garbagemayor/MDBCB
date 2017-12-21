#ifndef TREE_ITERATOR_H_
#define TREE_ITERATOR_H_

#include "TreeNode.h"

class TreeIterator {
    
private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //所在节点的编号
    int nodeId;
    //节点中的序号
    int listId;
    //节点
    TreeNode * node;
    
private:
    /*
     *  @构造函数
     *  功能:创建一个指向空的迭代器
     */
    TreeIterator() {
        oneFileManager = NULL;
        nodeId = -1;
        listId = -1;
        node = NULL;
    }
    
    /*
     *  @构造函数
     *  功能:创建一个正常的迭代器
     */
    TreeIterator( OneFileManager * oneFileManager_, int nodeId_, int listId_) {
        oneFileManager = oneFileManager_;
        nodeId = nodeId_;
        listId = listId_;
        node = new TreeNode(oneFileManager, nodeId);
    }
    
    /*
     *  @构造函数
     *  功能:拷贝
     */
    TreeIterator(const TreeIterator & ite) {
        nodeId = ite.nodeId;
        listId = ite.listId;
        node = new TreeNode(oneFileManager, nodeId);
    }
    
public:
    /*
     *  @析构函数
     */
    ~TreeIterator() {
    }
    
public:
    ///重载符号
    /*
     *  ++ ite
     */
    TreeIterator & operator ++ () {
        if (nodeId == -1 || listId == -1) {
            return *this;
        } else if (listId < (int) node -> keyList.size() - 1) {
            listId ++;
            return *this;
        } else {
            nodeId = node -> pageHeader -> getNextPageId();
            if (nodeId == -1) {
                listId = -1;
                node = NULL;
            } else {
                listId = 0;
                TreeNode * nodeTmp = new TreeNode(oneFileManager, nodeId);
                delete node;
                node = nodeTmp;
            }
        }
    }
    
    /*
     *  ite ++
     */
    TreeIterator operator ++ (int) {
        TreeIterator iteTmp(* this);
        ++ (* this);
        return iteTmp;
        
    }
    
    friend class TreeIndex;
};


#endif // TREE_ITERATOR_H_
