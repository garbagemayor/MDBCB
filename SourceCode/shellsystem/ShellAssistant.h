#ifndef SHELL_ASSISTANT_H_
#define SHELL_ASSISTANT_H_

#include "../DatabaseManager.h"

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <direct.h>

#ifdef WIN32
#include <windows.h>
HANDLE cmdColorHandle;
#endif

/**
 *  ��Ҫ����
 */
/*
 *  �ַ�������
 */
typedef std::vector < std::string * > StringList;

/*
 *  ��������ж���
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
 *  �ж�������
 */
typedef std::vector < UnionField * > UnionFieldList;

/*
 *  ��ֵ
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
 *  ��ֵ��
 */
typedef std::vector < UnionValue * > UnionValueRow;

/*
 *  ��ֵ�����飬��ֵ��
 */
typedef std::vector < UnionValueRow * > UnionValueTable;


/*
 *  ����ʱ��Ҫ�����ݣ�д�����������������Զ�������������
 */
class RunningData {
    
public:
    //����ҳ������
    BufPageManager * bufPageManager;
    //�����ﾳ�����ݿ�
    TableManager * database;
    //һ�������ǰ���ָ����һ�����ݱ�����Ҫ����
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
 *  ��Ҫ�����ݺͺ���
 */
RunningData cur;

/*
 *  ɾ�����ļ��У������������е��ļ����ļ��У����������·��Ҳ�����Ǿ���·��
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
 *  �ı����̨(windows)/�ն�(linux)������ɫ
 */
void setCmdColor(int c) {
    if (c == 0) {
        //Ĭ����ɫ
#ifdef WIN32
        SetConsoleTextAttribute(cmdColorHandle, FOREGROUND_INTENSITY);
#else
        printf("\033[0m");
#endif // WIN32
    } else if (c == 1) {
        //��ɫ
#ifdef WIN32
        SetConsoleTextAttribute(cmdColorHandle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
#else
        printf("\033[33m");
#endif // WIN321
    }
}

/*
 *  ��ȡ����������SQL�����е�����
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
 *  ����ǰ���SQL���ȷ�������ݱ�
 */
void loadCurTable(std::string * tbName) {
    //���û�д����ݿ⣬����
    if (cur.database == NULL) {
        std::cout << "Parser.INSERT INTO: error" << std::endl;
        std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
    } else if (!cur.database -> hasOpenedTable(* tbName)) {
        //���û��������ݱ�����
        std::cout << "Parser.INSERT INTO: error" << std::endl;
        std::cout << "û�����ݱ�:" << * tbName << std::endl;
    } else {
        //��ǰSQL������������ݱ�
        cur.table = cur.database -> getTableByName(* tbName);
    }
}

/*
 *  ���ķ�������������ת��Ϊ���ݱ��е������У�����ת���ͷ���NULL
 */
TableRow * genTableRow(UnionValueRow * sqlRow, TableHeader * tableHeader) {
    
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
    
    //�����һ�е����ݸ�����
    if ((int) sqlRow -> size() != tableHeader -> getNCol()) {
        return NULL;
    }
    TableRow * tableRow = new TableRow(tableHeader);
    for (int i = 0; i < tableHeader -> getNCol(); i ++) {
        //�����һ����������ͺ�NULL���
        UnionValue * sqlValue = sqlRow -> at(i);
        TableColumn * tableColumn = tableHeader -> getColumnById(i);
        TableGrid * tableGrid = tableRow -> getGridById(i);
        TableDataType superType = getSuperType(tableColumn -> getDataType());
        int typeLen = getDataTypeLength(tableColumn -> getDataType());
        if (sqlValue -> ty == 0) {
            //SQL����NULL
            if (!tableColumn -> allowNull()) {
                delete tableRow;
                return NULL;
            }
            tableGrid -> setNull();
        } else if (sqlValue -> ty == 1) {
            //SQL����UINT64
            if (superType != TableDataType::t_long &&
                superType != TableDataType::t_double) {
                delete tableRow;
                return NULL;
            }
            tableGrid -> setDataValueNumber(sqlValue -> dt.u, typeLen);
        } else if (sqlValue -> ty == 2) {
            //SQL����DOUBLE
            if (superType != TableDataType::t_double) {
                delete tableRow;
                return NULL;
            }
            tableGrid -> setDataValueFloat(sqlValue -> dt.d, typeLen);
        } else if (sqlValue -> ty == 3) {
            //SQL����STRING
            if (superType != TableDataType::t_string) {
                delete tableRow;
                return NULL;
            }
            std::string * s = sqlValue -> dt.s;
            tableGrid -> setDataValueArray((ByteBufType) s -> c_str(), s -> length());
        }
    }
    return tableRow;
}




















#endif // SHELL_ASSISTANT_H_
