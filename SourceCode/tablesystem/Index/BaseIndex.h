#ifndef BASE_INDEX_H_
#define BASE_INDEX_H_

#include "../../filesystem/OneFileManager.h"
#include "../Table/TableColumn.h"
#include "IndexStructure.h"

#include <iostream>
#include <string>

/**
 *  索引基类，派生之后由索引管理器IndexManager来管理
 *  一个索引存在于一个文件里面，对应数据表的一列
 */
class BaseIndex {
    
protected:
    //索引文件的单文件管理器
    OneFileManager * oneFileManager;
    //索引类型
    IndexStructure indexStructure;
    //数据表的名字
    std::string tableName;
    //索引管理的列的信息
    TableColumn * tableColumn;

public:
    /*
     *  @函数名:构造函数
     *  功能:读取或创建一个索引基类
     */
    BaseIndex(BufPageManager * bufPageManager_, std::string tableName_, TableColumn * tableColumn_) {
        //空指针报错
        if (bufPageManager_ == NULL || tableColumn_ == NULL) {
            std::cout << "BaseIndex(..., " << tableName_ << ", ...) error" << std::endl;
            return;
        }
        //基本信息
        indexStructure = IndexStructure::in_baseIndex;
        tableName = tableName_;
        tableColumn = tableColumn_;
        //创建或打开文件
        std::string fileName = getFileName();
        oneFileManager = new OneFileManager(bufPageManager_, fileName.c_str());
    }
    
    /*
     *  @析构函数
     *  功能:写回并关掉文件，virtual之后可以保证会先调用子类的析构函数
     */
    virtual ~BaseIndex() {
        delete oneFileManager;
    }
    
public:
    /*
     *  @函数名:getFileName
     *  功能:获取文件名
     */
    std::string getFileName() {
        return tableName + "." + tableColumn -> getName() + ".index";
    }
};

#endif // BASE_INDEX_H_
