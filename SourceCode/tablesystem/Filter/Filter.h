#ifndef FILTER_H
#define FILTER_H

#include "../Table/TableDataType.h"
#include "../Table/TableColumn.h"
#include "../Table/TableGrid.h"

/**
 *  筛选器树，支持形如“table1.column1 == table2.column2 AND ( table1.column3 < 5 OR table2.column3 < 10 )”这样的筛选条件
 *  大概就是这么个意思：
 *
 *  WhereClause =   WhereClause AND FilterItem
 *
 *  FilterItem  =   Col IS NNULL
 *              |   Col NOT IS NNULL
 *              |   Col Op Expr
 *
 *  Expr        =   Value
 *              |   Col
 *  
 *  Col         =   ColName
 *              |   TbName '.' ColName
 *
 *  Op          =   '='
 *              |   '<' '>'
 *              |   '<'
 *              |   '>'
 *              |   '<' '='
 *              |   '>' '='
 *
 *  Value       =   VALUE_INT
 *              |   VALUE_FLOAT
 *              |   VALUE_STRING
 *              |   NNULL
 *
 *  字符串只支持 == 和 != 两个比较运算，整数和浮点数支持全部六个比较运算
 */
class Filter {
    
public:
    ///常量
    enum Tag {
        ERROR = 0,
        FILTER,
        FI_NULL,
        FI_NOTN,
        FI_OP,
        EXPR_VAL,
        EXPR_COL,
        OP_EQ,
        OP_NE,
        OP_LT,
        OP_GT,
        OP_LE,
        OP_GE,
        VAL_INT,
        VAL_FLOAT,
        VAL_STRING,
        VAL_NULL,
    };
    //先声明
    class FilterBase;
    class WhereClause;
    class FilterNull;
    class FilterOp;
    class Expr;
    class Col;
    class Op;
    class Value;
    class Visitor;
    
public:
    //Filter语法分析树的各种节点
    /**
     *  表达式基类
     */
    class FilterBase {
        
    public:
        //节点类型
        Tag tag;
        //数据类型
        TableDataType type;
        //计算结果
        TableGrid * valGrid;
        bool valResult;
        
    public:
        FilterBase(Tag tag_){
            tag = tag_;
            type = TableDataType::t_error;
            valGrid = NULL;
            valResult = false;
        }
        
        virtual ~FilterBase() {
            if (valGrid != NULL) {
                delete valGrid;
            }
        }
        
        virtual void accept(Visitor * v) {
            v -> visitFilterBase(this);
        }
    };
    
    /**
     *  整个表达式
     */
    class WhereClause
        : public FilterBase {
        
    public:
        std::vector<FilterBase *> exprList;
        
    public:
        WhereClause(Tag tag_)
            : FilterBase(tag_) {
            exprList.clear();
            type = TableDataType::t_bool;
            valGrid = NULL;
            valResult = false;
        }
        
        ~WhereClause() {
            for (int i = 0; i < (int) exprList.size(); i ++) {
                if (exprList[i] != NULL) {
                    delete exprList[i];
                }
            }
            exprList.clear();
        }
        
        void accept(Visitor * v) {
            v -> visitWhereClause(this);
        }
    };
    
    /**
     *  IS NULL表达式和IS NOT NULL表达式
     */
    class FilterNull
        : public FilterBase {
        
    public:
        Col * expr;
        
    public:
        FilterNull(Tag tag_, Col * expr_)
            : FilterBase(tag_) {
            expr = expr_;
            type = TableDataType::t_bool;
            valGrid = NULL;
            valResult = false;
        }
        
        ~FilterNull() {
            if (expr != NULL) {
                delete expr;
                expr = NULL;
            }
        }
        
        void accept(Visitor * v) {
            v -> visitFilterNull(this);
        }
    };
    
