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
 *  Hash����������������̳У�������������IndexManager������
 *  ��0ҳ�Ƿ���������¼ÿ����ֵ��һ��Ͱ��ҳ��ŵ���ϡ�
 *  ����ÿҳ����Ͱ������¼����ϸ�Ķ�����
 *  ÿ��Ͱҳ��ҳͷ��level��¼���Ͱ���е�Hashֵ��
 */

class HashIndex
    : public BaseIndex {
    
protected:
    //���������
    static const int classifierPageId = 0;
    
public:
    /*
     *  @���캯��
     *  ����:��ȡ�򴴽�һ��Hash����
     *       �ȵ���BaseIndex�Ĺ��캯����Ȼ���¼������Ϣ
     */
    HashIndex(BufPageManager * bufPageManager_, std::string tableName_, TableColumn * tableColumn_)
        : BaseIndex(bufPageManager_, tableName_, tableColumn_) {
        //��ָ�뱨��
        if (bufPageManager_ == NULL || tableColumn_ == NULL) {
            std::cout << "HashIndex(..., " << tableName_ << ", ...) error" << std::endl;
            return;
        }
        //���û�����Ϣ
        indexStructure = IndexStructure::in_hashIndex;
        //������½��������ʹ����������ڵ㣬����û������
        if (oneFileManager -> getPageCnt() == 0) {
            HashClassifier * classifier = new HashClassifier(oneFileManager);
            classifier -> pageHeader -> setNextPageId(-1);
            classifier -> pageHeader -> setFreeCnt(0);
            classifier -> writeBackToFile();
            delete classifier;
        }
    }
    
    /*
     *  @��������
     */
    ~HashIndex() {
        
    }

public:
    ///����get����
    
public:
    ///����set����
    
public:
    ///��ͨ����
    /*
     *  @������:insertKey
     *  @����keyCell:Ҫ����ļ�ֵ
     *  ����:����һ����ֵ�������ֵ�ᱻ����֮���ٲ���
     *       ���������ͬһ����ֵ���Ҽ�ֵλ��ͬһҳͬһ�ۣ��Ͳ����
     */
    void insertKey(HashKeyCell * keyCell) {
        if (!containKey(keyCell)) {
            HashKeyCell * keyCell_ = new HashKeyCell(keyCell);
            __insertKey(keyCell_);
        }
    }
    
    /*
     *  @������:eraseKey
     *  @����keyCell:Ҫɾ���ļ�ֵ
     *  ����:ɾ��һ����ֵ���ȸ������ֵ�����������Ϊ��ɾ�������������ܻᷢ���仯
     *       �������û�������ֵ����ֵ��ҳ��š��۱�Ŷ���ͬ������ʲô������
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
     *  @������:containKey
     *  @����keyCell:Ҫ��ѯ�ļ�ֵ
     *  ����:��ѯ�����Ƿ���������ֵ��
     */
    bool containKey(HashKeyCell * keyCell) {
        HashIterator ite = __findKey(keyCell);
        return ite.bucketId != -1 && ite.listId != -1;
    }
    
    /*
     *  @������:findKey
     *  @����keyCell:Ҫ��ѯ�ļ�ֵ
     *  ����:��ѯ�����Ƿ���������ֵ������һ��������
     */
    HashIterator findKey(HashKeyCell * keyCell) {
        return __findKey(keyCell);
    }
    
    /*
     *  @������:begin
     *  ����:����Ҷ�ڵ������һ���ڵ�ĵ�һ����ֵ�ĵ�����
     */
    HashIterator beginIte() {
        return HashIterator::lowerBoundFromKey(oneFileManager, 0);
    }
    
    /*
     *  @������:end
     *  ����:����һ��ָ��յĵ�����
     */
    HashIterator endIte() {
        return HashIterator(oneFileManager, -1, -1);
    }
    
protected:
    ///���亯��
    /*
     *  @������:__insertKey
     *  @����keyCell:Ҫ�������Ŀ
     *  ����:����
     */
    void __insertKey(HashKeyCell * keyCell) {
        HashClassifier * classifier = new HashClassifier(oneFileManager, 0);
        HashBucket * curBucket = NULL;
        //��ȡ���Hashֵ�ĵ�һ��Ͱҳ
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
        //������˾���һ��Ͱҳ
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
        //�ڵ�ǰҳ��������Ŀ
        curBucket -> insertKey(keyCell);
        delete curBucket;
    }
    
    /*
     *  @������:__eraseKey
     *  @����keyCell:Ҫɾ������Ŀ
     *  ����:������ھ�ɾ��
     */
    void __eraseKey(HashKeyCell * keyCell) {
        HashClassifier * classifier = new HashClassifier(oneFileManager, 0);
        HashBucket * curBucket = NULL;
        //��ȡ���Hashֵ�ĵ�һ��Ͱҳ
        if (classifier -> bucketList[keyCell -> key] == -1) {
            delete classifier;
            return;
        } else {
            curBucket = new HashBucket(oneFileManager, classifier -> bucketList[keyCell -> key]);
        }
        delete classifier;
        //��������ھ���һ��Ͱҳ
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
        //�ڵ�ǰҳɾ�������Ŀ
        curBucket -> eraseKey(keyCell);
        delete curBucket;
    }
    
    /*
     *  @������:__findKey
     *  @����keyCell:��ѯ�ļ�ֵ
     *  ����:�ǵݹ�Ĳ�ѯ�Ƿ����һ����ֵ������һ����������ָ�����������Ҷ�ڵ������ڵ�λ��
     */
    HashIterator __findKey(HashKeyCell * keyCell) {
        HashClassifier * classifier = new HashClassifier(oneFileManager, 0);
        HashBucket * curBucket = NULL;
        //��ȡ���Hashֵ�ĵ�һ��Ͱҳ
        if (classifier -> bucketList[keyCell -> key] == -1) {
            delete classifier;
            return HashIterator();
        } else {
            curBucket = new HashBucket(oneFileManager, classifier -> bucketList[keyCell -> key]);
        }
        delete classifier;
        //��������ھ���һ��Ͱҳ
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
        //�ڵ�ǰҳɾ�������Ŀ
        HashIterator ite(oneFileManager, curBucket -> curPageId, listId);
        delete curBucket;
        return ite;
    }
};

#endif // HASH_INDEX_H
