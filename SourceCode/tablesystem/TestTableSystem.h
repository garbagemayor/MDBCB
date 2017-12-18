#include "TableManager.h"

int runTestTableSystem() {
    //创建数据表管理器
    FileManager * fileManager = new FileManager();
    BufPageManager * bufPageManager = new BufPageManager(fileManager);
    TableManager * tableManager = new TableManager(bufPageManager);
    
    //创建表头
    TableHeader * tableHeader = new TableHeader();
    tableHeader -> setName("Table1");
    //创建三个列并加进表头
    TableColumn * column1 = new TableColumn();
    column1 -> setName("column1");
    column1 -> setType(TableDataType::t_int);
    column1 -> setConstant();
    tableHeader -> addColumn(column1);
    delete column1;
    TableColumn * column2 = new TableColumn();
    column2 -> setName("column2");
    column2 -> setType(TableDataType::t_long);
    column2 -> setConstant();
    tableHeader -> addColumn(column2);
    delete column2;
    TableColumn * column3 = new TableColumn();
    column3 -> setName("column3");
    column3 -> setType(TableDataType::t_string);
    column3 -> setConstant();
    tableHeader -> addColumn(column3);
    delete column3;
    tableHeader -> setConstant();
    
    //创建表
    tableManager -> createTable(tableHeader);
    
    
    
    
    
    
    
    delete bufPageManager;
    delete tableManager;
    delete tableHeader;
    
    
    
    return 0;
}
