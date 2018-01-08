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
    TreeIterator(OneFileManager * oneFileManager_, int nodeId_, int listId_) {
        oneFileManager = oneFileManager_;
        nodeId = nodeId_;
        listId = listId_;
        node = new TreeNode(oneFileManager, nodeId);
    }
    
    /*
     *  @拷贝构造函数
     */
    TreeIterator(const TreeIterator & ite) {
        * this = ite;
    }
    
    /*
     *  @重载等号赋值
     */
    TreeIterator & operator = (const TreeIterator & ite) {
        oneFileManager = ite.oneFileManager;
        nodeId = ite.nodeId;
        listId = ite.listId;
        node = new TreeNode(oneFileManager, nodeId);
    }
    
    /*
     *  @析构函数
     */
    ~TreeIterator() {
        if (node != NULL) {
            delete node;
            node = NULL;
        }
    }
    
public:
    ///重载符号
    /*
     *  @函数名:getNodeId
     */
    int getNodeId() {
        return nodeId;
    }
    
    /*
     *  @函数名:getListId
     */
    int getListId() {
        return listId;
    }
    
    /*
     *  @函数名:getTreeNode
     */
    TreeNode * getTreeNode() {
        return node;
    }
    
    /*
     *  @函数名:getKeyCell
     */
    TreeNodeKeyCell * getKeyCell() {
        if (node == NULL) {
            return NULL;
        }
        return node -> keyList[listId];
    }
    
public:
    ///普通函数
    /*
     *  @函数名:next
     */
    void next() {
        if (nodeId == -1 || listId == -1) {
            return;
        }
        if (listId < (int) node -> keyList.size() - 1) {
            listId ++;
            return;
        } 
        nodeId = node -> pageHeader -> getNextPageId();
        if (nodeId == -1) {
            listId = -1;
            delete node;
            node = NULL;
            return;
        } else {
            listId = 0;
            delete node;
            node = new TreeNode(oneFileManager, nodeId);
        }
    }
    
    /*
     *  @函数名:isEnd()
     *  功能:返回迭代器是否指向空
     */
    bool isEnd() {
        return nodeId == -1 || listId == -1;
    }
    
    friend class TreeIndex;
};


#endif // TREE_ITERATOR_H_
