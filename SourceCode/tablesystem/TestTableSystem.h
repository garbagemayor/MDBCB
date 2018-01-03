#ifndef TEST_TABLE_SYSTEM_H_
#define TEST_TABLE_SYSTEM_H_

#include "TableManager.h"

int runTestTableSystem() {
    ///创建数据库
    //创建数据表管理器
    FileManager * fileManager = new FileManager();
    BufPageManager * bufPageManager = new BufPageManager(fileManager);
    TableManager * tableManager = new TableManager(bufPageManager);
    
    ///创建数据表
    //创建三个列并加进表头
    TableColumn * column1 = new TableColumn();
    column1 -> setName("column1");
    column1 -> setType(TableDataType::t_int);
    column1 -> setPrimaryKey(true);
    column1 -> setConstant();
    
    TableColumn * column2 = new TableColumn();
    column2 -> setName("column2");
    column2 -> setType(TableDataType::t_long);
    column2 -> setConstant();
    
    TableColumn * column3 = new TableColumn();
    column3 -> setName("column3");
    column3 -> setType(TableDataType::t_double);
    column3 -> setConstant();
    
    TableColumn * column4 = new TableColumn();
    column4 -> setName("column4");
    column4 -> setType(TableDataType::t_string);
    column4 -> setConstant();
    
    //创建表头
    TableHeader * tableHeader = new TableHeader();
    tableHeader -> setName("Table1");
    tableHeader -> addColumn(column1);
    tableHeader -> addColumn(column2);
    tableHeader -> addColumn(column3);
    tableHeader -> addColumn(column4);
    tableHeader -> setConstant();
    
    //创建表
    tableManager -> createTable(tableHeader);
    
    ///插入行
    //创建空行
    TableRow * tableRow1 = new TableRow(tableHeader);
    
    //给每个格子数据
    tableRow1 -> getGridByName("column1") -> setDataValueNumber(123, 4);
    tableRow1 -> getGridByName("column2") -> setDataValueNumber(1ull << 48, 8);
    tableRow1 -> getGridByName("column3") -> setDataValueFloat(1.23456789, 8);
    std::string str = "皮这一下你开心吗";
    tableRow1 -> getGridByName("column4") -> setDataValueArray((ByteBufType) str.c_str(), str.length());
    
    //插入行
    tableManager -> getTableByName("Table1") -> addRow(tableRow1);
    
    ///查询行
    //tableManager -> getTableByName("Table1") -> 
    
    
    
    ///删除行
    
    
    
    delete tableRow1;
    
    delete column1;
    delete column2;
    delete column3;
    delete column4;
    delete tableHeader;
    
    delete tableManager;
    delete bufPageManager;
    
    return 0;
}

#endif // TEST_TABLE_SYSTEM_H_
