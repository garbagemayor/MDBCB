#ifndef TABLE_ITERATOR_H_
#define TABLE_ITERATOR_H_

#include "../Page/TablePage.h"

class TableIterator {
    
public:
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
    ///���ظ���
    /*
     *  @������:next
     */
    void next() {
        //std::cout << "TableIterator.next() pageId = " << pageId << ", slotId = " << slotId
        //<< ", slotCnt = " << page -> getPageHeader() -> getSlotCnt() << std::endl;
        if (pageId == -1 || slotId == -1) {
            //std::cout << "TableIterator.next() flag 1" << std::endl;
            return;
        } else if (slotId + 1 < page -> getPageHeader() -> getSlotCnt()) {
            //std::cout << "TableIterator.next() flag 2" << std::endl;
            delete tableRow;
            tableRow = NULL;
            slotId ++;
            tableRow = new TableRow(tableHeader, page -> getSlot(slotId));
            //std::cout << "TableIterator.next() flag 2'" << std::endl;
            return;
        } else {
            //std::cout << "TableIterator.next() flag 3" << std::endl;
            delete tableRow;
            tableRow = NULL;
            while (true) {
                //std::cout << "TableIterator.next() flag 4" << std::endl;
                delete page;
                page = NULL;
                //std::cout << "TableIterator.next() flag 5" << std::endl;
                pageId ++;
                if (pageId == oneFileManager -> getPageCount()) {
                    pageId = -1;
                    slotId = -1;
                    return;
                }
                page = new TablePage(oneFileManager, pageId);
                if (page -> getPageHeader() -> getSlotCnt() > 0) {
                    slotId = 0;
                    tableRow = new TableRow(tableHeader, page -> getSlot(slotId));
                    return;
                }
            }
        }
    }
    
    /*
     *  @������:getTableRow
     */
    TableRow * getTableRow() {
        return tableRow;
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
