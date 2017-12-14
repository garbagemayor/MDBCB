#include <iostream>

#include "../../filesystem/PageFPI.h"
#include "../../filesystem/bufmanager/BufPageManager.h"

/*
 *  һ���ڵ�����ļ�ϵͳ��һ��page��
 */
template <typename KeyType>
class TreeNodeBase {

    //��Ԫ��
    friend class Tree;

protected:
    //ҳʽ�ļ�ϵͳ������
    BufPageManager * pageManager;
    //����ڵ���ҳʽ�ļ�ϵͳ�����page
    PageFPI fpi;
    //�ڵ���������������sizeof(KeyType)�������

protected:
    int nMax;
    //�ڵ㵱ǰ����
    int n;
    //��ֵ�б������С��nMax����Ч��Χ��n
    KeyType * key;
    //���ڵ�
    PageFPI fath;

public:
    //�鹹�캯��
    virtual TreeNodeBase(BufPageManager * pageManager, int pageId) {
        fpi.fileId = 
    }

    //����������
    virtual ~TreeNodeVase() = 0;
    
public:
};

/*
 *  ��Ҷ�ӽڵ㡣
 */
template <typename KeyType>
class TreeNode
    : public TreeNodeBase <KeyType> {

protected:
    //�ӽڵ��б������С��nMax+1����Ч��Χ��n+1
    PageFPI * son;

public:
    TreeNode() {

    }




};

/*
 *  Ҷ�ӽڵ㡣
 */
template <typename KeyType>
class TreeLeaf
    : public TreeNodeBase <KeyType> {

protected:
    //�б������С��nMax����Ч��Χ��n
    PageFPI * son;


};
