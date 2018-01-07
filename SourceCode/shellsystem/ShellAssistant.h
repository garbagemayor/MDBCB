#ifndef SHELL_ASSISTANT_H_
#define SHELL_ASSISTANT_H_

#include "../DatabaseManager.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <direct.h>

#ifdef WIN32
#include <windows.h>
HANDLE cmdColorHandle;
#endif

/**
 *  需要的类
 */
/*
 *  字符串数组
 */
typedef std::vector < std::string * > StringList;

/*
 *  创建表的列定义
 */
class UnionField {
    
public:
    int ty;
    union data {
        TableColumn * tc;   //ty = 1
        StringList * pk;    //ty = 2
    } dt;
    
public:
    UnionField() {
        ty = 0;
        dt.tc = NULL;
    }
    ~UnionField() {
        if (ty == 1) {
            delete dt.tc;
        } else {
            delete dt.pk;
        }
    }
};

/*
 *  列定义数组
 */
typedef std::vector < UnionField * > UnionFieldList;

/*
 *  数值
 */
class UnionValue {
    
public:
    int ty;
    union data {
        /*NULL*/            //ty = 0
        uint64 u;           //ty = 1
        double d;           //ty = 2
        std::string * s;    //ty = 3
    } dt;
    
public:
    UnionValue() {
        ty = 0;
        dt.u = 0;
    }
    
    ~UnionValue() {
        if (ty == 3) {
            delete dt.s;
        }
    }
};

/*
 *  数值行
 */
typedef std::vector < UnionValue * > UnionValueRow;

/*
 *  数值行数组，数值表
 */
typedef std::vector < UnionValueRow * > UnionValueTable;


/*
 *  运行时需要的数据，写到类里面可以在最后自动调用析构函数
 */
class RunningData {
    
public:
    //缓存页管理器
    BufPageManager * bufPageManager;
    //运行语境的数据库
    TableManager * database;
    //一条语句中前半句指定的一个数据表，不需要析构
    Table * table;
    
    RunningData() {
        bufPageManager = NULL;
        database = NULL;
        table = NULL;
    }
    ~RunningData() {
        if (database != NULL) {
            delete database;
            database = NULL;
        }
        if (bufPageManager != NULL) {
            delete bufPageManager;
            bufPageManager = NULL;
        }
    }
};

/**
 *  需要的数据和函数
 */
RunningData cur;

/*
 *  删除该文件夹，包括其中所有的文件和文件夹，可以是相对路径也可以是绝对路径
 */
int removeDir(const char*  dirPath) {
    struct _finddata_t fb;
    char path[256 + 4];
    strcpy(path, dirPath);
    strcat(path, "/*");
    int handle = _findfirst(path, &fb);
    if (handle != 0) {
        while (0 == _findnext(handle, &fb)) {
            int noFile = strcmp(fb.name, "..");
            if (0 != noFile) {
                memset(path, 0, sizeof(path));
                strcpy(path, dirPath);
                strcat(path, "/");
                strcat(path, fb.name);
                if (fb.attrib == 16) {
                    removeDir(path);
                } else {
                    remove(path);
                }
            }
        }
        _findclose(handle);
    }
    return rmdir(dirPath);
}

/*
 *  改变控制台(windows)/终端(linux)字体颜色
 */
