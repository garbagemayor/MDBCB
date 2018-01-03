#ifndef FILTER_H
#define FILTER_H

#include "../Table/TableDataType.h"
#include "../Table/TableColumn.h"
#include "../Table/TableGrid.h"

/**
 *  ɸѡ������֧�����硰table1.column1 == table2.column2 AND ( table1.column3 < 5 OR table2.column3 < 10 )��������ɸѡ����
 *  ��ž�����ô����˼��
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
 *  �ַ���ֻ֧�� == �� != �����Ƚ����㣬�����͸�����֧��ȫ�������Ƚ�����
 */
class Filter {
    
public:
    ///����
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
    //������
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
    //Filter�﷨�������ĸ��ֽڵ�
    /**
     *  ���ʽ����
     */
    class FilterBase {
        
    public:
        //�ڵ�����
        Tag tag;
        //��������
        TableDataType type;
        //������
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
     *  �������ʽ
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
     *  IS NULL���ʽ��IS NOT NULL���ʽ
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
     *  �Ƚϱ��ʽ
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
     *  �ж���������ֵ
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
     *  ���ݱ����
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
     *  �����
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
     *  ����
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
     *  ��������
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
