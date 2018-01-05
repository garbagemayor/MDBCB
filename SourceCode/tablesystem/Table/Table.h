#ifndef TABLE_H_
#define TABLE_H_

#include "../../filesystem/OneFileManager.h"
#include "../Page/TablePage.h"
#include "../Page/TablePageAssistant.h"
#include "../Index/IndexManager.h"
#include "../Filter/Filter.h"
#include "../Filter/Calculator.h"
#include "TableHeader.h"
#include "TableRow.h"

#include <string>

/**
 *  单个数据表，由数据表管理器TableManager管理。
 *  一个数据表对应一个文件，由 <表名> + ".table"命名。
 *  如果是新建数据表，需要保证原本没有同名的数据表。
 *  在文件的第0页，存储表头等基本信息，不存数据。
 *  存了基本信息之后，剩下的部分存放每一页的空闲字节数，不够用就开新页
 */
class Table {
    
private:
    //单文件管理器
    OneFileManager * oneFileManager;
    //表头和表的基本信息
    TableHeader * tableHeader;
    //表页助手
    TablePageAssistant * tablePageAssistant;
    //索引管理器
    IndexManager * indexManager;
    
public:
    /*
     *  @构造函数
     *  @参数bufPageManager_:缓存页管理器
     *  @参数tableHeader_:新数据表的表头
     *  功能:新建一个数据表，要3个步骤：(1)创建第0页的页头和页脚(2)新建第0页(3)写入表头
     */
    Table(BufPageManager * bufPageManager_, TableHeader * tableHeader_) {
        //空指针报错
        if (bufPageManager_ == NULL || tableHeader_ == NULL) {
            std::cout << "Table(..., ...) error" << std::endl;
            return;
        }
        //打开文件
        std::string fileName = tableHeader_ -> getName() + ".table";
        oneFileManager = new OneFileManager(bufPageManager_, fileName.c_str());
        tableHeader = tableHeader_;
        //新建第0页，创建并写入表头
        TablePage * page0 = new TablePage(oneFileManager);
        int headerSlotId = page0 -> createSlot(tableHeader -> getSizeInSlot());
        ByteBufType headerSlot = page0 -> getSlot(headerSlotId);
        tableHeader -> writeAsByte(headerSlot);
        delete page0;
        //创建表页助手，写入内容
        tablePageAssistant = new TablePageAssistant(oneFileManager);
        //创建索引管理器（主键列、数据要互不相同的列），给这些列创建索引
        indexManager = new IndexManager(bufPageManager_, tableHeader);
    }
    
    /*
     *  @构造函数
     *  @参数bufPageManager_:缓存页管理器
     *  @参数tableName_:数据表的名字
     *  功能:打开一个原有数据表，只需要读取第0页的表头信息
     */
    Table(BufPageManager * bufPageManager_, std::string tableName_) {
        std::cout << "Table(..., " << tableName_ << ") debug" << std::endl;
        oneFileManager = new OneFileManager(bufPageManager_, (tableName_ + ".table").c_str());
        //去第0页读取表头信息
        TablePage * page0 = new TablePage(oneFileManager, 0);
        tableHeader = new TableHeader(page0 -> getSlot(0));
        delete page0;
        //创建表页助手，读取内容
        tablePageAssistant = new TablePageAssistant(oneFileManager);
        //创建索引管理器读取这些索引
        indexManager = new IndexManager(bufPageManager_, tableHeader);
    }
    
    /*
     *  @析构函数
     *  功能:写回并关掉文件
     */
    ~Table() {
        delete oneFileManager;
        delete tablePageAssistant;
    }
    
public:
    ///基本get函数
    /*
     *  @函数名:getOneFileManager
     *  功能:获取数据表的单文件管理器
     */
    OneFileManager * getOneFileManager() {
        return oneFileManager;
    }
    
    /*
     *  @函数名:getTableHeader
     *  功能:获取数据表的表头
     */
    TableHeader * getTableHeader() {
        return tableHeader;
    }
    
    /*
     *  @函数名:getName
     *  功能:获取数据表名称
     */
    std::string getName() {
        return tableHeader -> getName();
    }
    
    /*
     *  @函数名:getNCol
     *  功能:获取数据表列数
     */
    int getNCol() {
        return tableHeader -> getNCol();
    }
    
    /*
     *  @函数名:getNRow
     *  功能:获取数据表行数
     */
    int getNRow() {
        return tableHeader -> getNRow();
    }
    
public:
    ///普通函数
    /*
     *  @函数名:addRow
     *  @参数tableRow:要加入的行，它会被复制之后加入，所以在哪里定义的就在哪里释放内存
     *  @参数pageId:用于返回插入位置的页编号
     *  @参数slotId:用于返回插入位置的槽编号
     *  功能:添加一行数据，去每一页里面找一个能加入的位置把它加进去
     */
    void addRow(TableRow * tableRow, int & pageId, int & slotId) {
        //表头不同报错
        if (!tableHeader -> isEqualTo(tableRow -> getTableHeader())) {
            std::cout << "Table.addRow(...) error" << std::endl;
            return;
        }
        //新列不满足NULL条件报错
        if (!tableRow -> canMeetNullRequirement()) {
            std::cout << "Table.addRow(...) error" << std::endl;
            return;
        }
        //新列不满足数据互不相同条件报错
        ///TODO
        /*if (!indexManager -> canMeetUniqueRequirement(tableRow)) {
            std::cout << "Table.addRow(...) error" << std::endl;
            return;
        }*/
        //在表页助手里面找一个合适的页
        int slotLen = tableRow -> getSizeInSlot();
        pageId = tablePageAssistant -> findPageForSlot(slotLen);
        //在这一页中获取槽的编号
        TablePage * page;
        if (pageId < oneFileManager -> getPageCnt()) {
            page = new TablePage(oneFileManager, pageId);   //在已有的页面上添加
        } else {
            page = new TablePage(oneFileManager);           //在新开的页面上添加
        }
        //写进去
        slotId = page -> createSlot(slotLen);
        ByteBufType buf = page -> getSlot(slotId);
        tableRow -> writeAsByte(buf);
        //改表页助手
        tablePageAssistant -> setFreeCnt(pageId, page -> getPageHeader() -> getFreeCnt());
    }
    
    /*
     *  @函数名:addRow
     *  @参数tableRow:要加入的行，它会被复制之后加入，所以在哪里定义的就在哪里释放内存
     *  功能:添加一行数据，去每一页里面找一个能加入的位置把它加进去
     */
    void addRow(TableRow * tableRow) {
        int pageId;
        int slotId;
        addRow(tableRow, pageId, slotId);
    }
    
    
};

#endif // TABLE_H_
