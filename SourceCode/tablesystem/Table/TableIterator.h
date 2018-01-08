#ifndef TABLE_ITERATOR_H_
#define TABLE_ITERATOR_H_

#include "../Page/TablePage.h"

class TableIterator {
    
private:
    //���ļ�������
    OneFileManager * oneFileManager;
    //��ͷ
    TableHeader * tableHeader;
    //ҳ���
    int pageId;
    //�۱��
    int slotId;
    //��ҳ
    TablePage * page;
    //����
    TableRow * tableRow;
    
public:
    /*
     *  @���캯��
     *  ����:����һ��ָ��յĵ�����
     */
    TableIterator() {
        //std::cout << "TableIterator()" << std::endl;
        oneFileManager = NULL;
        tableHeader = NULL;
        pageId = -1;
        slotId = -1;
        page = NULL;
        tableRow = NULL;
    }
    
    /*
     *  @���캯��
     *  ����:����һ�������ĵ�����
     */
    TableIterator(OneFileManager * oneFileManager_, TableHeader * tableHeader_, int pageId_, int slotId_) {
        //std::cout << "TableIterator(...) pageId = " << pageId_ << ", slotId = " << slotId_ << std::endl;
        oneFileManager = oneFileManager_;
        tableHeader = tableHeader_;
        pageId = pageId_;
        slotId = slotId_;
        page = new TablePage(oneFileManager, pageId);
        tableRow = new TableRow(tableHeader, page -> getSlot(slotId));
    }
    
    /*
     *  @�������캯��
     */
    TableIterator(const TableIterator & ite) {
        * this = ite;
    }
    
    /*
     *  @���صȺŸ�ֵ
     */
    TableIterator & operator = (const TableIterator & ite) {
        oneFileManager = ite.oneFileManager;
        tableHeader = ite.tableHeader;
        pageId = ite.pageId;
        slotId = ite.slotId;
        page = new TablePage(oneFileManager, pageId);
        tableRow = new TableRow(tableHeader, page -> getSlot(slotId));
        return *this;
    }
    
    ~TableIterator() {
        //std::cout << "~TableIterator()" << std::endl;
        if (tableRow != NULL) {
            delete tableRow;
            tableRow = NULL;
        }
        if (page != NULL) {
            delete page;
            page = NULL;
        }
    }
    
public:
    ///����get����
    /*
     *  @������:getPageId
     */
    int getPageId() {
        return pageId;
    }
    
    /*
     *  @������:getSlotId
     */
    int getSlotId() {
        return slotId;
    }
    
    /*
     *  @������:getTableRow
     */
    TableRow * getTableRow() {
        return tableRow;
    }
    
public:
    ///��ͨ����
    /*
     *  @������:next
     */
    void next() {
        //std::cout << "TableIterator.next() pageId = " << pageId << ", slotId = " << slotId
        //<< ", slotCnt = " << page -> getPageHeader() -> getSlotCnt() << std::endl;
        if (pageId == -1 || slotId == -1) {
            //std::cout << "TableIterator.next() flag 1" << std::endl;
            return;
        }
        delete tableRow;
        tableRow = NULL;
        slotId = page -> getNextSlotId(slotId);
        if (slotId != -1) {
            tableRow = new TableRow(tableHeader, page -> getSlot(slotId));
            return;
        }
        while (true) {
            delete page;
            page = NULL;
            pageId ++;
            if (pageId >= oneFileManager -> getPageCount()) {
                pageId = -1;
                slotId = -1;
                return;
            }
            page = new TablePage(oneFileManager, pageId);
            if (page -> getPageHeader() -> getObjId() == 2) {
                continue;
            }
            slotId = page -> getNextSlotId(-1);
            if (slotId != -1) {
                tableRow = new TableRow(tableHeader, page -> getSlot(slotId));
                return;
            }
        }
    }
    
    /*
     *  @������:isEnd()
     *  ����:���ص������Ƿ�ָ���
     */
    bool isEnd() {
        return pageId == -1 || slotId == -1;
    }
    
    friend class Table;
};

#endif // TABLE_ITERATOR_H_