void setCmdColor(int c) {
    if (c == 0) {
        //默认颜色
#ifdef WIN32
        SetConsoleTextAttribute(cmdColorHandle, FOREGROUND_INTENSITY);
#else
        printf("\033[0m");
#endif // WIN32
    } else if (c == 1) {
        //黄色
#ifdef WIN32
        SetConsoleTextAttribute(cmdColorHandle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
#else
        printf("\033[33m");
#endif // WIN321
    }
}

/*
 *  获取数据类型在SQL语言中的名称
 */
std::string getTypeNameInSQL(TableDataType type) {
    std::string typeName;
    switch (type) {
    case TableDataType::t_bool:
        typeName = "BOOL";
        break;
    case TableDataType::t_char:
        typeName = "CHAR";
        break;
    case TableDataType::t_short:
        typeName = "SHORT";
        break;
    case TableDataType::t_int:
        typeName = "INT";
        break;
    case TableDataType::t_long:
        typeName = "LONG";
        break;
    case TableDataType::t_float:
        typeName = "FLOAT";
        break;
    case TableDataType::t_double:
        typeName = "DOUBLE";
        break;
    case TableDataType::t_string:
        typeName = "VARCHAR";
        break;
    case TableDataType::t_lob:
        typeName = "LOB";
        break;
    default:
        typeName = "ERROR";
    }
    return typeName;
}

/*
 *  加载前半句SQL语句确定的数据表
 */
void loadCurTable(std::string * tbName) {
    //如果没有打开数据库，报错
    if (cur.database == NULL) {
        std::cout << "Parser.INSERT INTO: error" << std::endl;
        std::cout << "没有已经打开的数据库" << std::endl;
    } else if (!cur.database -> hasOpenedTable(* tbName)) {
        //如果没有这个数据表，报错
        std::cout << "Parser.INSERT INTO: error" << std::endl;
        std::cout << "没有数据表:" << * tbName << std::endl;
    } else {
        //当前SQL语句描述的数据表
        cur.table = cur.database -> getTableByName(* tbName);
    }
}

/*
 *  把文法产生的数据行转换为数据表中的数据行，不能转换就返回NULL
 */
TableRow * genTableRow(UnionValueRow * sqlRow, Table * table, std::string & errorMessage) {
    std::stringstream ssbuf;
    TableHeader * tableHeader = table -> getTableHeader();
    
    std::cout << "genTableRow(...) {" << std::endl;
    std::cout << "    tableHeader = {" << std::endl;
    std::cout << "        name = " << tableHeader -> getName() << std::endl;
    std::cout << "        nCol = " << tableHeader -> getNCol() << std::endl;
    std::cout << "        nRow = " << tableHeader -> getNRow() << std::endl;
    for (int i = 0; i < tableHeader -> getNCol(); i ++) {
    std::cout << "        columnList[" << i << "] = {" << std::endl;
    std::cout << "            name = " << tableHeader -> getColumnById(i) -> getName() << std::endl;
    std::cout << "            type = " << tableHeader -> getColumnById(i) -> getDataType() << std::endl;
    std::cout << "            length = " << tableHeader -> getColumnById(i) -> getDataLength() << std::endl;
    std::cout << "        }" << std::endl;
    }
    std::cout << "    }" << std::endl;
    std::cout << "}" << std::endl;
    
    //检查这一行的数据格数量
    if ((int) sqlRow -> size() != tableHeader -> getNCol()) {
        ssbuf << "读取到" << (int) sqlRow -> size() << "个数据，期望得到" << tableHeader -> getNCol() << "个";
        ssbuf >> errorMessage;
        return NULL;
    }
    TableRow * tableRow = new TableRow(tableHeader);
    IndexManager * indexManager = table -> getIndexManager();
    for (int i = 0; i < tableHeader -> getNCol(); i ++) {
        //检查这一格的数据类型和NULL情况
        UnionValue * sqlValue = sqlRow -> at(i);
        TableColumn * tableColumn = tableHeader -> getColumnById(i);
        TableGrid * tableGrid = tableRow -> getGridById(i);
        TableDataType superType = getSuperType(tableColumn -> getDataType());
        int typeLen = getDataTypeLength(tableColumn -> getDataType());
        if (sqlValue -> ty == 0) {
            //SQL遇到NULL
            if (!tableColumn -> allowNull()) {
                ssbuf << "输入的第" << i << "个数据格" << "不允许为NULL值";
                ssbuf >> errorMessage;
                delete tableRow;
                return NULL;
            }
            tableGrid -> setNull();
        } else if (sqlValue -> ty == 1) {
            //SQL遇到UINT64
            if (superType != TableDataType::t_long &&
                superType != TableDataType::t_double) {
                ssbuf << "输入的第" << i << "个数据格" << "的数据类型不兼容，";
                ssbuf << "读取到" << "UINT64" << "无法转换为" << getTypeNameInSQL(tableColumn -> getDataType());
                ssbuf >> errorMessage;
                delete tableRow;
                return NULL;
            }
            tableGrid -> setDataValueNumber(sqlValue -> dt.u, typeLen);
        } else if (sqlValue -> ty == 2) {
            //SQL遇到DOUBLE
            if (superType != TableDataType::t_double) {
                ssbuf << "输入的第" << i << "个数据格" << "的数据类型不兼容，";
                ssbuf << "读取到" << "DOUBLE" << "无法转换为" << getTypeNameInSQL(tableColumn -> getDataType());
                ssbuf >> errorMessage;
                delete tableRow;
                return NULL;
            }
            tableGrid -> setDataValueFloat(sqlValue -> dt.d, typeLen);
        } else if (sqlValue -> ty == 3) {
            //SQL遇到STRING
            if (superType != TableDataType::t_string) {
                ssbuf << "输入的第" << i << "个数据格" << "的数据类型不兼容，";
                ssbuf << "读取到" << "VARCHAR" << "无法转换为" << getTypeNameInSQL(tableColumn -> getDataType());
                ssbuf >> errorMessage;
                delete tableRow;
                return NULL;
            }
            std::string * s = sqlValue -> dt.s;
            tableGrid -> setDataValueArray((ByteBufType) s -> c_str(), s -> length());
        }
        //数据不允许重复的列检查
        if (tableColumn -> isUnique()) {
            if (tableColumn -> hasTreeIndex() ||
                tableColumn -> hasHashIndex()) {
                //B+树索引
                TreeIndex * treeIndex = (TreeIndex *) indexManager -> getIndexById(i);
                if (treeIndex -> containKey(tableGrid -> getDataValueNumber())) {
                    ssbuf << "输入的第" << i << "个数据格" << "在数据表中重复出现，但该列不允许重复数据";
                    ssbuf >> errorMessage;
                    delete tableRow;
                    return NULL;
                }
            }
            /*
             else if (tableColumn -> hasHashIndex()) {
                //Hash索引
                HashIndex * hashIndex = (HashIndex *) indexManager -> getIndexById(i);
                if (hashIndex -> containKey(tableGrid -> getDataPointer(), tableGrid -> getDataLength()) {
                    ssbuf << "输入的第" << i "个数据格" << "在数据表中重复出现，但该列不允许重复数据";
                    ssbuf >> errorMessage;
                    delete tableRow;
                    return NULL;
                }
            }
            */
        }
    }
    return tableRow;
}




















#endif // SHELL_ASSISTANT_H_
