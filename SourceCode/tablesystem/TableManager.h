#ifndef TABLE_MANAGER_H_
#define TABLE_MANAGER_H_

#include "../filesystem/bufmanager/BufPageManager.h"
#include "Table.h"

/**
 *  数据表管理器，管理所有数据表
 *  
 */
class TableManager {
    
public:
    //缓存页管理器
    BufPageManager * bufPageManager;
    //数据表列表
    std::vector<Table *> tableList;
    
public:/*
     *  @构造函数
     *  @参数bufPageManager_:缓存页管理器
     *  功能:新建一个数据表管理器
     */
    TableManager(BufPageManager * bufPageManager_) {
        bufPageManager = bufPageManager_;
        tableList.clear();
    }
    
    /*
     *  @函数名:createTable
     *  @参数tableHeader:新数据表的名称
     *  功能:新建一个数据表，如果有同名的数据表就报错
     */
    void createTable(TableHeader * tableHeader) {
        //表头仍然可修改报错
        if (tableHeader -> isModifiable()) {
            std::cout << "TableManager.createTable(" << tableHeader -> getName() << "_ error" << std::endl;
            return;
        }
        //同名数据表报错
        for (int i = 0; i < (int) tableList.size(); i ++) {
            if (tableList[i] -> getName() == tableHeader -> getName()) {
                std::cout << "TableManager.createTable(" << tableHeader -> getName() << "_ error" << std::endl;
                return;
            }
        }
        tableList.push_back(new Table(bufPageManager, tableHeader));
    }
    
    /*
     *  @函数名:openTable
     *  @参数tableName:数据表的名称
     *  功能:打开一个已存在的数据表，如果已经打开过就报错
     */
    void openTable(std::string tableName) {
        for (int i = 0; i < (int) tableList.size(); i ++) {
            if (tableList[i] -> getName() == tableName) {
                std::cout << "TableManager.openTable(" << tableName << "_ error" << std::endl;
                return;
            }
        }
        tableList.push_back(new Table(bufPageManager, tableName));
    }
    
    /*
     *  @函数名:hasOpenedTable
     *  @参数tableName:数据表的名称
     *  功能:查询是否已经打开过这个表
     */
    bool hasOpenedTable(std::string tableName) {
        for (int i = 0; i < (int) tableList.size(); i ++) {
            if (tableList[i] -> getName() == tableName) {
                return true;
            }
        }
        return false;
    }
    
    /*
     *  @函数名:closeTable
     *  @参数tableName:数据表的名称
     *  功能:关闭一个已经打开的数据表，如果没有这样的数据表就报错
     */
    void closeTable(std::string tableName) {
        int n = (int) tableList.size();
        for (int i = 0; i < n; i ++) {
            if (tableList[i] -> getName() == tableName) {
                delete tableList[i];
                tableList[i] = tableList[n - 1];
                tableList.pop_back();
                return;
            }
        }
        std::cout << "TableManager.closeTable(" << tableName << ") error" << std::endl;
        return;
    }
    
    
public:
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};


#endif // TABLE_MANAGER_H_
