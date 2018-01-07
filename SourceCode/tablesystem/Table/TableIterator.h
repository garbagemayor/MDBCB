#ifndef TABLE_ITERATOR_H_
#define TABLE_ITERATOR_H_

#include "../Page/TablePage.h"

class TableIterator {
    
public:
    //单文件管理器
    OneFileManager * oneFileManager;
    //表头
    TableHeader * tableHeader;
    //页编号
    int pageId;
    //槽编号
    int slotId;
    //表页
    TablePage * page;
    //表行
    TableRow * tableRow;
    
public:
    /*
     *  @构造函数
     *  功能:创建一个指向空的迭代器
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
     *  @构造函数
     *  功能:创建一个正常的迭代器
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
     *  @拷贝构造函数
     */
    TableIterator(const TableIterator & ite) {
        * this = ite;
    }
    
    /*
     *  @重载等号赋值
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
    ///重载负号
    /*
     *  @函数名:next
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
     *  @函数名:getTableRow
     */
    TableRow * getTableRow() {
        return tableRow;
    }
    
    /*
     *  @函数名:isEnd()
     *  功能:返回迭代器是否指向空
     */
    bool isEnd() {
        return pageId == -1 || slotId == -1;
    }
    
    friend class Table;
};

#endif // TABLE_ITERATOR_H_
