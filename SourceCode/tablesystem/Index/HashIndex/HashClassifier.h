#ifndef HASH_CLASSIFIER_H
#define HASH_CLASSIFIER_H

#include "../../../filesystem/ByteBufBase.h"
#include "../../../filesystem/OneFileManager.h"
#include "../../filesystem/bufmanager/BufPageManager.h"
#include "../../Page/TablePageHeader.h"
#include "../IndexStructure.h"

#include <iostream>
#include <string>
#include <vector>

/**
 *  Hash�����ķ����������ݼ��������Hashֵ����ȡͰ��ҳ�������ҳ���
 *  Ĭ��HASH_MODP = 1997��Ͱ���ͺ�����
 */
class HashClassifier {
    
private:
    //���ļ�������
    OneFileManager * oneFileManager;
    //ҳͷ
    TablePageHeader * pageHeader;
    //��ǰҳ���
    int curPageId;
    //��ǰҳ������ָ��
    ByteBufType curPageData;
    //Ͱ�б�
    std::vector<int> bucketList;
    
public:
    /*
     *  @���캯��
     *  ����:����һ����������û������
     */
    HashClassifier(OneFileManager * oneFileManager_) {
        //��ָ�뱨��
        if (oneFileManager_ == NULL) {
            std::cout << "HashClassifier(...) error" << std::endl;
            return;
        }
        //����ҳ��дҳͷ
        oneFileManager = oneFileManager_;
        curPageData = oneFileManager -> getNewPage(curPageId);
        pageHeader = new TablePageHeader(curPageId);
        pageHeader -> setOneFileManager(oneFileManager);
        pageHeader -> setPageData(curPageData);
        pageHeader -> setIndexId(IndexStructure::in_hashIndex);
        pageHeader -> writeBackToBuffer();
        //Ͱ�б�
        bucketList.resize(HASH_MODP);
        for (int i = 0; i < HASH_MODP; i ++) {
            bucketList[i] = -1;
        }
    }
    
    /*
     *  @���캯��
     *  ����:��ȡһ��������
     */
    HashClassifier(OneFileManager * oneFileManager_, int curPageId_) {
        //��ָ�뱨��
        if (oneFileManager_ == NULL) {
            std::cout << "HashClassifier(...) error" << std::endl;
            return;
        }
        //����һҳ
        oneFileManager = oneFileManager_;
        curPageId = curPageId_;
        curPageData = oneFileManager -> getPage(curPageId);
        //��ȡҳͷ��Ͱ�б�
        readFromByte();
    }
    
    /*
     *  @��������
     */
    ~HashClassifier() {
        //д��ҳͷ��Ͱ�б�
        writeBackToFile();
        //�����ڴ�
        delete pageHeader;
        bucketList.clear();
    }
    
public:
    ///����get����
    
    
public:
    ///����set����
    
    
public:
    ///��ͨ����
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
     *  @������:writeBackToFile
     *  ����:��ҳͷ��Ͱ�б����Ϣд�ص����ļ�������
     */
    void writeBackToFile() {
        //д��ҳͷ
        pageHeader -> writeBackToBuffer();
        //д��Ͱ�б�
        ByteBufType curBuf = curPageData + PAGE_HEADER_SIZE;
        int bucketCnt = bucketList.size();
        int slotLen = 4 + 4 * bucketCnt;
        writeNumberToByte(curBuf, 2, slotLen);
        writeNumberToByte(curBuf, 2, bucketCnt);
        for (int i = 0; i < bucketCnt; i ++) {
            writeNumberToByte(curBuf, 4, bucketList[i]);
        }
    }
    
    /*
     *  @������:readFromByte
     *  ����:�Ӷ����������ж�ȡҳͷ��Ͱ�б����Ϣ
     */
    void readFromByte() {
        //����ҳͷ����
        if (pageHeader != NULL) {
            std::cout << "HashClassifier.readFromByte() error" << std::endl;
            return;
        }
        //��ȡҳͷ
        pageHeader = new TablePageHeader(oneFileManager, curPageData);
        //��ȡ�ӽڵ��б�
        ByteBufType curBuf = curPageData + PAGE_HEADER_SIZE;
        int slotLen = readByteToNumber(curBuf, 2);
        int bucketCnt = readByteToNumber(curBuf, 2);
        bucketList.clear();
        bucketList.resize(bucketCnt);
        for (int i = 0; i < bucketCnt; i ++) {
            bucketList[i] = readByteToNumber(curBuf, 4);
        }
        //���Ⱦ���
        if (curBuf - (curPageData + PAGE_HEADER_SIZE) != slotLen) {
            std::cout << "HashClassifier.readFromByte() error" << std::endl;
            return;
        }
    }
    
    friend class HashIndex;
    friend class HashIterator;
};

#endif // HASH_CLASSIFIER_H
