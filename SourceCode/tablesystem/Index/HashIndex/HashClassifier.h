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
 *  Hash索引的分类器，根据计算出来的Hash值，获取桶的页链表的首页编号
 *  默认HASH_MODP = 1997个桶，就很优雅
 */
class HashClassifier {
    
private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //页头
    TablePageHeader * pageHeader;
    //当前页编号
    int curPageId;
    //当前页的数据指针
    ByteBufType curPageData;
    //桶列表
    std::vector<int> bucketList;
    
public:
    /*
     *  @构造函数
     *  功能:创建一个分类器，没有数据
     */
    HashClassifier(OneFileManager * oneFileManager_) {
        //空指针报错
        if (oneFileManager_ == NULL) {
            std::cout << "HashClassifier(...) error" << std::endl;
            return;
        }
        //开新页，写页头
        oneFileManager = oneFileManager_;
        curPageData = oneFileManager -> getNewPage(curPageId);
        pageHeader = new TablePageHeader(curPageId);
        pageHeader -> setOneFileManager(oneFileManager);
        pageHeader -> setPageData(curPageData);
        pageHeader -> setIndexId(IndexStructure::in_hashIndex);
        pageHeader -> writeBackToBuffer();
        //桶列表
        bucketList.resize(HASH_MODP);
        for (int i = 0; i < HASH_MODP; i ++) {
            bucketList[i] = -1;
        }
    }
    
    /*
     *  @构造函数
     *  功能:读取一个分类器
     */
    HashClassifier(OneFileManager * oneFileManager_, int curPageId_) {
        //空指针报错
        if (oneFileManager_ == NULL) {
            std::cout << "HashClassifier(...) error" << std::endl;
            return;
        }
        //打开这一页
        oneFileManager = oneFileManager_;
        curPageId = curPageId_;
        curPageData = oneFileManager -> getPage(curPageId);
        //读取页头和桶列表
        readFromByte();
    }
    
    /*
     *  @析构函数
     */
    ~HashClassifier() {
        //写回页头和桶列表
        writeBackToFile();
        //清理内存
        delete pageHeader;
        bucketList.clear();
    }
    
public:
    ///基本get函数
    
    
public:
    ///基本set函数
    
    
public:
    ///普通函数
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    /*
     *  @函数名:writeBackToFile
     *  功能:把页头和桶列表的信息写回到单文件管理器
     */
    void writeBackToFile() {
        //写回页头
        pageHeader -> writeBackToBuffer();
        //写回桶列表
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
     *  @函数名:readFromByte
     *  功能:从二进制数据中读取页头和桶列表的信息
     */
    void readFromByte() {
        //已有页头报错
        if (pageHeader != NULL) {
            std::cout << "HashClassifier.readFromByte() error" << std::endl;
            return;
        }
        //读取页头
        pageHeader = new TablePageHeader(oneFileManager, curPageData);
        //读取子节点列表
        ByteBufType curBuf = curPageData + PAGE_HEADER_SIZE;
        int slotLen = readByteToNumber(curBuf, 2);
        int bucketCnt = readByteToNumber(curBuf, 2);
        bucketList.clear();
        bucketList.resize(bucketCnt);
        for (int i = 0; i < bucketCnt; i ++) {
            bucketList[i] = readByteToNumber(curBuf, 4);
        }
        //长度纠错
        if (curBuf - (curPageData + PAGE_HEADER_SIZE) != slotLen) {
            std::cout << "HashClassifier.readFromByte() error" << std::endl;
            return;
        }
    }
    
    friend class HashIndex;
    friend class HashIterator;
};

#endif // HASH_CLASSIFIER_H
