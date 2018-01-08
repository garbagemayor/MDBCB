#ifndef TREE_NODE_H_
#define TREE_NODE_H_

#include "../../../filesystem/ByteBufBase.h"
#include "../../../filesystem/OneFileManager.h"
#include "../../../filesystem/bufmanager/BufPageManager.h"
#include "../../Page/TablePageHeader.h"
#include "../IndexStructure.h"
#include "TreeNodeKeyCell.h"

#include <iostream>
#include <string>
#include <vector>

/**
 *  一个节点独占一页，以页编号作为访问其他节点的依据
 *  任何数据类型都算8B，以及数据行的RID页编号4B和槽编号4B，子节点页编号4B，共20B，一个节点最多400个子节点
 *  存储方式为：slotLen(2B) keyCnt(2B) keyList(_B)，但是没有页脚
 */
class TreeNode {

private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //页头
    TablePageHeader * pageHeader;
    //当前节点的页编号
    int curPageId;
    //当前页的数据指针
    ByteBufType curPageData;
    //子节点列表
    std::vector<TreeNodeKeyCell *> keyList;

public:
    /*
     *  @构造函数
     *  功能:创建一个新的节点，没有数据
     */
    TreeNode(OneFileManager * oneFileManager_) {
        //std::cout << "TreeNode(...) begin" << std::endl;
        //空指针报错
        if (oneFileManager_ == NULL) {
            std::cout << "TreeNode(...) error" << std::endl;
            return;
        }
        //开新页，写页头
        oneFileManager = oneFileManager_;
        curPageData = oneFileManager -> getNewPage(curPageId);
        pageHeader = new TablePageHeader(curPageId);
        pageHeader -> setOneFileManager(oneFileManager);
        pageHeader -> setPageData(curPageData);
        pageHeader -> setIndexId(IndexStructure::in_treeIndex);
        pageHeader -> writeBackToBuffer();
        //子树、子节点的信息
        keyList.clear();
        //std::cout << "TreeNode(...) end" << std::endl;
    }
    
    /*
     *  @构造函数
     *  功能:读取一个节点
     */
    TreeNode(OneFileManager * oneFileManager_, int curPageId_) {
        //空指针报错
        if (oneFileManager_ == NULL) {
            std::cout << "TreeNode(...) error" << std::endl;
            return;
        }
        //打开这一页，读取页头
        oneFileManager = oneFileManager_;
        pageHeader = NULL;
        curPageId = curPageId_;
        curPageData = oneFileManager -> getPage(curPageId);
        //读取页头和子节点列表
        readFromByte();
    }

    /*
     *  @析构函数
     */
    ~TreeNode() {
        //写回页头和子节点列表
        writeBackToFile();
        //清理内存
        delete pageHeader;
        for (int i = 0; i < (int) keyList.size(); i ++) {
            delete keyList[i];
        }
        keyList.clear();
    }
    
public:
    ///基本get函数
    /*
     *  @函数名:isRoot
     *  功能:返回当前节点是否是根节点
     */
    bool isRoot() {
        return curPageId == 0;
    }
    
    /*
     *  @函数名:isLeaf
     *  功能:返回当期节点是否是叶子节点
     */
    bool isLeaf() {
        return pageHeader -> getLevel() == 0;
    }
    
    
public:
    ///基本set函数
    
    
    
public:
    ///普通函数
    /*
     *  @函数名:insertKey
     *  功能:插入一个键值，不复制直接插入
     */
    void insertKey(TreeNodeKeyCell * keyCell, bool (* cmpKeyValue) (uint64, uint64)) {
        //std::cout << "TreeNode.insertKey() curPageID = " << curPageId << ", key = " << keyCell -> key << ", size = " << keyList.size() << std::endl;
        //检查子节点数量报错
        if ((int) keyList.size() == MAX_SON_NUM) {
            std::cout << "TreeNode.insertKey(..., ...) error" << std::endl;
            return;
        }
        //右移并插入
        keyList.push_back(NULL);
        int s;
        for (s = (int) keyList.size() - 2; s >= 0; s --) {
            if (s == 0 || keyList[s] -> isLessThan(keyCell, cmpKeyValue)) {
                keyList[s + 1] = keyList[s];
            }
        }
        keyList[s + 1] = keyCell;
        //std::cout << "TreeNode.insertKey() s = " << s << std::endl;
    }
    
    /*
     *  @函数名:eraseKey
     *  功能:删除一个键值，直接清理掉
     */
    void eraseKey(TreeNodeKeyCell * keyCell) {
        //检查子节点数量报错
        if (!isRoot() && (int) keyList.size() == MIN_SON_NUM) {
            std::cout << "TreeNode.eraseKey(...) error" << std::endl;
            return;
        }
        //找出来
        int s;
        for (s = 0; s < (int) keyList.size(); s ++) {
            if (keyList[s] -> isEqualTo(keyCell)) {
                break;
            }
        }
        //找不到报错
        if (s == (int) keyList.size()) {
            std::cout << "TreeNode.eraseKey(...) error" << std::endl;
            return;
        }
        //删除并左移
        delete keyList[s];
        for (s ++; s < (int) keyList.size(); s ++) {
            keyList[s - 1] = keyList[s];
        }
        keyList.pop_back();
    }
    
