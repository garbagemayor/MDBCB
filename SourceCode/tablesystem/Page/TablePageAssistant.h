#ifndef TABLE_PAGE_ASSISTANT_H
#define TABLE_PAGE_ASSISTANT_H

#include "../../filesystem/ByteBufBase.h"
#include "../../filesystem/OneFileManager.h"
#include "TablePage.h"
#include "TablePageAssistantItem.h"

#include <vector>

/**
 *  表页助手，用表文件的一些页集中存放每一页的空闲字节数，便于插入时跳转到恰当的页面
 *  从第0页开始，不够用之后再开新的页
 */
class TablePageAssistant {
    
private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //助手页列表
    std::vector<TablePageAssistantItem *> assiList;
    //当前的最大容量
    int capacity;
    
public:
    /*
     *  @构造函数
     *  功能:创建一个表页助手，读取或创建第0页的表页助手起始位置
     */
    TablePageAssistant(OneFileManager * oneFileManager_) {
        oneFileManager = oneFileManager_;
        TablePageAssistantItem * assiItem = new TablePageAssistantItem(oneFileManager, 0);
        assiList.clear();
        assiList.push_back(assiItem);
        capacity = assiItem -> getAssiEnd();
    }
    
    ~TablePageAssistant() {
        for (int i = 0; i < (int) assiList.size(); i ++) {
            delete assiList[i];
        }
        assiList.clear();
    }
    
public:
    ///基本get函数
    /*
     *  @函数名:getFreeCnt
     *  @参数pageId:页编号
     *  功能:获取一页的空闲字节数，如果页编号超出范围就报错并返回-1
     */
    int getFreeCnt(int pageId) {
        //页编号超出范围报错
        if (pageId < 0 || pageId >= oneFileManager -> getPageCnt()) {
            std::cout << "TablePageAssistant.getFreeCnt(" << pageId << ") error" << std::endl;
            return -1;
        }
        //自动的找助手页，知道范围达标
        while (capacity <= pageId) {
            __getNextAssiItem();
        }
        for (int i = 0; i < (int) assiList.size(); i ++) {
            if (assiList[i] -> getAssiBegin() <= pageId && pageId < assiList[i] -> getAssiEnd()) {
                return assiList[i] -> getFreeCnt(pageId);
            }
        }
        //找不到报错
        if (true) {
            std::cout << "TablePageAssistant.getFreeCnt(" << pageId << ") error" << std::endl;
            return -1;
        }
    }
    
public:
    ///基本set函数
    /*
     *  @函数名:setFreeCnt
     *  功能:设置某一页的空闲字节数吗，如果页编号超出范围就报错
     */
    void setFreeCnt(int pageId, int pageFreeCnt) {
        //页编号超出范围报错
        if (pageId < 0 || pageId >= oneFileManager -> getPageCnt()) {
            std::cout << "TablePageAssistant.setFreeCnt(" << pageId << ", " << pageFreeCnt << ") error" << std::endl;
            return;
        }
        //自动的找助手页，知道范围达标
        while (capacity <= pageId) {
            __getNextAssiItem();
        }
        for (int i = 0; i < (int) assiList.size(); i ++) {
            if (assiList[i] -> getAssiBegin() <= pageId && pageId < assiList[i] -> getAssiEnd()) {
                assiList[i] -> setFreeCnt(pageId, pageFreeCnt);
                return;
            }
        }
        //找不到报错
        if (true) {
            std::cout << "TablePageAssistant.setFreeCnt(" << pageId << ", " << pageFreeCnt << ") error" << std::endl;
            return;
        }
    }
    
    /*
     *  @函数名:findPageForSlot
     *  @参数slotLen:新槽的长度
     *  功能:给新槽找一个合适的页面，返回页编号
     */
    int findPageForSlot(int slotLen) {
        for (int i = 1; i < oneFileManager -> getPageCnt() ; i ++) {
            if (getFreeCnt(i) >= slotLen + 2) {
                return i;
            }
        }
        return oneFileManager -> getPageCnt();
    }
    
private:
    ///普通函数
    /*
     *  @函数名:__getNextAssiItem
     *  功能:读取或创建下一个助手页
     */
    void __getNextAssiItem(){
        int nextAssistantPageId = assiList[assiList.size() - 1] -> getNextPageId();
        if (nextAssistantPageId == -1) {
            //文件中没有下一个助手页，自己创建一个
            TablePageAssistantItem * assiItem = new TablePageAssistantItem(assiList[assiList.size() - 1]);
            assiList.push_back(assiItem);
            capacity = assiItem -> getAssiEnd();
            this -> setFreeCnt(assiItem -> getPageId(), 0);
        } else {
            //文件中已经有下一个助手页，读取
            TablePageAssistantItem * assiItem = new TablePageAssistantItem(oneFileManager, nextAssistantPageId);
            assiList.push_back(assiItem);
            capacity = assiItem -> getAssiEnd();
        }
    }
};

#endif // TABLE_PAGE_ASSISTANT_H
