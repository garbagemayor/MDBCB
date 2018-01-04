#ifndef HASH_BUCKET_H
#define HASH_BUCKET_H

#include "../../../filesystem/ByteBufBase.h"
#include "../../../filesystem/OneFileManager.h"
#include "../../../filesystem/bufmanager/BufPageManager.h"
#include "../../Page/TablePageHeader.h"
#include "../IndexStructure.h"

#include <iostream>
#include <string>
#include <vector>

/**
 *  Hash������Ͱҳ
 */
class HashBucket {
    
private:
    //���ļ�������
    OneFileManager * oneFileManager;
    //ҳͷ
    TablePageHeader * pageHeader;
    //��ǰҳ���
    int curPageId;
    //��ǰҳ������ָ��
    ByteBufType curPageData;
    //��Ŀ�б�
    std::vector<HashKeyCell *> keyList;
    
public:
    /*
     *  @���캯��
     *  ����:����һ��Ͱҳ��û������
     */
    HashBucket(OneFileManager * oneFileManager_) {
        //��ָ�뱨��
        if (oneFileManager_ == NULL) {
            std::cout << "HashBucket(...) error" << std::endl;
            return;
        }
        //����ҳ��дҳͷ
        oneFileManager = oneFileManager_;
        curPageData = oneFileManager -> getNewPage(curPageId);
        pageHeader = new TablePageHeader(curPageId);
        pageHeader -> setOneFileManager(oneFileManager_);
        pageHeader -> setPageData(curPageData);
        pageHeader -> setIndexId(IndexStructure::in_hashIndex);
        pageHeader -> writeBackToBuffer();
        //��Ŀ��Ϣ
        keyList.clear();
    }
    
    /*
     *  @���캯��
     *  ����:��ȡһ��Ͱҳ
     */
    HashBucket(OneFileManager * oneFileManager_, int curPageId_) {
        //��ָ�뱨��
        if (oneFileManager_ == NULL) {
            std::cout << "HashBucket(...) error" << std::endl;
            return;
        }
        //����һҳ����ȡҳͷ
        oneFileManager = oneFileManager_;
        curPageId = curPageId_;
        curPageData = oneFileManager -> getPage(curPageId);
        //��ȡҳͷ���ӽڵ��б�
        readFromByte();
    }

    /*
     *  @��������
     */
    ~HashBucket() {
        //д��ҳͷ���ӽڵ��б�
        writeBackToFile();
        //�����ڴ�
        delete pageHeader;
        for (int i = 0; i < (int) keyList.size(); i ++) {
            delete keyList[i];
        }
        keyList.clear();
    }

public:
    ///��ͨ����
    /*
     *  @������:insertKey
     *  ����:����һ����ֵ��������ֱ�Ӳ���
     */
    void insertKey(HashKeyCell * keyCell) {
        //����ӽڵ���������
        if ((int) keyList.size() == MAX_BUCKET_SIZE) {
            std::cout << "HashBucket.insertKey(...) error" << std::endl;
            return;
        }
        //ĩβ����
        keyList.push_back(keyCell);
    }
    
    /*
     *  @������:eraseKey
     *  ����:ɾ��һ����ֵ��ֱ�������
     */
    void eraseKey(HashKeyCell * keyCell) {
        //�ҳ���
        int s;
        for (s = 0; s < (int) keyList.size(); s ++) {
            if (keyList[s] -> isEqualTo(keyCell)) {
                break;
            }
        }
        //�Ҳ�������
        if (s == (int) keyList.size()) {
            std::cout << "HashBucket.eraseKey(...) error" << std::endl;
            return;
        }
        //ɾ���������һ���������
        delete keyList[s];
        keyList[s] = keyList.back();
        keyList.pop_back();
    }
    
    /*
     *  @������:containKey
     *  ����:��ѯ�Ƿ���������ֵ
     */
    bool containKey(HashKeyCell * keyCell) {
        for (int s = 0; s < (int) keyList.size(); s ++) {
            if (keyList[s] -> isEqualTo(keyCell)) {
                return true;
            }
        }
        return false;
    }
    
    /*
     *  @������:writeBackToFile
     *  ����:��ҳͷ���ӽڵ��б����Ϣд�ص����ļ�������
     */
    void writeBackToFile() {
        //д��ҳͷ
        pageHeader -> writeBackToBuffer();
        //д���ӽڵ��б�
        ByteBufType curBuf = curPageData + PAGE_HEADER_SIZE;
        int keyCnt = keyList.size();
        int slotLen = 4 + 16 * keyCnt;
        writeNumberToByte(curBuf, 2, slotLen);
        writeNumberToByte(curBuf, 2, keyCnt);
        for (int i = 0; i < keyCnt; i ++) {
            keyList[i] -> writeAsByte(curBuf);
        }
    }
    
    /*
     *  @������:readFromByte
     *  ����:�Ӷ����������ж�ȡҳͷ���ӽڵ��б����Ϣ
     */
    void readFromByte() {
        //����ҳͷ����
        if (pageHeader != NULL) {
            std::cout << "HashBucket.readFromByte() error" << std::endl;
            return;
        }
        //��ȡҳͷ
        pageHeader = new TablePageHeader(oneFileManager, curPageData);
        //��ȡ�ӽڵ��б�
        ByteBufType curBuf = curPageData + PAGE_HEADER_SIZE;
        int slotLen = readByteToNumber(curBuf, 2);
        int keyCnt = readByteToNumber(curBuf, 2);
        keyList.clear();
        keyList.resize(keyCnt);
        for (int i = 0; i < keyCnt; i ++) {
            keyList[i] = new HashKeyCell();
            keyList[i] -> readFromByte(curBuf);
        }
        //���Ⱦ���
        if (curBuf - (curPageData + PAGE_HEADER_SIZE) != slotLen) {
            std::cout << "HashBucket.readFromByte() error" << std::endl;
            return;
        }
    }
    
    friend class HashIndex;
    friend class HashIterator;
};

#endif // HASH_BUCKET_H
