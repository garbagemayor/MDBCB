#ifndef TABLE_H_
#define TABLE_H_

#include "../../filesystem/OneFileManager.h"
#include "../Page/TablePage.h"
#include "TableHeader.h"
#include "TableRow.h"

/**
 *  单个数据表，由数据表管理器TableManager管理。
 *  一个数据表对应一个文件，由 <表名> + ".table"命名。
 *  如果是新建数据表，需要保证原本没有同名的数据表。
 *  在文件的第0页，存储表头等基本信息，不存数据。
 */
class Table {
    
public:
    //单文件管理器
    OneFileManager * oneFileManager;
    //表头和表的基本信息
    TableHeader * tableHeader;
    //索引管理器
    //IndexManager indexManager;
    
public:
    /*
     *  @构造函数
     *  @参数bufPageManager_:缓存页管理器
     *  @参数tableHeader_:新数据表的表头
     *  功能:新建一个数据表，要3个步骤：(1)创建第0页的页头和页脚(2)新建第0页(3)写入表头
     */
    Table(BufPageManager * bufPageManager_, TableHeader * tableHeader_) {
        oneFileManager = new OneFileManager(bufPageManager_, (tableHeader_ -> getName() + ".table").c_str());
        tableHeader = tableHeader_;
        //创建第0页的页头和页脚
        //新建第0页，写入页头页脚
        TablePage * page0 = new TablePage(oneFileManager);
        //新建槽，写入表头;
        page0 -> addSlot(tableHeader -> getSizeInSlot(), tableHeader -> toByteBuffer());
    }
    
    /*
     *  @构造函数
     *  @参数bufPageManager_:缓存页管理器
     *  @参数tableName_:数据表的名字
     *  功能:打开一个原有数据表，只需要读取第0页的表头信息
     */
    Table(BufPageManager * bufPageManager_, std::string tableName_) {
        oneFileManager = new OneFileManager(bufPageManager_, (tableName_ + ".table").c_str());
        TablePage * page0 = new TablePage(oneFileManager, 0);
        tableHeader = new TableHeader(page0 -> getSlot(0));
    }
    
public:
    /*
     *  @函数名:getName
     *  功能:获取数据表名称
     */
    std::string getName() {
        return tableHeader -> getName();
    }
    
    /*
     *  @函数名:addRow
     *  @参数tableRow:要加入的行，它会被复制之后加入，所以在哪里定义的就在哪里释放内存
     *  @参数pageId:用于返回插入位置的页编号
     *  @参数slotId:用于返回插入位置的槽编号
     *  功能:添加一行数据，去每一页里面找一个能加入的位置把它加进去
     */
    int addRow(TableRow * tableRow, int & pageId, int & slotId) {
        
    }
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif // TABLE_H_
