#ifndef BASE_INDEX_H_
#define BASE_INDEX_H_

#include "../../filesystem/OneFileManager.h"
#include "../../tablesystem/TableManager.h"

/*
 *  索引基类。
 *  一个索引存在于一个文件里面。
 */
class BaseIndex {
    
public:
    enum IndexType {
        baseIndex = 0,
        treeIndex = 1,
        hashIndex = 2,
    };
    
protected:
    //索引对应的表管理器
    TableManager * tableManager;
    //索引文件的单文件管理器
    OneFileManager * oneFileManager;
    //索引类型
    IndexType indexType;
    

public:
    //构造函数
    IndexBase(TableManager * tableManager_, char * colName) {
        tableManager = tableManager_;
        indexType = IndexType.baseIndex;
        static char fileName[256];
        sprintf(fileName, "%s__%s.ind", table->getName(), colName);
        oneFileManager = new OneFileManager(tableManager->bpm, fileName);
    }
};

#endif // BASE_INDEX_H_