    /*
     *  @函数名:containKey
     *  功能:查询是否包含这个键值
     */
    bool containKey(TreeNodeKeyCell * keyCell) {
        for (int s = 0; s < (int) keyList.size(); s ++) {
            if (keyList[s] -> isEqualTo(keyCell)) {
                return true;
            }
        }
        return false;
    }
    
    /*
     *  @函数名:replaceKey
     *  功能:替换掉键值，不替换子节点编号，不清理，不检查单调性
     */
    void replaceKey(TreeNodeKeyCell * keyCellOld, TreeNodeKeyCell * keyCellNew) {
        //找出来
        int s;
        for (s = 0; s < (int) keyList.size(); s ++) {
            if (keyList[s] -> isEqualTo(keyCellOld)) {
                break;
            }
        }
        //找不到报错
        if (s == (int) keyList.size()) {
            std::cout << "TreeNode.replaceKey(..., ...) error" << std::endl;
            return;
        }
        //替换
        keyList[s] -> replaceKey(keyCellNew);
    }
    
    /*
     *  @函数名:splitKeyList
     *  @参数nodeBro:分裂出的兄弟节点
     *  @参数nodeBroSize:分裂出的兄弟节点的子节点数量
     *  功能:（无条件）把子节点列表分成两份，添加到nodeBro里去
     */
    void splitKeyList(TreeNode * nodeBro, int nodeBroSize) {
        //检查子节点数量报错
        if (!isRoot() && (int) keyList.size() != MAX_SON_NUM) {
            std::cout << "TreeNode.splitKeyList(..., " << nodeBroSize << ") error" << std::endl;
            return;
        }
        //检查兄弟节点不为空报错
        if ((int) nodeBro -> keyList.size() != 0) {
            std::cout << "TreeNode.splitKeyList(..., " << nodeBroSize << ") error" << std::endl;
            return;
        }
        //分成两份
        int sz = (int) keyList.size();
        for (int s = sz - nodeBroSize; s < sz; s ++) {
            nodeBro -> keyList.push_back(keyList[s]);
        }
        for (int s = sz - 1; s >= sz - nodeBroSize; s --) {
            keyList.pop_back();
        }
    }
    
    /*
     *  @函数名:writeBackToFile
     *  功能:把页头和子节点列表的信息写回到单文件管理器
     */
    void writeBackToFile() {
        //std::cout << "TreeNode.writeBackToFile() begin curPageId = " << curPageId << std::endl;
        //写回页头
        pageHeader -> writeBackToBuffer();
        //写回子节点列表
        ByteBufType curBuf = curPageData + PAGE_HEADER_SIZE;
        //std::cout << "TreeNode.writeBackToFile() curBuf = " << (int) curBuf << std::endl;
        int keyCnt = keyList.size();
        int slotLen = 4 + 20 * keyCnt;
        writeNumberToByte(curBuf, 2, slotLen);
        writeNumberToByte(curBuf, 2, keyCnt);
        for (int i = 0; i < keyCnt; i ++) {
            keyList[i] -> writeAsByte(curBuf);
        }
        oneFileManager -> markDirty(curPageId);
        oneFileManager -> writeBack(curPageId);
        //std::cout << "TreeNode.writeBackToFile() end" << std::endl;
    }
    
    /*
     *  @函数名:readFromByte
     *  功能:从二进制数据中读取页头和子节点列表的信息
     */
    void readFromByte() {
        //已有页头报错
        if (pageHeader != NULL) {
            std::cout << "TreeNode.readFromByte() error 1" << std::endl;
            return;
        }
        //读取页头
        pageHeader = new TablePageHeader(oneFileManager, curPageData);
        //读取子节点列表
        ByteBufType curBuf = curPageData + PAGE_HEADER_SIZE;
        //std::cout << "TreeNode.readFromByte() begin curPageId = " << curPageId << "curBuf = " << (int) curBuf << std::endl;
        int slotLen = readByteToNumber(curBuf, 2);
        int keyCnt = readByteToNumber(curBuf, 2);
        keyList.clear();
        keyList.resize(keyCnt);
        for (int i = 0; i < keyCnt; i ++) {
            keyList[i] = new TreeNodeKeyCell();
            keyList[i] -> readFromByte(curBuf);
        }
        //长度纠错
        if (curBuf - (curPageData + PAGE_HEADER_SIZE) != slotLen) {
            std::cout << "TreeNode.readFromByte() error 2" << std::endl;
            return;
        }
        //std::cout << "TreeNode.readFromByte() end" << std::endl;
    }
    
    friend class TreeIndex;
    friend class TreeIterator;
};

#endif // TREE_NODE_H_
