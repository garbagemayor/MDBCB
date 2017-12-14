#ifndef INDEX_MANAGER_H_
#define INDEX_MANAGER_H_

#include <iostream>

#include "../tablesystem/TableManager.h"
#include "IndexTree/IndexTree.h"

/*
 *  索引基类。
 *  一个索引存在于一个文件里面。
 */
class IndexBase {

protected:
    //文件编号
    int fileId;
    //页数统计
    int pageCount;

    //表
    TableManager * table;
    //列名
    char * colName;

public:
    //虚构造函数
    virtual IndexBase(TableManager * table_, char * colName_) {
        table = table_;
        colName = colName_;
        //创建文件
        static char fileName[256];
        sprintf(fileName, "%s__%s.ind", table->getName(), colName);
        FileManager * fileManager = new FileManager();
        fileManager.createFile(fileName);   //TODO 异常处理
        fileManager.openFile(fileName, fileId); //TODO 异常处理
        pageCount = 0;
    }

};


/*
 *  B+树索引。
 */
template <typename KeyType>
class IndexTree
    : public IndexBase {
    
protected:
    

protected:
    IndexTree(TableManager * table_, char * colName_)
        : IndexBase(table_, colName_) {
        
        
    }

public:



};




/*
 *  一个表只有一个索引管理器，一个索引管理器可以管理多个列的索引。
 */
class IndexManager {

private:
    //索引针对的表
    TableManager * table;
    //索引数量
    int n;
    //索引列表
    IndexBase * index;

public:



};

#endif // INDEX_MANAGER_H_
