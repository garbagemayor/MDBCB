#ifndef TABLE_PAGE_ASSISTANT_H
#define TABLE_PAGE_ASSISTANT_H

#include "../../filesystem/ByteBufBase.h"
#include "../../filesystem/OneFileManager.h"
#include "TablePage.h"
#include "TablePageAssistantItem.h"

#include <vector>

/**
 *  ��ҳ���֣��ñ��ļ���һЩҳ���д��ÿһҳ�Ŀ����ֽ��������ڲ���ʱ��ת��ǡ����ҳ��
 *  �ӵ�0ҳ��ʼ��������֮���ٿ��µ�ҳ
 */
class TablePageAssistant {
    
private:
    //���ļ�������
    OneFileManager * oneFileManager;
    //����ҳ�б�
    std::vector<TablePageAssistantItem *> assiList;
    //��ǰ���������
    int capacity;
    
public:
    /*
     *  @���캯��
     *  ����:����һ����ҳ���֣���ȡ�򴴽���0ҳ�ı�ҳ������ʼλ��
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
    ///����get����
    /*
     *  @������:getFreeCnt
     *  @����pageId:ҳ���
     *  ����:��ȡһҳ�Ŀ����ֽ��������ҳ��ų�����Χ�ͱ�������-1
     */
    int getFreeCnt(int pageId) {
        //ҳ��ų�����Χ����
        if (pageId < 0 || pageId >= oneFileManager -> getPageCnt()) {
            std::cout << "TablePageAssistant.getFreeCnt(" << pageId << ") error" << std::endl;
            return -1;
        }
        //�Զ���������ҳ��֪����Χ���
        while (capacity <= pageId) {
            __getNextAssiItem();
        }
        for (int i = 0; i < (int) assiList.size(); i ++) {
            if (assiList[i] -> getAssiBegin() <= pageId && pageId < assiList[i] -> getAssiEnd()) {
                return assiList[i] -> getFreeCnt(pageId);
            }
        }
        //�Ҳ�������
        if (true) {
            std::cout << "TablePageAssistant.getFreeCnt(" << pageId << ") error" << std::endl;
            return -1;
        }
    }
    
public:
    ///����set����
    /*
     *  @������:setFreeCnt
     *  ����:����ĳһҳ�Ŀ����ֽ��������ҳ��ų�����Χ�ͱ���
     */
    void setFreeCnt(int pageId, int pageFreeCnt) {
        //ҳ��ų�����Χ����
        if (pageId < 0 || pageId >= oneFileManager -> getPageCnt()) {
            std::cout << "TablePageAssistant.setFreeCnt(" << pageId << ", " << pageFreeCnt << ") error" << std::endl;
            return;
        }
        //�Զ���������ҳ��֪����Χ���
        while (capacity <= pageId) {
            __getNextAssiItem();
        }
        for (int i = 0; i < (int) assiList.size(); i ++) {
            if (assiList[i] -> getAssiBegin() <= pageId && pageId < assiList[i] -> getAssiEnd()) {
                assiList[i] -> setFreeCnt(pageId, pageFreeCnt);
                return;
            }
        }
        //�Ҳ�������
        if (true) {
            std::cout << "TablePageAssistant.setFreeCnt(" << pageId << ", " << pageFreeCnt << ") error" << std::endl;
            return;
        }
    }
    
    /*
     *  @������:findPageForSlot
     *  @����slotLen:�²۵ĳ���
     *  ����:���²���һ�����ʵ�ҳ�棬����ҳ���
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
    ///��ͨ����
    /*
     *  @������:__getNextAssiItem
     *  ����:��ȡ�򴴽���һ������ҳ
     */
    void __getNextAssiItem(){
        int nextAssistantPageId = assiList[assiList.size() - 1] -> getNextPageId();
        if (nextAssistantPageId == -1) {
            //�ļ���û����һ������ҳ���Լ�����һ��
            TablePageAssistantItem * assiItem = new TablePageAssistantItem(assiList[assiList.size() - 1]);
            assiList.push_back(assiItem);
            capacity = assiItem -> getAssiEnd();
            this -> setFreeCnt(assiItem -> getPageId(), 0);
        } else {
            //�ļ����Ѿ�����һ������ҳ����ȡ
            TablePageAssistantItem * assiItem = new TablePageAssistantItem(oneFileManager, nextAssistantPageId);
            assiList.push_back(assiItem);
            capacity = assiItem -> getAssiEnd();
        }
    }
};

#endif // TABLE_PAGE_ASSISTANT_H
