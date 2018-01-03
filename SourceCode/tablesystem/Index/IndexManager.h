#ifndef INDEX_MANAGER_H_
#define INDEX_MANAGER_H_

#include "../../filesystem/bufmanager/BufPageManager.h"
#include "../Table/TableHeader.h"
#include "TreeIndex/TreeIndex.h"
#include "HashIndex/HashIndex.h"

#include <iostream>

/**
 *  索引管理器类
 *  一个表只有一个索引管理器，一个索引管理器可以管理多个列的索引
 *  indexList中的下标就是tableHeader中每个列的下标，没有索引就NULL
 *  每列最多只能有一个索引，string和lob类型只能用Hash索引，其他类型既可以B+树索引也可以Hash索引
 */
class IndexManager {

private:
    //缓存页管理器
    BufPageManager * bufPageManager;
    //表头
    TableHeader * tableHeader;
    //索引列表
    std::vector<BaseIndex *> indexList;

public:
    /*
     *  @构造函数
     *  功能:创建一个索引管理器，创建或读取每个有索引的列的索引
     */
    IndexManager(BufPageManager * bufPageManager_, TableHeader * tableHeader_) {
        bufPageManager = bufPageManager_;
        tableHeader = tableHeader_;
        indexList.clear();
        indexList.resize(tableHeader -> getNCol());
        for (int i = 0; i < tableHeader -> getNCol(); i ++) {
            TableColumn * tableColumn = tableHeader -> getColumnById(i);
            if (tableColumn -> hasTreeIndex()) {
                indexList[i] = new TreeIndex(bufPageManager, tableHeader -> getName(), tableColumn);
            } else if(tableColumn -> hasHashIndex()) {
                indexList[i] = new HashIndex(bufPageManager, tableHeader -> getName(), tableColumn);
            } else {
                indexList[i] = NULL;
            }
        }
    }
    
public:
    /*
     *  @函数名:getIndexById
     *  功能:用编号获取列的索引
     */
    BaseIndex * getIndexById(int id) {
        if (id < 0 || id >= (int) indexList.size()) {
            std::cout << "IndexManager.getIndexById(" << id << ") error" << std::endl;
            return NULL;
        }
        return indexList[id];
    }
    
    /*
     *  @函数名:getIndexByName
     *  功能:用数据列的名称获取列的索引
     */
    BaseIndex * getIndexByName(std::string columnName) {
        for (int i = 0; i < (int) indexList.size(); i ++) {
            if (tableHeader -> getColumnById(i) -> getName() == columnName) {
                return indexList[i];
            }
        }
        if (true) {
            std::cout << "IndexManager.getIndexByName(" << columnName << ") error" << std::endl;
            return NULL;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
};

#endif // INDEX_MANAGER_H_
