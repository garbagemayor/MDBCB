#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Filter.h"

class TableRow;
class Table;
class TableManager;
    
class Calculator
    : public Filter::Visitor {
    
protected:
    //数据表管理器
    TableManager * tableManager;
    
public:
    Calculator(TableManager * tableManager_)
        : Filter::Visitor() {
        tableManager = tableManager_;
    }
    
    ~Calculator() {
    }
    
public:
    static void run(TableManager * tableManager_, Filter::FilterBase * filterBase) {
        Calculator * calculator = new Calculator(tableManager_);
        calculator -> visitWhereClause((Filter::WhereClause *) filterBase);
    }
    
protected:
    void visitWhereClause(Filter::WhereClause * where) {
        bool valResult = true;
        for (int i = 0; i < (int) where -> exprList.size(); i ++) {
            where -> exprList[i] -> accept(this);
            valResult = valResult || where -> exprList[i] -> valResult;
        }
        where -> valResult = valResult;
    }
    
    void visitFilterNull(Filter::FilterNull * filterNull) {
        switch (filterNull -> tag) {
        case Filter::Tag::FI_NULL:
            filterNull -> valResult = filterNull -> expr -> valGrid -> isNull();
            break;
        case Filter::Tag::FI_NOTN:
            filterNull -> valResult = ! filterNull -> expr -> valGrid -> isNull();
            break;
        default:
            filterNull -> valResult = false;
        }
    }
    
    void visitFilterOp(Filter::FilterOp * filterOp) {
        switch (filterOp -> op -> tag) {
        case Filter::Tag::OP_EQ:
            filterOp -> valResult = filterOp -> left -> valGrid -> isEqualTo(filterOp -> right -> valGrid);
            break;
        case Filter::Tag::OP_NE:
            filterOp -> valResult = ! filterOp -> left -> valGrid -> isEqualTo(filterOp -> right -> valGrid);
            break;
        case Filter::Tag::OP_LT:
            filterOp -> valResult = filterOp -> left -> valGrid -> isLessThan(filterOp -> right -> valGrid);
            break;
        case Filter::Tag::OP_GT:
            filterOp -> valResult = filterOp -> left -> valGrid -> isGreaterThan(filterOp -> right -> valGrid);
            break;
        case Filter::Tag::OP_LE:
            filterOp -> valResult = ! filterOp -> left -> valGrid -> isGreaterThan(filterOp -> right -> valGrid);
            break;
        case Filter::Tag::OP_GE:
            filterOp -> valResult = ! filterOp -> left -> valGrid -> isLessThan(filterOp -> right -> valGrid);
            break;
        default:
            filterOp -> valResult = false;
        }
    }
    
    void visitExpr(Filter::Expr * expr) {
        expr -> valGrid = expr -> expr -> valGrid;
    }
    
    void visitCol(Filter::Col * col);
    
    void visitOp(Filter::Op * op) {
    }
    
    void visitValue(Filter::Value * value) {
        switch (value -> type) {
        case TableDataType::t_long:
            value -> valGrid -> setDataValueNumber(value -> value, 8);
            break;
        case TableDataType::t_double:
            value -> valGrid -> setDataValueFloat(* (double *) & value -> value, 8);
            break;
        case TableDataType::t_string:
            value -> valGrid -> setDataValueArray((ByteBufType) (value -> value & 0xffffffff), value -> value >> 32);
            break;
        case TableDataType::t_null:
            value -> valGrid -> setNull();
            break;
        default:
            value -> valGrid -> setNull();
        }
    }
};

#endif // CALCULATOR_H
