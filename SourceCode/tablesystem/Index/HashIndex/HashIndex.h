#ifndef HASH_INDEX_H
#define HASH_INDEX_H

#include "../BaseIndex.h"
#include "HashKeyCell.h"
#include "HashClassifier.h"
#include "HashBucket.h"
#include "HashIterator.h"

#include <string>
#include <vector>
#include <iostream>

/**
 *  Hash索引，从索引基类继承，由索引管理器IndexManager来管理。
 *  第0页是分类器，记录每个键值第一个桶的页编号的组合。
 *  后面每页都是桶链表，记录更详细的东西。
 *  每个桶页的页头的level记录这个桶共有的Hash值。
 */

class HashIndex
    : public BaseIndex {
    
protected:
    //分类器编号
    static const int classifierPageId = 0;
    
public:
    /*
     *  @构造函数
     *  功能:读取或创建一个Hash索引
     *       先调用BaseIndex的构造函数，然后记录基本信息
     */
    HashIndex(BufPageManager * bufPageManager_, std::string tableName_, TableColumn * tableColumn_)
        : BaseIndex(bufPageManager_, tableName_, tableColumn_) {
        //空指针报错
        if (bufPageManager_ == NULL || tableColumn_ == NULL) {
            std::cout << "HashIndex(..., " << tableName_ << ", ...) error" << std::endl;
            return;
        }
        //设置基本信息
        indexStructure = IndexStructure::in_hashIndex;
        //如果是新建索引，就创建分类器节点，里面没有数据
        if (oneFileManager -> getPageCnt() == 0) {
            HashClassifier * classifier = new HashClassifier(oneFileManager);
            classifier -> pageHeader -> setNextPageId(-1);
            classifier -> pageHeader -> setFreeCnt(0);
            classifier -> writeBackToFile();
            delete classifier;
        }
    }
    
    /*
     *  @析构函数
     */
    ~HashIndex() {
        
    }

public:
    ///基本get函数
    
public:
    ///基本set函数
    
public:
    ///普通函数
    /*
     *  @函数名:insertKey
     *  @参数keyCell:要插入的键值
     *  功能:插入一个键值，这个键值会被复制之后再插入
     *       如果表中有同一个键值，且键值位于同一页同一槽，就不添加
     */
    void insertKey(HashKeyCell * keyCell) {
        if (!containKey(keyCell)) {
            HashKeyCell * keyCell_ = new HashKeyCell(keyCell);
            __insertKey(keyCell_);
        }
    }
    
    /*
     *  @函数名:eraseKey
     *  @参数keyCell:要删除的键值
     *  功能:删除一个键值，先复制这个值再清理掉，因为在删除过程中它可能会发生变化
     *       如果表中没有这个键值（数值、页编号、槽编号都相同），就什么都不做
     */
    void eraseKey(HashKeyCell * keyCell) {
        if (containKey(keyCell)) {
            HashKeyCell * keyCell_ = new HashKeyCell();
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
    bool containKey(HashKeyCell * keyCell) {
        HashIterator ite = __findKey(keyCell);
        return ite.bucketId != -1 && ite.listId != -1;
    }
    
    /*
     *  @函数名:findKey
     *  @参数keyCell:要查询的键值
     *  功能:查询表中是否包含这个键值，返回一个迭代器
     */
    HashIterator findKey(HashKeyCell * keyCell) {
        return __findKey(keyCell);
    }
    
    /*
     *  @函数名:begin
     *  功能:返回叶节点链表第一个节点的第一个键值的迭代器
     */
    HashIterator beginIte() {
        return HashIterator::lowerBoundFromKey(oneFileManager, 0);
    }
    
    /*
     *  @函数名:end
     *  功能:返回一个指向空的迭代器
     */
    HashIterator endIte() {
        return HashIterator(oneFileManager, -1, -1);
    }
    
protected:
    ///补充函数
    /*
     *  @函数名:__insertKey
     *  @参数keyCell:要插入的条目
     *  功能:插入
     */
    void __insertKey(HashKeyCell * keyCell) {
        HashClassifier * classifier = new HashClassifier(oneFileManager, 0);
        HashBucket * curBucket = NULL;
        //获取这个Hash值的第一个桶页
        if (classifier -> bucketList[keyCell -> key] == -1) {
            curBucket = new HashBucket(oneFileManager);
            curBucket -> pageHeader -> setPrevPageId(-1);
            curBucket -> pageHeader -> setLevel(keyCell -> key);
            curBucket -> pageHeader -> writeBackToBuffer();
            classifier -> bucketList[keyCell -> key] = curBucket -> curPageId;
        } else {
            curBucket = new HashBucket(oneFileManager, classifier -> bucketList[keyCell -> key]);
        }
        delete classifier;
        //如果满了就下一个桶页
        while ((int) curBucket -> keyList.size() == MAX_BUCKET_SIZE) {
            HashBucket * nextBucket = NULL;
            if (curBucket -> pageHeader -> getNextPageId() == -1) {
                nextBucket = new HashBucket(oneFileManager);
                nextBucket -> pageHeader -> setPrevPageId(curBucket -> curPageId);
                nextBucket -> pageHeader -> setLevel(keyCell -> key);
                nextBucket -> pageHeader -> writeBackToBuffer();
                curBucket -> pageHeader -> setNextPageId(nextBucket -> curPageId);
            } else {
                nextBucket = new HashBucket(oneFileManager, curBucket -> pageHeader -> getNextPageId());
            }
            delete curBucket;
            curBucket = nextBucket;
        }
        //在当前页添加这个条目
        curBucket -> insertKey(keyCell);
        delete curBucket;
    }
    
    /*
     *  @函数名:__eraseKey
     *  @参数keyCell:要删除的条目
     *  功能:如果存在就删除
     */
    void __eraseKey(HashKeyCell * keyCell) {
        HashClassifier * classifier = new HashClassifier(oneFileManager, 0);
        HashBucket * curBucket = NULL;
        //获取这个Hash值的第一个桶页
        if (classifier -> bucketList[keyCell -> key] == -1) {
            delete classifier;
            return;
        } else {
            curBucket = new HashBucket(oneFileManager, classifier -> bucketList[keyCell -> key]);
        }
        delete classifier;
        //如果不存在就下一个桶页
        while (!curBucket -> containKey(keyCell)) {
            HashBucket * nextBucket = NULL;
            if (curBucket -> pageHeader -> getNextPageId() == -1) {
                delete curBucket;
                return;
            } else {
                nextBucket = new HashBucket(oneFileManager, curBucket -> pageHeader -> getNextPageId());
            }
            delete curBucket;
            curBucket = nextBucket;
        }
        //在当前页删除这个条目
        curBucket -> eraseKey(keyCell);
        delete curBucket;
    }
    
    /*
     *  @函数名:__findKey
     *  @参数keyCell:查询的键值
     *  功能:非递归的查询是否包含一个键值，返回一个迭代器，指向这个数据在叶节点中所在的位置
     */
    HashIterator __findKey(HashKeyCell * keyCell) {
        HashClassifier * classifier = new HashClassifier(oneFileManager, 0);
        HashBucket * curBucket = NULL;
        //获取这个Hash值的第一个桶页
        if (classifier -> bucketList[keyCell -> key] == -1) {
            delete classifier;
            return HashIterator();
        } else {
            curBucket = new HashBucket(oneFileManager, classifier -> bucketList[keyCell -> key]);
        }
        delete classifier;
        //如果不存在就下一个桶页
        int listId;
        while (true) {
            listId = curBucket -> containKey(keyCell);
            if (listId != -1) {
                break;
            }
            HashBucket * nextBucket = NULL;
            if (curBucket -> pageHeader -> getNextPageId() == -1) {
                delete curBucket;
                return HashIterator();
            } else {
                nextBucket = new HashBucket(oneFileManager, curBucket -> pageHeader -> getNextPageId());
            }
            delete curBucket;
            curBucket = nextBucket;
        }
        //在当前页删除这个条目
        HashIterator ite(oneFileManager, curBucket -> curPageId, listId);
        delete curBucket;
        return ite;
    }
};

#endif // HASH_INDEX_H
