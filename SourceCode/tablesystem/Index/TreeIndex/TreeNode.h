#ifndef TABLE_NODE_H_
#define TABLE_NODE_H_

#include "../../../filesystem/ByteBufBase.h"
#include "../../../filesystem/OneFileManager.h"
#include "../../filesystem/bufmanager/BufPageManager.h"
#include "../../Page/TablePageHeader.h"
#include "TreeNodeSon.h"

#include <iostream>
#include <string>
#include <vector>

/**
 *  一个节点独占一页，以页编号作为访问其他节点的依据
 *  任何数据类型都算8B，以及数据行的RID页编号4B和槽编号4B，子节点页编号4B，共20B，一个节点最多400个子节点
 */
class TreeNode {

private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //页头
    TablePageHeader * pageHeader;
    //当前节点的页编号
    int curPageId;
    //叶子节点链表中下一个节点的页编号，非叶子节点就是-1
    int nextLeaf;
    //子节点列表
    std::vector<TreeNodeSon> sonList;

public:
    /*
     *  @构造函数
     *  功能:创建一个新的节点，如果恰好是第0页就是创建一个根节点，没有数据
     */
    TreeNodeBase(OneFileManager * oneFileManager_) {
        
        
        
    }

    //析构函数
    ~TreeNodeVase() {
    }
    
public:
};


#endif // TABLE_NODE_H_
