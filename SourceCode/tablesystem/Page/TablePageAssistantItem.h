#ifndef TABLE_PAGE_ASSISTANT_ITEM_H
#define TABLE_PAGE_ASSISTANT_ITEM_H

#include "../../filesystem/ByteBufBase.h"
#include "../../filesystem/OneFileManager.h"
#include "TablePage.h"

/**
 *  ��ҳ���ֵ�ÿһҳ�������ҳ����ʹ��
 *  �洢��ʽ��slotLen(2B) assiOffset(4B) ...(assiSize*2B)
 */
class TablePageAssistantItem {
    
private:
    //���ļ�������
    OneFileManager * oneFileManager;
    //��һҳ��ҳ������
    TablePage * curPage;
    //ƫ����
    int assiOffset;
    //�������ǳ��ȵ�һ��
    int assiSize;
    //ƫ�����洢����������
    ByteBufType assiData;
    
public:
    /*
     *  @���캯��
     *  @����oneFileManager:���ļ�������
     *  ����:������һ������ҳ��ռ�ݱ�ĵ�0ҳ������ʣ��ռ�
    TablePageAssistantItem(TablePage * curPage_) {
        //��ָ�뱨��
        if (curPage_ == NULL) {
            std::cout << "TablePageAssistantItem(NULL) error 1" << std::endl;
            return;
        }
        //������Ϣ��
        oneFileManager = curPage -> getOneFileManager();
        curPage = curPage_;
        curPage -> markDirty();
        assiOffset = 0;
        int assiSlotLen = curPage -> getPageHeader() -> getFreeCnt() - 2;
        assiSize = (assiSlotLen - 6) / 2;
        //ҳ�е�����
        int assiSlotId = curPage -> createSlot(assiSlotLen);
        assiData = curPage -> getSlot(assiSlotId);
        memset(assiData, 0, sizeof(Byte) * assiSlotLen);
        ByteBufType assiData_ = assiData;
        writeNumberToByte(assiData_, 2, assiSlotLen);
        writeNumberToByte(assiData_, 4, assiOffset);
    }
     */
    
    /*
     *  @���캯��
     *  @lastAssistant:��һ������ҳ
     *  ����:������һ������ҳ
     */
    TablePageAssistantItem(TablePageAssistantItem * lastAssistant) {
        //��ָ�뱨��
        if (lastAssistant == NULL) {
            std::cout << "TablePageAssistantItem(NULL) error 2" << std::endl;
            return;
        }
        //������Ϣ������һ������ҳ���������������ҳ��ҳͷ��������
        oneFileManager = lastAssistant -> oneFileManager;
        curPage = new TablePage(oneFileManager);
        lastAssistant -> curPage -> markDirty();
        curPage -> markDirty();
        lastAssistant -> curPage -> getPageHeader() -> setNextPageId(curPage -> getPageId());
        curPage -> getPageHeader() -> setPrevPageId(lastAssistant -> curPage -> getPageId());
        assiOffset = lastAssistant -> assiOffset + lastAssistant -> assiSize;
        int assiSlotLen = curPage -> getPageHeader() -> getFreeCnt() - 2;
        assiSize = (assiSlotLen - 6) / 2;
        //ҳ�е�����
        int assiSlotId = curPage -> createSlot(assiSlotLen);
        assiData = curPage -> getSlot(assiSlotId);
        memset(assiData, 0, sizeof(Byte) * assiSlotLen);
        ByteBufType assiData_ = assiData;
        writeNumberToByte(assiData_, 2, assiSlotLen);
        writeNumberToByte(assiData_, 4, assiOffset);
    }
    
