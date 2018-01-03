#ifndef HASH_ITERATOR_H
#define HASH_ITERATOR_H

#include "HashClassifier.h"
#include "HashBucket.h"

class HashIterator {
    
private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //所在桶页的编号
    int bucketId;
    //节点中的序号
    int listId;
    //节点
    HashBucket * bucket;
    
public:
    /*
     *  @构造函数
     *  功能:创建一个指向空的迭代器
     */
    HashIterator() {
        oneFileManager = NULL;
        bucketId = -1;
        listId = -1;
        bucket = NULL;
    }
    
    /*
     *  @构造函数
     *  功能:创建一个正常的迭代器
     */
    HashIterator( OneFileManager * oneFileManager_, int bucketId_, int listId_) {
        oneFileManager = oneFileManager_;
        bucketId = bucketId_;
        listId = listId_;
        bucket = new HashBucket(oneFileManager, bucketId);
    }
    
    /*
     *  @构造函数
     *  功能:拷贝
     */
    HashIterator(const HashIterator & ite) {
        bucketId = ite.bucketId;
        listId = ite.listId;
        bucket = new HashBucket(oneFileManager, bucketId);
    }
    
    /*
     *  @析构函数
     */
    ~HashIterator() {
        if (bucket != NULL) {
            delete bucket;
        }
    }

public:
    ///重载符号
    /*
     *  ++ ite
     */
    HashIterator & operator ++ () {
        ///TODO
        return *this;
    }
    
    /*
     *  ite ++
     */
    HashIterator operator ++ (int) {
        HashIterator iteTmp(* this);
        ++ (* this);
        return iteTmp;
        
    }
    
public:
    ///普通函数
    /*
     *  @函数名:lowerBoundFromKey
     *  功能:找到Hash值不小于hashKey的第一个非空桶中的第0个条目，返回它的迭代器
     */
    static HashIterator lowerBoundFromKey(OneFileManager * oneFileManager, int hashKey) {
        HashClassifier * classifier = new HashClassifier(oneFileManager, 0);
        HashBucket * curBucket = NULL;
        for (; hashKey < HASH_MODP; hashKey ++) {
            if (classifier -> bucketList[hashKey] != -1) {
                curBucket = new HashBucket(oneFileManager, classifier -> bucketList[hashKey]);
                while ((int) curBucket -> keyList.size() == 0) {
                    int nextPageId = curBucket -> pageHeader -> getNextPageId();
                    if (nextPageId == -1) {
                        delete curBucket;
                        curBucket = NULL;
                        break;
                    } else {
                        HashBucket * bucketTmp = new HashBucket(oneFileManager, nextPageId);
                        delete curBucket;
                        curBucket = bucketTmp;
                    }
                }
                if (curBucket != NULL) {
                    HashIterator ite(oneFileManager, curBucket -> curPageId, 0);
                    delete curBucket;
                    return ite;
                }
            }
        }
        return HashIterator(oneFileManager, -1, -1);
    }
    
    friend class HashIndex;
};

#endif // HASH_ITERATOR_H