    /**
     *  比较表达式
     */
    class FilterOp
        : public FilterBase {
        
    public:
        Col * left;
        Op * op;
        Expr * right;
        
    public:
        FilterOp(Tag tag_, Col * left_, Op * op_, Expr * right_)
            : FilterBase(tag_) {
            left = left_;
            op = op_;
            right = right_;
            if (right -> type == TableDataType::t_null ||
                left -> type == right -> type) {
                type = TableDataType::t_bool;
            } else {
                type = TableDataType::t_error;
            }
            valGrid = NULL;
            valResult = false;
        }
        
        ~FilterOp() {
            if (left != NULL) {
                delete left;
                left = NULL;
            }
            if (op != NULL) {
                delete op;
                op = NULL;
            }
            if (right != NULL) {
                delete right;
                right = NULL;
            }
        }
        
        void accept(Visitor * v) {
            v -> visitFilterOp(this);
        }
    };
    
    /**
     *  判断条件的右值
     */
    class Expr
        : public FilterBase {
        
    public:
        FilterBase * expr;
        
    public:
        Expr(Tag tag_, FilterBase * expr_)
            : FilterBase(tag_) {
            expr = expr_;
            type = expr -> type;
            valGrid = NULL;
            valResult = false;
        }
        
        ~Expr() {
            if (expr != NULL) {
                delete expr;
                expr = NULL;
            }
        }
        
        void accept(Visitor * v) {
            v -> visitExpr(this);
        }
    };
    
    /**
     *  数据表的列
     */
    class Col
        : public FilterBase {
        
    public:
        std::string tableName;
        TableColumn * tableColumn;
        
    public:
        Col(Tag tag_, std::string tableName_, TableColumn * tableColumn_)
            : FilterBase(tag_) {
            tableName = tableName_;
            tableColumn = tableColumn_;
            type = getSuperType(tableColumn_ -> getDataType());
            valGrid = new TableGrid(tableColumn_);
        }
        
        ~Col() {
            if (valGrid != NULL) {
                delete valGrid;
                valGrid = NULL;
            }
        }
        
        void accept(Visitor * v) {
            v -> visitCol(this);
        }
    };
    
    /**
     *  运算符
     */
    class Op
        : public FilterBase {
        
    public:
        Op(Tag tag_)
            : FilterBase(tag_) {
            type = TableDataType::t_error;
        }
        
        ~Op() {
        }
        
        void accept(Visitor * v) {
            v -> visitOp(this);
        }
    };
    
    /**
     *  常数
     */
    class Value
        : public FilterBase{
        
    public:
        uint64 value;
        
    public:
        Value(Tag tag_, uint64 value_)
            : FilterBase(tag_) {
            switch (tag) {
            case VAL_INT:
                type = TableDataType::t_long;
                break;
            case VAL_FLOAT:
                type = TableDataType::t_double;
                break;
            case VAL_STRING:
                type = TableDataType::t_string;
                break;
            case VAL_NULL:
                type = TableDataType::t_null;
                break;
            default:
                type = TableDataType::t_error;
            }
            value = value_;
            TableColumn * tableColumn = new TableColumn();
            tableColumn -> setType(type);
            valGrid = new TableGrid(tableColumn);
        }
        
        ~Value() {
            if (valGrid != NULL) {
                delete valGrid;
                valGrid = NULL;
            }
        }
        
        void accept(Visitor * v) {
            v -> visitValue(this);
        }
    };
    
    /**
     *  遍历工具
     */
    class Visitor {
        
    public:
        Visitor() {
        }
        
        virtual ~Visitor() {
        }
        
    public:
        
        void visitWhereClause(Filter::WhereClause * that) {
            visitFilterBase(that);
        }
        
        void visitFilterNull(Filter::FilterNull * that) {
            visitFilterBase(that);
        }
        
        void visitFilterOp(Filter::FilterOp * that) {
            visitFilterBase(that);
        }
        
        void visitExpr(Filter::Expr * that) {
            visitFilterBase(that);
        }
        
        void visitCol(Filter::Col * that) {
            visitFilterBase(that);
        }
        
        void visitOp(Filter::Op * that) {
            visitFilterBase(that);
        }
        
        void visitValue(Filter::Value * that) {
            visitFilterBase(that);
        }
        
        void visitFilterBase(FilterBase * that) {
            std::cout << "Filter.Visitor.visitFilterBase(...) error" << std::endl;
        }
    };
};

#endif // FILTER_H
