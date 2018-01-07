#ifndef SHELL_CLASS_H_
#define SHELL_CLASS_H_

#include "../DatabaseManager.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <direct.h>

/**
 *  Parser需要的类和重定义
 */
/*
 *  identList:字符串数组
 */
typedef std::vector < std::string * > StringList;

/*
 *  field:创建表的列定义
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
 *  fieldList:列定义数组
 */
typedef std::vector < UnionField * > UnionFieldList;

/*
 *  value:数值
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
 *  valueList:数值行
 *  valueLists:数值行数组，数值表
 */
typedef std::vector < UnionValue * > UnionValueList;
typedef std::vector < UnionValueList * > UnionValueLists;

/*
 *  setItem:更新值
 */
class UnionSetItem {
    
public:
    std::string * col;
    UnionValue * uv;
    
    UnionSetItem() {
        col = NULL;
        uv = NULL;
    }
    
    ~UnionSetItem() {
        delete col;
        delete uv;
    }
};

/*
 *  setList, setClause:更新值数组
 */
typedef std::vector < UnionSetItem * > UnionSetClause;

/*
 *  col:列
 */
class UnionCol {
    
public:
    std::string * tb;   //注意要复制之后再加入
    std::string * col;
    TableColumn * tc;   //不用析构
    
    UnionCol() {
        tb = NULL;
        col = NULL;
        tc = NULL;
    }
    ~UnionCol() {
        delete tb;
        delete col;
    }
};

/*
 *  selector:列数组
 */
typedef std::vector < UnionCol * > UnionColList;

/*
 *  whereItem:一句比较运算
 */
class UnionWhereItem {
    
public:
    enum OpTag {
        OP_ERROR = 0,
        OP_EQ,
        OP_NE,
        OP_LT,
        OP_GT,
        OP_LE,
        OP_GE,
    };
    
public:
    OpTag op;
    UnionCol * left;
    int ty;
    union RValue {
        /* NULL */          //ty = 0
        UnionValue * uv;    //ty = 1
        UnionCol * uc;      //ty = 2
    } right;
    
    UnionWhereItem() {
        op = OP_ERROR;
        left = NULL;
        ty = 0;
        right.uv = NULL;
    }
    
    ~UnionWhereItem() {
        if (left != NULL) {
            delete left;
            left = NULL;
        }
        if (ty == 1) {
            delete right.uv;
            right.uv = NULL;
        } else {
            delete right.uc;
            right.uc = NULL;
        }
    }
};

/*
 *  whereClause:一坨比较运算
 */
typedef std::vector < UnionWhereItem * > UnionWhereClause;
 


#endif // SHELL_CLASS_H_
