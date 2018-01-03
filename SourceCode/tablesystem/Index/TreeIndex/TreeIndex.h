#ifndef TREE_INDEX_H_
#define TREE_INDEX_H_

#include "../BaseIndex.h"
#include "TreeNodeKeyCell.h"
#include "TreeNode.h"
#include "TreeIterator.h"

#include <string>
#include <vector>
#include <iostream>

/**
 *  B+树索引，从索引基类继承，由索引管理器IndexManager来管理。
 *  对节点的记录都使用页编号，第0页是根节点。
 *  叶节点链表用nextPageId构成单向链表，-1表示边界。
 *  把第0页的页头的freeCnt值作为B+树叶节点链表的，因为不会用到这个值。
 */
class TreeIndex 
    : public BaseIndex {
    
protected:
    //根节点编号
    static const int rootPageId = 0;
    //键值比较函数的指针
    bool (* cmpKeyValue) (uint64, uint64);
    
public:
    /*
     *  @构造函数
     *  功能:读取或创建一个B+树索引
     *       先调用BaseIndex的构造函数，然后记录基本信息
     */
    TreeIndex(BufPageManager * bufPageManager_, std::string tableName_, TableColumn * tableColumn_)
        : BaseIndex(bufPageManager_, tableName_, tableColumn_) {
        //空指针报错
        if (bufPageManager_ == NULL || tableColumn_ == NULL) {
            std::cout << "TreeIndex(..., " << tableName_ << ", ...) error" << std::endl;
            return;
        }
        //变长类型报错
        if (tableColumn_ -> hasVariableLength()) {
            std::cout << "TreeIndex(..., " << tableName_ << ", ...) error" << std::endl;
            return;
        }
        //设置基本信息
        indexStructure = IndexStructure::in_treeIndex;
        cmpKeyValue = cmpFunctionList[tableColumn -> getDataType()];
        //如果是新建索引，就创建一个根节点，里面没有数据
        if (oneFileManager -> getPageCnt() == 0) {
            TreeNode * node0 = new TreeNode(oneFileManager);
            node0 -> pageHeader -> setNextPageId(-1);
            node0 -> pageHeader -> setFreeCnt(0);
            node0 -> pageHeader -> setLevel(0);
            node0 -> writeBackToFile();
            delete node0;
        }
    }
    
    /*
     *  @析构函数
     */
    ~TreeIndex() {
    }
    
public:
    ///基本get函数
    
    
    
public:
    
    
    
public:
    ///普通函数
    /*
     *  @函数名:insertKey
     *  @参数keyCell:要插入的键值
     *  功能:插入一个键值，这个值会被复制之后再插入，复制时会把sonPageId设为0
     *       如果表中有同一个键值，且来源于数据表的同一页同一个槽，就不添加
     */
    void insertKey(TreeNodeKeyCell * keyCell) {
        if (!containKey(keyCell)) {
            TreeNodeKeyCell * keyCell_ = new TreeNodeKeyCell();
            keyCell_ -> replaceKey(keyCell);
            __insertKey(keyCell_);
        }
    }
    
    /*
     *  @函数名:eraseKey
     *  @参数keyCell:要删除的键值
     *  功能:删除一个键值，先复制这个值再清理掉，因为在删除过程中它可能会发生变化
     *       如果表中没有这个键值（数值、页编号、槽编号都相同），就什么都不做
     */
    void eraseKey(TreeNodeKeyCell * keyCell) {
        if (containKey(keyCell)) {
            TreeNodeKeyCell * keyCell_ = new TreeNodeKeyCell();
            keyCell_ -> replaceKey(keyCell);
            __eraseKey(keyCell_);
            delete keyCell_;
        }
    }
    
    /*
     *  @函数名:containKey
     *  @参数keyCell:要查询的键值
     *  功能:查询表中是否包含这个键值，
     */
    bool containKey(TreeNodeKeyCell * keyCell) {
        TreeIterator ite = __findKey(keyCell);
        return ite.nodeId != -1 && ite.listId != -1;
    }
    
    /*
     *  @函数名:findKey
     *  @参数keyCell:要查询的键值
     *  功能:查询表中是否包含这个键值，返回一个迭代器
     */
    TreeIterator findKey(TreeNodeKeyCell * keyCell) {
        return __findKey(keyCell);
    }
    
    /*
     *  @函数名:begin
     *  功能:返回叶节点链表第一个节点的第一个键值的迭代器
     */
    TreeIterator beginIte() {
        TreeNode * node0 = new TreeNode(oneFileManager, rootPageId);
        TreeIterator ite;
        if (node0 -> isLeaf() && node0 -> keyList.size() == 0) {
            ite = TreeIterator(oneFileManager, -1, -1);
        } else {
            ite = TreeIterator(oneFileManager, node0 -> pageHeader -> getFreeCnt(), 0);
        }
        delete node0;
        return ite;
    }
    
    /*
     *  @函数名:end
     *  功能:返回一个指向空的迭代器
     */
    TreeIterator endIte() {
        return TreeIterator(oneFileManager, -1, -1);
    }
    
protected:
    ///补充函数
    /*
     *  @函数名:__insertKey
     *  @参数keyCell:待插入的键值
     *  功能:非递归的插入一个键值，不复制直接插入
     *       利用一个节点栈，先向下到达叶子节点，再逐层向上分三种情况处理
     */
    void __insertKey(TreeNodeKeyCell * keyCell) {
        //节点栈
        std::vector<TreeNode *> myStack;
        myStack.clear();
        //向下直达叶子节点
        TreeNode * nodeCur = new TreeNode(oneFileManager, rootPageId);
        while (!nodeCur -> isLeaf()) {
            int s;
            for (s = (int) nodeCur -> keyList.size() - 1; s >= 0; s --) {
                if (s == 0 || nodeCur -> keyList[s] -> isLessThan(keyCell, cmpKeyValue)) {
                    break;
                }
            }
            myStack.push_back(nodeCur);
            nodeCur = new TreeNode(oneFileManager, nodeCur -> keyList[s] -> sonPageId);
        }
        //自底向上添加
        while (true) {
            if (nodeCur -> keyList.size() < MAX_SON_NUM) {
                //添加之后不会溢出
                //直接添加然后退出循环
                nodeCur -> insertKey(keyCell, cmpKeyValue);
                break;
            } else if (!nodeCur -> isRoot()) {
                //直接插入后会溢出且不是根节点
                //先分裂一个新节点，把数据搬进去
                TreeNode * nodeBro = new TreeNode(oneFileManager);
                TreeNode * nodePar = myStack[myStack.size() - 1];
                nodeBro -> pageHeader -> setLevel(nodeCur -> pageHeader -> getLevel());
                nodeCur -> splitKeyList(nodeBro, MIN_SON_NUM);
                //两个节点中选一个，把待添加的键值加入进去
                if (keyCell -> isLessThan(nodeBro -> keyList[0], cmpKeyValue)) {
                    nodeCur -> insertKey(keyCell, cmpKeyValue);
                    //如果加进去之后恰好是第0个，就要替换掉祖先中的键值
                    if (keyCell -> isEqualTo(nodeCur -> keyList[0])) {
                        for (int s = (int) myStack.size() - 1; s >= 0; s --) {
                            if (myStack[s] -> containKey(nodeCur -> keyList[1])) {
                                myStack[s] -> replaceKey(nodeCur -> keyList[1], keyCell);
                            } else {
                                break;
                            }
                        }
                    }
                } else {
                    nodeBro -> insertKey(keyCell, cmpKeyValue);
                }
                //如果nodeCur叶子节点，还要改叶节点链表
                if (nodeCur -> isLeaf()) {
                    nodeBro -> pageHeader -> setNextPageId(nodeCur -> pageHeader -> getNextPageId());
                    nodeCur -> pageHeader -> setNextPageId(nodeBro -> curPageId);
                }
                //清理并准备下一轮循环
                keyCell -> replaceKey(nodeBro -> keyList[0]);
                keyCell -> replaceSon(nodeBro -> curPageId);
                delete nodeBro;
                delete nodeCur;
                nodeCur = nodePar;
                myStack.pop_back();
            } else {
                //根节点且会溢出
                //先分裂两个新节点，把数据搬进去
                TreeNode * nodeA = new TreeNode(oneFileManager);
                TreeNode * nodeB = new TreeNode(oneFileManager);
                nodeA -> pageHeader -> setLevel(nodeCur -> pageHeader -> getLevel());
                nodeB -> pageHeader -> setLevel(nodeCur -> pageHeader -> getLevel());
                nodeCur -> pageHeader -> setLevel(nodeCur -> pageHeader -> getLevel() + 1);
                nodeCur -> splitKeyList(nodeB, MIN_SON_NUM);
                nodeCur -> splitKeyList(nodeA, MIN_SON_NUM);
                //两个节点中选一个，把待添加的键值加进去
                if (keyCell -> isLessThan(nodeB -> keyList[0], cmpKeyValue)) {
                    nodeA -> insertKey(keyCell, cmpKeyValue);
                } else {
                    nodeB -> insertKey(keyCell, cmpKeyValue);
                }
                //然后还要把nodeA和nodeB都加到nodeCur的子节点列表里面
                TreeNodeKeyCell * keyCellA = new TreeNodeKeyCell(nodeA -> keyList[0]);
                nodeCur -> insertKey(keyCellA, cmpKeyValue);
                nodeCur -> keyList[0] -> replaceSon(nodeA -> curPageId);
                TreeNodeKeyCell * keyCellB = new TreeNodeKeyCell(nodeB -> keyList[0]);
                nodeCur -> insertKey(keyCellB, cmpKeyValue);
                nodeCur -> keyList[1] -> replaceSon(nodeB -> curPageId);
                //如果nodeCur是叶节点，还要改叶节点链表
                if (nodeA -> isLeaf()) {
                    nodeCur -> pageHeader -> setFreeCnt(nodeA -> curPageId);
                    nodeA -> pageHeader -> setNextPageId(nodeB -> curPageId);
                    nodeB -> pageHeader -> setNextPageId(-1);
                }
                //清理并退出循环
                delete nodeA;
                delete nodeB;
                delete nodeCur;
                break;
            }
        }
        //清理栈
        for (int i = 0; i < (int) myStack.size(); i ++) {
            delete myStack[i];
        }
        myStack.clear();
    }
    
    /*
     *  @函数名:__eraseKey
     *  @参数keyCell:待删除的键值
     *  功能:非递归的删除一个键值
     *       利用一个节点栈，先向下到达叶子节点，再逐层向上分三种情况处理
     */
    void __eraseKey(TreeNodeKeyCell * keyCell) {
        //节点栈
        std::vector<TreeNode *> myStack;
        myStack.clear();
        //向下直达叶子节点
        TreeNode * nodeCur = new TreeNode(oneFileManager, rootPageId);
        while (!nodeCur -> isLeaf()) {
            int s;
            for (s = (int) nodeCur -> keyList.size() - 1; s >= 0; s --) {
                if (s == 0 || nodeCur -> keyList[s] -> isLessThan(keyCell, cmpKeyValue)) {
                    break;
                }
            }
            myStack.push_back(nodeCur);
            nodeCur = new TreeNode(oneFileManager, nodeCur -> keyList[s] -> sonPageId);
        }
        //自底向上删除
        while (true) {
            if (!nodeCur -> isRoot() && nodeCur -> keyList.size() > MIN_SON_NUM) {
                //不是根节点，且删除之后不会萎靡
                //直接删，如果恰好是第0个键值还要改祖先
                nodeCur -> eraseKey(keyCell);
                if (nodeCur -> keyList[0] -> isEqualTo(keyCell)) {
                    for (int s = (int) myStack.size(); s >= 0; s --) {
                        if (myStack[s] -> containKey(keyCell)) {
                            myStack[s] -> replaceKey(keyCell, nodeCur -> keyList[0]);
                        } else {
                            break;
                        }
                    }
                }
            } else if (!nodeCur -> isRoot()) {
                //不是根节点，且删除之后会萎靡
                //获取右兄弟
                TreeNode * nodePar = myStack[myStack.size() - 1];
                TreeNode * nodeBro = NULL;
                int t;
                for (t = 0; t < (int) nodePar -> keyList.size(); t ++) {
                    if (nodePar -> keyList[t] -> isEqualTo(nodeCur -> keyList[0])) {
                        break;
                    }
                }
                if (t + 1 < (int) nodePar -> keyList.size()) {
                    nodeBro = new TreeNode(oneFileManager, nodePar -> keyList[t + 1] -> sonPageId);
                }
                if (nodeBro != NULL) {
                    //如果有右兄弟
                    if (nodeBro -> keyList.size() > MIN_SON_NUM) {
                        //且右兄弟转移一个键值之后不会萎靡
                        //先转移一个键值，只有父亲节点需要替换，祖先不需要
                        nodePar -> replaceKey(nodeBro -> keyList[0], nodeBro -> keyList[1]);
                        nodeCur -> keyList.push_back(nodeBro -> keyList[0]);
                        for (int s = 1; s < (int) nodeBro -> keyList.size(); s ++) {
                            nodeBro -> keyList[s - 1] = nodeBro -> keyList[s];
                        }
                        //然后直接删除，如果恰好是第0个键值还要改祖先
                        nodeCur -> eraseKey(keyCell);
                        if (nodeCur -> keyList[0] -> isEqualTo(keyCell)) {
                            for (int s = (int) myStack.size() - 1; s >= 0; s --) {
                                if (myStack[s] -> containKey(keyCell)) {
                                    myStack[s] -> replaceKey(keyCell, nodeCur -> keyList[0]);
                                } else {
                                    break;
                                }
                            }
                        }
                        //清理并退出循环
                        delete nodeBro;
                        delete nodeCur;
                        break;
                    } else {
                        //且右兄弟转移一个键值之后也会萎靡
                        //先复制右兄弟的第0个键值，下轮循环用
                        TreeNodeKeyCell * keyCellNew = new TreeNodeKeyCell(nodeBro -> keyList[0]);
                        //先把右兄弟的键值全部拿过来
                        for (int s = 0; s < (int) nodeBro -> keyList.size(); s ++) {
                            nodeCur -> keyList.push_back(nodeBro -> keyList[s]);
                        }
                        nodeBro -> keyList.clear();
                        //然后直接删除，如果恰好是第0个键值还要改祖先
                        nodeCur -> eraseKey(keyCell);
                        if (nodeCur -> keyList[0] -> isEqualTo(keyCell)) {
                            for (int s = (int) myStack.size() - 1; s >= 0; s --) {
                                if (myStack[s] -> containKey(keyCell)) {
                                    myStack[s] -> replaceKey(keyCell, nodeCur -> keyList[0]);
                                } else {
                                    break;
                                }
                            }
                        }
                        //如果是叶节点，还要改叶节点链表
                        if (nodeCur -> pageHeader -> getLevel() == 0) {
                            nodeCur -> pageHeader -> setNextPageId(nodeBro -> pageHeader -> getNextPageId());
                            nodeBro -> pageHeader -> setNextPageId(-1);
                        }
                        //清理并准备下一轮循环
                        keyCell -> replaceKey(keyCellNew);
                        delete keyCellNew;
                        delete nodeBro;
                        delete nodeCur;
                        nodeCur = nodePar;
                        myStack.pop_back();
                    }
                } else {
                    //如果没有右兄弟，就一定有左兄弟，获取左兄弟
                    nodeBro = new TreeNode(oneFileManager, nodePar -> keyList[t - 1] -> sonPageId);
                    if (nodeBro -> keyList.size() > MIN_SON_NUM) {
                        //且左兄弟转移一个键值之后不会萎靡
                        //先转移一个键值，只有父亲需要替换，祖先不需要
                        nodeCur -> keyList.push_back(NULL);
                        for (int s = nodeCur -> keyList.size() - 1; s >= 1; s --) {
                            nodeCur -> keyList[s] = nodeCur -> keyList[s - 1];
                        }
                        nodeCur -> keyList[0] = nodeBro -> keyList[nodeBro -> keyList.size() - 1];
                        nodeBro -> keyList.pop_back();
                        //然后直接删除，显然不可能恰好是第0个键值
                        nodeBro -> eraseKey(keyCell);
                        //清理并退出循环
                        delete nodeBro;
                        delete nodeCur;
                        break;
                    } else {
                        //且左兄弟转移一个键值之后也会萎靡
                        //先复制当前节点的第0个键值，下轮循环用
                        TreeNodeKeyCell * keyCellNew = new TreeNodeKeyCell(nodeCur -> keyList[0]);
                        //先把当前节点的键值全部添加到左兄弟去
                        for (int s = 0; s < (int) nodeCur -> keyList.size(); s ++) {
                            nodeBro -> keyList.push_back(nodeCur -> keyList[s]);
                        }
                        nodeCur -> keyList.clear();
                        //然后直接删除，显然不会改祖先
                        nodeBro -> eraseKey(keyCell);
                        //如果是叶节点，还要改叶节点链表
                        if (nodeCur -> pageHeader -> getLevel() == 0) {
                            nodeBro -> pageHeader -> setNextPageId(nodeCur -> pageHeader -> getNextPageId());
                            nodeCur -> pageHeader -> setNextPageId(-1);
                        }
                        //清理并准备下一轮循环
                        keyCell -> replaceKey(keyCellNew);
                        delete keyCellNew;
                        delete nodeBro;
                        delete nodeCur;
                        nodeCur = nodePar;
                        myStack.pop_back();
                    }
                }
            } else {
                //是根节点，啥也不管先直接删
                nodeCur -> eraseKey(keyCell);
                if (nodeCur -> isLeaf() || nodeCur -> keyList.size() >= 2) {
                    //且根节点就是叶节点，或者，且根节点删除之后还没萎靡
                    //清理并退出循环
                    delete nodeCur;
                    break;
                } else {
                    //且根节点不是叶节点，且根节点删除之后已经萎靡
                    //找到删除后根节点唯一的一个子节点，把根节点情况
                    TreeNode * nodeSon = new TreeNode(oneFileManager, nodeCur -> keyList[0] -> sonPageId);
                    delete nodeCur -> keyList[0];
                    nodeCur -> keyList.clear();
                    //把子节点的全部键值都搬过来
                    for (int s = 0; s < (int) nodeSon -> keyList.size(); s ++) {
                        nodeCur -> keyList.push_back(nodeSon -> keyList[s]);
                    }
                    nodeCur -> keyList.clear();
                    //重新计算根节点的参数（level, nextPageId, freeCnt）
                    nodeCur -> pageHeader -> setLevel(nodeSon -> pageHeader -> getLevel());
                    if (nodeCur -> isLeaf()) {
                        nodeCur -> pageHeader -> setFreeCnt(nodeCur -> curPageId);
                        nodeCur -> pageHeader -> setNextPageId(nodeSon -> pageHeader -> getNextPageId());
                    }
                    //清理并退出循环
                    delete nodeSon;
                    delete nodeCur;
                    break;
                }
            }
        }
        //清理栈
        for (int s = 0; s < (int) myStack.size(); s ++) {
            delete myStack[s];
        }
        myStack.clear();
    }
    
    /*
     *  @函数名:__findKey
     *  @参数keyCell:查询的键值
     *  功能:非递归的查询是否包含一个键值，返回一个迭代器，指向这个数据在叶节点中所在的位置
     */
    TreeIterator __findKey(TreeNodeKeyCell * keyCell) {
        TreeNode * nodeCur = new TreeNode(oneFileManager, rootPageId);
        TreeNode * nodeTmp;
        int s;
        //向下逐层查询
        while (true) {
            for (s = (int) nodeCur -> keyList.size() - 1; s >= 0; s --) {
                if (!nodeCur -> keyList[s] -> isGreaterThan(keyCell, cmpKeyValue)) {
                    break;
                }
            }
            if (nodeCur -> isLeaf()) {
                break;
            }
            //向下一层
            nodeTmp = new TreeNode(oneFileManager, nodeCur -> keyList[s] -> sonPageId);
            delete nodeCur;
            nodeCur = nodeTmp;
        }
        if (nodeCur -> keyList[s] -> isEqualTo(keyCell)) {
            return TreeIterator(oneFileManager, nodeCur -> curPageId, s);
        } else {
            return TreeIterator();
        }
    }
};

#endif // TREE_INDEX_H_