    /*
     *  @���캯��
     *  @����oneFileManager_:���ļ�������
     *  @����pageId_:ҳ���
     *  ����:������0ҳ������ҳ�����߶�ȡ��pageId_ҳ������ҳ
     */
    TablePageAssistantItem(OneFileManager * oneFileManager_, int pageId_) {
        //��ָ�뱨��
        if (oneFileManager_ == NULL) {
            std::cout << "TablePageAssistantItem(NULL) error 3" << std::endl;
            return;
        }
        //������Ϣ������һ������ҳ���������������ҳ��ҳͷ��������
        oneFileManager = oneFileManager_;
        curPage = new TablePage(oneFileManager, pageId_);
        if (pageId_ == 0 && curPage -> getPageHeader() -> getFreeCnt() > 6) {
            //��0ҳû�н�������ҳ���֣����ڵ�0ҳ�½�����
            curPage -> markDirty();
            assiOffset = 0;
            int assiSlotLen = curPage -> getPageHeader() -> getFreeCnt() - 2;
            assiSize = (assiSlotLen - 6) / 2;
            int assiSlotId = curPage -> createSlot(assiSlotLen);
            assiData = curPage -> getSlot(assiSlotId);
            memset(assiData, 0, sizeof(Byte) * assiSlotLen);
            ByteBufType assiData_ = assiData;
            writeNumberToByte(assiData_, 2, assiSlotLen);
            writeNumberToByte(assiData_, 4, assiOffset);
        } else {
            //��һҳ�Ѿ���������ҳ���֣��Ͷ�ȡ����
            int assiSlotId = pageId_ == 0 ? 1 : 0;
            assiData = curPage -> getSlot(assiSlotId);
            ByteBufType assiData_ = assiData;
            int assiSlotLen = readByteToNumber(assiData_, 2);
            assiOffset = readByteToNumber(assiData_, 4);
            assiSize = (assiSlotLen - 6) / 2;
        }
    }
    
    ~TablePageAssistantItem() {
        delete curPage;
    }
    
public:
    ///����get����
    /*
     *  @������:getPageId
     *  ����:��������������ڵ�ҳ���
     */
    int getPageId() {
        return curPage -> getPageId();
    }
    
    /*
     *  @������:getAssiBegin
     *  ����:����������ֹ������ʼҳ���
     */
    int getAssiBegin() {
        return assiOffset;
    }
    
    /*
     *  @������:getAssiEnd
     *  ����:����������ֹ�������һҳ����һҳ���
     */
    int getAssiEnd() {
        return assiOffset + assiSize;
    }
    
    /*
     *  @������:getFreeCnt
     *  @����pageId:��ѯ��ҳ���
     *  ����:��ѯһҳ�Ŀ��пռ䣬�鲻���ͱ�������-1
     */
    int getFreeCnt(int pageId) {
        //�鲻������
        if (pageId < assiOffset || assiOffset + assiSize <= pageId) {
            std::cout << "TablePageAssistantItem.getFreeCnt(" << pageId << ") error" << std::endl;
            return -1;
        }
        //��ѯ
        ByteBufType tmpBuf = assiData + 6 + (pageId - assiOffset);
        int tmpCnt = readByteToNumber(tmpBuf, 2);
        return tmpCnt;
    }
    
    /*
     *  @������:getNextPageId
     *  ����:��ѯ��һ�����ֵ�ҳ���
     */
    int getNextPageId() {
        return curPage -> getPageHeader() -> getNextPageId(); 
    }
    
public:
    ///����set����
    /*
     *  @������:setFreeCnt
     *  @����pageId:�޸ĵ�ҳ���
     *  @����pageFreeCnt:�޸ĺ�Ŀ��пռ�
     *  ����:�޸�һҳ�Ŀ��пռ䣬�����޸ľͱ���������޸ĺ��ֵ
     */
    void setFreeCnt(int pageId, int pageFreeCnt) {
        //�鲻������
        if (pageId < assiOffset || assiOffset + assiSize <= pageId) {
            std::cout << "TablePageAssistantItem.setFreeCnt(" << pageId << ", " << pageFreeCnt << ") error" << std::endl;
            return ;
        }
        //�޸�
        curPage -> markDirty();
        ByteBufType tmpBuf = assiData + 6 + (pageId - assiOffset);
        writeNumberToByte(tmpBuf, 2, pageFreeCnt);
    }
    
    friend class TablePageAssistant;
};

#endif // TABLE_PAGE_ASSISTANT_ITEM_H
