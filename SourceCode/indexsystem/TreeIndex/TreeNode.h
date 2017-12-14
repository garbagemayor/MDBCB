#include <iostream>

#include "../../filesystem/PageFPI.h"
#include "../../filesystem/bufmanager/BufPageManager.h"

/*
 *  一个节点就是文件系统的一个page。
 */
template <typename KeyType>
class TreeNodeBase {

    //友元类
    friend class Tree;

protected:
    //页式文件系统管理器
    BufPageManager * pageManager;
    //这个节点在页式文件系统里面的page
    PageFPI fpi;
    //节点的最大容量，根据sizeof(KeyType)计算出来

protected:
    int nMax;
    //节点当前容量
    int n;
    //键值列表，数组大小是nMax，有效范围是n
    KeyType * key;
    //父节点
    PageFPI fath;

public:
    //虚构造函数
    virtual TreeNodeBase(BufPageManager * pageManager, int pageId) {
        fpi.fileId = 
    }

    //虚析构函数
    virtual ~TreeNodeVase() = 0;
    
public:
};

/*
 *  非叶子节点。
 */
template <typename KeyType>
class TreeNode
    : public TreeNodeBase <KeyType> {

protected:
    //子节点列表，数组大小是nMax+1，有效范围是n+1
    PageFPI * son;

public:
    TreeNode() {

    }




};

/*
 *  叶子节点。
 */
template <typename KeyType>
class TreeLeaf
    : public TreeNodeBase <KeyType> {

protected:
    //列表，数组大小是nMax，有效范围是n
    PageFPI * son;


};
