#ifndef HASH_ITERATOR_H
#define HASH_ITERATOR_H

#include "HashClassifier.h"
#include "HashBucket.h"

class HashIterator {
    
private:
    //���ļ�������
    OneFileManager * oneFileManager;
    //����Ͱҳ�ı��
    int bucketId;
    //�ڵ��е����
    int listId;
    //�ڵ�
    HashBucket * bucket;
    
public:
    /*
     *  @���캯��
     *  ����:����һ��ָ��յĵ�����
     */
    HashIterator() {
        oneFileManager = NULL;
        bucketId = -1;
        listId = -1;
        bucket = NULL;
    }
    
    /*
     *  @���캯��
     *  ����:����һ�������ĵ�����
     */
    HashIterator( OneFileManager * oneFileManager_, int bucketId_, int listId_) {
        oneFileManager = oneFileManager_;
        bucketId = bucketId_;
        listId = listId_;
        bucket = new HashBucket(oneFileManager, bucketId);
    }
    
    /*
     *  @���캯��
     *  ����:����
     */
    HashIterator(const HashIterator & ite) {
        bucketId = ite.bucketId;
        listId = ite.listId;
        bucket = new HashBucket(oneFileManager, bucketId);
    }
    
    /*
     *  @��������
     */
    ~HashIterator() {
        if (bucket != NULL) {
            delete bucket;
        }
    }

public:
    ///���ط���
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
    ///��ͨ����
    /*
     *  @������:lowerBoundFromKey
     *  ����:�ҵ�Hashֵ��С��hashKey�ĵ�һ���ǿ�Ͱ�еĵ�0����Ŀ���������ĵ�����
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
