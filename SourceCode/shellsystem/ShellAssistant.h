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
int setCmdColor(int c) {
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

typedef std::vector < std::string * > StringList;

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

typedef std::vector < UnionField * > UnionFieldList;




#endif // SHELL_ASSISTANT_H_
