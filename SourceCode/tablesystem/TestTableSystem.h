#include "TableManager.h"

int runTestTableSystem() {
    //�������ݱ������
    FileManager * fileManager = new FileManager();
    BufPageManager * bufPageManager = new BufPageManager(fileManager);
    TableManager * tableManager = new TableManager(bufPageManager);
    
    //������ͷ
    TableHeader * tableHeader = new TableHeader();
    tableHeader -> setName("Table1");
    //���������в��ӽ���ͷ
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
    
    //������
    tableManager -> createTable(tableHeader);
    
    
    
    
    
    
    
    delete bufPageManager;
    delete tableManager;
    delete tableHeader;
    
    
    
    return 0;
}
