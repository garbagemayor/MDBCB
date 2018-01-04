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
 *  Hash索引的桶页
 */
class HashBucket {
    
private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //页头
    TablePageHeader * pageHeader;
    //当前页编号
    int curPageId;
    //当前页的数据指针
    ByteBufType curPageData;
    //条目列表
    std::vector<HashKeyCell *> keyList;
    
public:
    /*
     *  @构造函数
     *  功能:创建一个桶页，没有数据
     */
    HashBucket(OneFileManager * oneFileManager_) {
        //空指针报错
        if (oneFileManager_ == NULL) {
            std::cout << "HashBucket(...) error" << std::endl;
            return;
        }
        //开新页，写页头
        oneFileManager = oneFileManager_;
        curPageData = oneFileManager -> getNewPage(curPageId);
        pageHeader = new TablePageHeader(curPageId);
        pageHeader -> setOneFileManager(oneFileManager_);
        pageHeader -> setPageData(curPageData);
        pageHeader -> setIndexId(IndexStructure::in_hashIndex);
        pageHeader -> writeBackToBuffer();
        //条目信息
        keyList.clear();
    }
    
    /*
     *  @构造函数
     *  功能:读取一个桶页
     */
    HashBucket(OneFileManager * oneFileManager_, int curPageId_) {
        //空指针报错
        if (oneFileManager_ == NULL) {
            std::cout << "HashBucket(...) error" << std::endl;
            return;
        }
        //打开这一页，读取页头
        oneFileManager = oneFileManager_;
        curPageId = curPageId_;
        curPageData = oneFileManager -> getPage(curPageId);
        //读取页头和子节点列表
        readFromByte();
    }

    /*
     *  @析构函数
     */
    ~HashBucket() {
        //写回页头和子节点列表
        writeBackToFile();
        //清理内存
        delete pageHeader;
        for (int i = 0; i < (int) keyList.size(); i ++) {
            delete keyList[i];
        }
        keyList.clear();
    }

public:
    ///普通函数
    /*
     *  @函数名:insertKey
     *  功能:插入一个键值，不复制直接插入
     */
    void insertKey(HashKeyCell * keyCell) {
        //检查子节点数量报错
        if ((int) keyList.size() == MAX_BUCKET_SIZE) {
            std::cout << "HashBucket.insertKey(...) error" << std::endl;
            return;
        }
        //末尾插入
        keyList.push_back(keyCell);
    }
    
    /*
     *  @函数名:eraseKey
     *  功能:删除一个键值，直接清理掉
     */
    void eraseKey(HashKeyCell * keyCell) {
        //找出来
        int s;
        for (s = 0; s < (int) keyList.size(); s ++) {
            if (keyList[s] -> isEqualTo(keyCell)) {
                break;
            }
        }
        //找不到报错
        if (s == (int) keyList.size()) {
            std::cout << "HashBucket.eraseKey(...) error" << std::endl;
            return;
        }
        //删除并把最后一个补充过来
        delete keyList[s];
        keyList[s] = keyList.back();
        keyList.pop_back();
    }
    
    /*
     *  @函数名:containKey
     *  功能:查询是否包含这个键值
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
     *  @函数名:writeBackToFile
     *  功能:把页头和子节点列表的信息写回到单文件管理器
     */
    void writeBackToFile() {
        //写回页头
        pageHeader -> writeBackToBuffer();
        //写回子节点列表
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
     *  @函数名:readFromByte
     *  功能:从二进制数据中读取页头和子节点列表的信息
     */
    void readFromByte() {
        //已有页头报错
        if (pageHeader != NULL) {
            std::cout << "HashBucket.readFromByte() error" << std::endl;
            return;
        }
        //读取页头
        pageHeader = new TablePageHeader(oneFileManager, curPageData);
        //读取子节点列表
        ByteBufType curBuf = curPageData + PAGE_HEADER_SIZE;
        int slotLen = readByteToNumber(curBuf, 2);
        int keyCnt = readByteToNumber(curBuf, 2);
        keyList.clear();
        keyList.resize(keyCnt);
        for (int i = 0; i < keyCnt; i ++) {
            keyList[i] = new HashKeyCell();
            keyList[i] -> readFromByte(curBuf);
        }
        //长度纠错
        if (curBuf - (curPageData + PAGE_HEADER_SIZE) != slotLen) {
            std::cout << "HashBucket.readFromByte() error" << std::endl;
            return;
        }
    }
    
    friend class HashIndex;
    friend class HashIterator;
};

#endif // HASH_BUCKET_H
