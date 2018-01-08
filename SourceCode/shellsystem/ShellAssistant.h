#ifndef SHELL_ASSISTANT_H_
#define SHELL_ASSISTANT_H_

#include "ShellClass.h"
#include "ShellLexerAssistant.h"

/**
 *  运行时需要的数据，写到类里面可以在最后自动调用析构函数
 */
class RunningData {
    
public:
    //缓存页管理器
    BufPageManager * bufPageManager;
    //运行语境的数据库
    TableManager * database;
    //运行语境最近操作的数据表，不需要析构
    Table * table;
    //首次运行标记，用来产生">>>"
    bool firstRoundFlag;
    
    RunningData() {
        bufPageManager = NULL;
        database = NULL;
        table = NULL;
        firstRoundFlag = true;
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
 *  需要的函数
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
TableRow * genTableRow(UnionValueList * sqlRow, Table * table, std::string & errorMessage) {
    std::stringstream ssbuf;
    TableHeader * tableHeader = table -> getTableHeader();
    /*
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
    */
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
            //std::cout << "sqlValue -> dt.d = " << sqlValue -> dt.d << std::endl;
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
        //std::cout << "genTableRow flag 1 " << std::endl;
        if (tableColumn -> isUnique()) {
            if (tableColumn -> hasTreeIndex() ||
                tableColumn -> hasHashIndex()) {
                //B+树索引
                //std::cout << "genTableRow flag 2 " << std::endl;
                TreeIndex * treeIndex = (TreeIndex *) indexManager -> getIndexById(i);
                //std::cout << "genTableRow flag 4 " << std::endl;
                if (treeIndex -> containKey(tableGrid -> getDataValueNumber())) {
                    //std::cout << "genTableRow flag 3 " << std::endl;
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

bool checkTableNameList(StringList * & tbNameList, UnionWhereClause * whList, std::string & errorMessage) {
    std::stringstream ssbuf;
    //检查数据表是否存在
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        if (!cur.database -> hasOpenedTable(* tbNameList -> at(i))) {
            ssbuf << "在WHERE语句中声明的数据表" << * tbNameList -> at(i) << "不存在";
            ssbuf >> errorMessage;
            return false;
        }
    }
    //去掉重复数据表
    bool errorFlag = false;
    StringList * tbNameList2 = new StringList();
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        std::string * tbName = tbNameList -> at(i);
        int cnt = 0;
        for (int j = 0; j < (int) tbNameList2 -> size(); j ++) {
            if (* tbNameList2 -> at(j) == * tbName) {
                cnt ++;
            }
        }
        if (cnt == 0) {
            tbNameList2 -> push_back(tbName);
        } else {
            if (cnt == 1) {
                ssbuf << * tbNameList -> at(i) << ", ";
            }
            errorFlag = true;
            delete tbNameList -> at(i);
            tbNameList -> at(i) = NULL;
        }
    }
    delete tbNameList;
    tbNameList = tbNameList2;
    if (errorFlag) {
        ssbuf >> errorMessage;
        errorMessage = std::string("在FROM语句中有重复的数据表:") + errorMessage;
        return false;
    }
    /*
    std::cout << "剩余数据表: ";
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        std::cout << * tbNameList -> at(i) << ", ";
    }
    std::cout << std::endl;
    */
    //检查用到的数据表是否列出
    for (int j = 0; j < (int) whList -> size(); j ++) {
        /*
        std::cout << "whList[" << j << "] = {";
        std::cout << * whList -> at(j) -> left -> tb << "." << * whList -> at(j) -> left -> col << ", ";
        std::cout << (int) whList -> at(j) -> op << ", " << whList -> at(j) -> ty << ", ";
        if (whList -> at(j) -> ty == 2) {
        std::cout << * whList -> at(j) -> right.uc -> tb << "." << * whList -> at(j) -> right.uc -> col << "}" << std::endl;
        } else {
        std::cout << "continue" << std::endl;
        }
        */
        std::string * tbName = whList -> at(j) -> left -> tb;
        int i;
        for (i = 0; i < (int) tbNameList -> size(); i ++) {
            if (* tbName == * tbNameList -> at(i)) {
                break;
            }
        }
        if (i == (int) tbNameList -> size()) {
            ssbuf << "在WHERE语句中需要用到数据表" << * tbName << "但在FROM语句中未声明";
            ssbuf >> errorMessage;
            return false;
        }
        if (whList -> at(j) -> ty != 2) {
            continue;
        }
        tbName = whList -> at(j) -> right.uc -> tb;
        for (i = 0; i < (int) tbNameList -> size(); i ++) {
            if (* tbName == * tbNameList -> at(i)) {
                break;
            }
        }
        if (i == (int) tbNameList -> size()) {
            ssbuf << "在WHERE语句中需要用到数据表" << * tbName << "但在FROM语句中未声明";
            ssbuf >> errorMessage;
            return false;
        }
    }
    //检查没有用到的数据表
    if ((int) tbNameList -> size() == 1) {
        return true;
    }
    std::vector < bool > useful;
    useful.resize(tbNameList -> size());
    for (int i = 0; i < (int) useful.size(); i ++) {
        useful[i] = false;
    }
    for (int j = 0; j < (int) whList -> size(); j ++) {
        std::string * tbName = whList -> at(j) -> left -> tb;
        int i;
        for (i = 0; i < (int) tbNameList -> size(); i ++) {
            if (* tbName == * tbNameList -> at(i)) {
                useful[i] = true;
                break;
            }
        }
        if (whList -> at(j) -> ty != 2) {
            continue;
        }
        tbName = whList -> at(j) -> right.uc -> tb;
        for (i = 0; i < (int) tbNameList -> size(); i ++) {
            if (* tbName == * tbNameList -> at(i)) {
                useful[i] = true;
                break;
            }
        }
    }
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        if (useful[i] == false) {
            ssbuf << "在FROM语句中声明了数据表" << * tbNameList -> at(i) << "但在WHERE语句中未使用";
            ssbuf >> errorMessage;
            return false;
        }
    }
    return true;
}

bool checkSetClause(std::string * tbName, UnionSetClause * scList, std::string & errorMessage) {
    std::stringstream ssbuf;
    Table * table = cur.database -> getTableByName(* tbName);
    //检查是否包含这些列
    for (int i = 0; i < (int) scList -> size(); i ++) {
        std::string * colName = scList -> at(i) -> col;
        if (! table -> getTableHeader() -> hasColumn(* colName)) {
            ssbuf << "在数据表" << * tbName << "没有数据列:" << * colName;
            ssbuf >> errorMessage;
            return false;
        }
    }
    //检查重复的数据列
    bool errorFlag = false;
    for (int i = 0; i < (int) scList -> size(); i ++) {
        std::string * colNameI = scList -> at(i) -> col;
        int cnt = 0;
        for (int j = 0; j < i; j ++) {
            std::string * colNameJ = scList -> at(i) -> col;
            if (* colNameI == * colNameJ) {
                cnt ++;
            }
        }
        if (cnt >= 1) {
            errorFlag = true;
            if (cnt == 1) {
                ssbuf << * colNameI << ", ";
            }
        }
    }
    if (errorFlag) {
        ssbuf >> errorMessage;
        errorMessage = std::string("在SET语句中有重复的数据列:") + errorMessage;
        return false;
    }
    //检查数据类型、NULL兼容性
    for (int i = 0; i < (int) scList -> size(); i ++) {
        std::string * colName = scList -> at(i) -> col;
        UnionValue * uv = scList -> at(i) -> uv;
        TableColumn * tbCol = table -> getTableHeader() -> getColumnByName(* colName);
        TableDataType spTy = getSuperType(tbCol -> getDataType());
        if (uv -> ty == 0) {
            //右边是NULL常量
            if (! tbCol -> allowNull()) {
                ssbuf << "数据表" << * tbName << "的数据列" << * colName << "不允许NULL值";
                ssbuf >> errorMessage;
                return false;
            }
        } else if (uv -> ty == 1) {
            //右边是整数常量
            if (spTy != TableDataType::t_long &&
                spTy != TableDataType::t_double) {
                ssbuf << "数据表" << * tbName << "的数据列" << * colName << "是" << getTypeNameInSQL(tbCol -> getDataType()) << "类型，不能被赋值为整数";
                ssbuf >> errorMessage;
                return false;
            }
        } else if (uv -> ty == 2) {
            //右边是浮点数常量
            if (spTy != TableDataType::t_double) {
                ssbuf << "数据表" << * tbName << "的数据列" << * colName << "是" << getTypeNameInSQL(tbCol -> getDataType()) << "类型，不能被赋值为浮点数";
                ssbuf >> errorMessage;
                return false;
            }
        } else if (uv -> ty == 3) {
            //右边是字符串常量
            if (spTy != TableDataType::t_string) {
                ssbuf << "数据表" << * tbName << "的数据列" << * colName << "是" << getTypeNameInSQL(tbCol -> getDataType()) << "类型，不能被赋值为字符串";
                ssbuf >> errorMessage;
                return false;
            }
        } 
    }
    return true;
}

bool checkSelector(UnionColList * & sColList, StringList * tbNameList, std::string & errorMessage) {
    std::stringstream ssbuf;
    //SELECT * FROM语句
    if (sColList == NULL) {
        sColList = new UnionColList();
        for (int i = 0; i < (int) tbNameList -> size(); i ++) {
            Table * tb = cur.database -> getTableByName(* tbNameList -> at(i));
            for (int j = 0; j < tb -> getNCol(); j ++) {
                TableColumn * tc = tb -> getTableHeader() -> getColumnById(j);
                UnionCol * uc = new UnionCol();
                uc -> tb = tbNameList -> at(i);
                uc -> col = new std::string(tc -> getName());
                uc -> tc = tc;
                sColList -> push_back(uc);
            }
        }
        return true;
    }
    //检查数据表都已经出现过
    //std::cout << "whList -> size() = " << whList -> size() << std::endl;
    for (int i = 0; i < (int) sColList -> size(); i ++) {
        std::string * tbName = sColList -> at(i) -> tb;
        int j;
        for (j = 0; j < (int) tbNameList -> size(); j ++) {
            if (* tbNameList -> at(j) == * tbName) {
                break;
            }
        }
        if (j == (int) tbNameList -> size()) {
            ssbuf << "在SELECT语句中需要用到数据表" << * tbName << "但在FROM语句中未声明";
            ssbuf >> errorMessage;
            return false;
        }
    }   
    return true;
}

bool cmpUnionValue(UnionValue * uvL, UnionWhereItem::OpTag op, UnionValue * uvR) {
    bool satisfy = false;
    if (uvL -> ty == 0) {
        //左边是NULL
        if (uvR -> ty == 0) {
            //右边是NULL
            satisfy = (op == UnionWhereItem::OpTag::OP_EQ);
        } else {
            //右边是整数、浮点数、字符串
            satisfy = (op == UnionWhereItem::OpTag::OP_NE);
        }
    } else if (uvL -> ty == 1) {
        //左边是整数
        uint64 vl = uvL -> dt.u;
        if (uvR -> ty == 1) {
            //右边是整数
            uint64 vr = uvR -> dt.u;
            //std::cout << "vl = " << vl << ", vr = " << vr << ", op = " << (int) op << std::endl;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else if (uvR -> ty == 2) {
            //右边是浮点数
            double vr = uvR -> dt.d;
            //std::cout << "vL = " << vl << ", vr = " << vr << std::endl;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else {
            //右边是NULL、字符串
            satisfy = (op == UnionWhereItem::OpTag::OP_NE);
        }
    } else if (uvL -> ty == 2) {
        //左边是浮点数
        double vl = uvL -> dt.d;
        if (uvR -> ty == 1) {
            //右边是整数
            uint64 vr = uvR -> dt.u;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else if (uvR -> ty == 2) {
            //右边是浮点数
            double vr = uvR -> dt.d;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else {
            //右边是NULL、字符串
            satisfy = (op == UnionWhereItem::OpTag::OP_NE);
        }
    } else if (uvL -> ty == 3) {
        //左边是字符串
        std::string vl(* uvL -> dt.s);
        if (uvR -> ty == 3) {
            //右边是整数
            std::string vr(* uvR -> dt.s);
            //std::cout << "vl = '" << vl << "', vr = '" << vr << "'" << std::endl;
            switch (op) {
            case UnionWhereItem::OpTag::OP_EQ:
                satisfy = (vl == vr);
                break;
            case UnionWhereItem::OpTag::OP_NE:
                satisfy = (vl != vr);
                break;
            case UnionWhereItem::OpTag::OP_LT:
                satisfy = (vl < vr);
                break;
            case UnionWhereItem::OpTag::OP_GT:
                satisfy = (vl > vr);
                break;
            case UnionWhereItem::OpTag::OP_LE:
                satisfy = (vl <= vr);
                break;
            case UnionWhereItem::OpTag::OP_GE:
                satisfy = (vl >= vr);
                break;
            }
        } else {
            //右边是NULL、整数、浮点数
            satisfy = (op == UnionWhereItem::OpTag::OP_NE);
        }
    }
    return satisfy;
}

void runUpdate(std::string * tbName, UnionSetClause * scList, UnionWhereClause * whList) {
    //涉及的数据行
    std::vector < std::pair < int, int > > rowList;
    //获取数据表和迭代器
    Table * table = cur.database -> getTableByName(* tbName);
    TableIterator * ite = table -> beginIte();
    //用迭代器枚举每一行
    while (!ite -> isEnd()) {
        //依次检查每一条WHERE语句是否满足
        bool satisfy = true;
        int i1;
        for (i1 = 0; i1 < (int) whList -> size() && satisfy; i1 ++) {
            UnionWhereItem * wh = whList -> at(i1);
            //左边的UnionValue
            UnionValue uvL;
            TableDataType suL = getSuperType(wh -> left -> tc -> getDataType());
            if (ite -> getTableRow() -> getGridByName(* wh -> left -> col) -> isNull()) {
                //左边是NULL
                uvL.ty = 0;
            } else {
                switch (suL) {
                case TableDataType::t_long:
                    //左边是整数
                    uvL.ty = 1;
                    uvL.dt.u = ite -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataValueNumber();
                    break;
                case TableDataType::t_double:
                    //左边是浮点数
                    uvL.ty = 2;
                    uvL.dt.d = ite -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataValueFloat();
                    break;
                case TableDataType::t_string:
                    //左边是字符串
                    uvL.ty = 3;
                    ByteBufType dpL = ite -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataPointer();
                    uvL.dt.s = new std::string((char *) dpL);
                    break;
                }
            }
            //右边的UnionValue
            UnionValue uvR;
            switch (wh -> ty) {
            case 0:
                //右边是NULL
                uvR.ty = 0;
                break;
            case 1:
                //右边是常量
                uvR = * wh -> right.uv;
                break;
            case 2:
                //右边是数据格
                TableDataType suR = getSuperType(wh -> right.uc -> tc -> getDataType());
                if (ite -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> isNull()) {
                    //右边是NULL
                    uvR.ty = 0;
                } else {
                    switch (suR) {
                    case TableDataType::t_long:
                        //右边是整数
                        uvR.ty = 1;
                        uvR.dt.u = ite -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataValueNumber();
                        break;
                    case TableDataType::t_double:
                        //右边是浮点数
                        uvR.ty = 2;
                        uvR.dt.d = ite -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataValueFloat();
                        break;
                    case TableDataType::t_string:
                        //右边是字符串
                        uvR.ty = 3;
                        ByteBufType dpR = ite -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataPointer();
                        uvR.dt.s = new std::string((char *) dpR);
                        break;
                    }
                }
                break;
            }
            //计算
            satisfy = satisfy && cmpUnionValue(& uvL, wh -> op, & uvR);
        }
        //如果满足条件，就把这一行加入待删除列表，因为直接删除会影响迭代器
        if (satisfy) {
            rowList.push_back(make_pair(ite -> getPageId(), ite -> getSlotId()));
        }
        //下一行的迭代器
        ite -> next();
    }
    //删除或者更新
    std::cout << "共找到" << (int) rowList.size() << "条符合条件的记录" << std::endl;
    for (int i = 0; i < (int) rowList.size(); i ++) {
        int pageId = rowList[i].first;
        int slotId = rowList[i].second;
        if (scList == NULL) {
            table -> eraseRow(pageId, slotId);
        } else {
            TableRow * row = table -> getRow(pageId, slotId);
            for (int j = 0; j < (int) scList -> size(); j ++) {
                UnionSetItem * sc = scList -> at(j);
                TableGrid * grid = row -> getGridByName(* sc -> col);
                if (sc -> uv -> ty == 0) {
                    grid -> setNull();
                } else if (sc -> uv -> ty == 1) {
                    grid -> setDataValueNumber(sc -> uv -> dt.u, grid -> getDataLength());
                } else if (sc -> uv -> ty == 2) {
                    grid -> setDataValueFloat(sc -> uv -> dt.d, grid -> getDataLength());
                } else if (sc -> uv -> ty == 3) {
                    std::string * s = sc -> uv -> dt.s;
                    grid -> setDataValueArray((ByteBufType) s -> c_str(), s -> length());
                }
            }
            table -> updateRow(pageId, slotId, row);
            delete row;
        }
    }
    std::cout << "共" << (scList == NULL ? "删除" : "更新") << (int) rowList.size() << "条记录" << std::endl;
}

void runDelete(std::string * tbName, UnionWhereClause * whList) {
    runUpdate(tbName, NULL, whList);
}

void runSelect(UnionColList * sColList, StringList * tbNameList, UnionWhereClause * whList) {
    int printCnt = 0;
    bool iteFlag = true;
    std::vector < Table * > tbList;
    std::vector < TableIterator * > iteList;
    //获取数据表列表和迭代器列组
    //std::cout << "runSelect() flag 1" << std::endl;
    for (int i = 0; i < (int) tbNameList -> size(); i ++) {
        std::string * tbName = tbNameList -> at(i);
        Table * table = cur.database -> getTableByName(* tbName);
        tbList.push_back(table);
        //std::cout << "runSelect() flag 1-2" << std::endl;
        iteList.push_back(table -> beginIte());
        //std::cout << "runSelect() flag 1-3" << std::endl;
        if (iteList.back() -> isEnd()) {
            iteFlag = false;
        }
    }
    //std::cout << "runSelect() flag 2" << std::endl;
    //循环直到全部枚举完毕
    while (iteFlag) {
        //依次检查每一条WHERE语句是否满足
        bool satisfy = true;
        int i1;
        for (i1 = 0; i1 < (int) whList -> size() && satisfy; i1 ++) {
            UnionWhereItem * wh = whList -> at(i1);
            //找出左值描述的数据表，在数据表列表和迭代器组里面的编号，如果右值也是数据表就也顺便找出来
            int iL = 0, iR = 0;
            for (int i = 0; i < (int) tbList.size(); i ++) {
                std::string tbName = tbList[i] -> getName();
                if (tbName == * wh -> left -> tb) {
                    iL = i;
                }
                if (wh -> ty == 2 && tbName == * wh -> right.uc -> tb) {
                    iR = i;
                }
            }
            //左边的UnionValue
            UnionValue uvL;
            TableDataType suL = getSuperType(wh -> left -> tc -> getDataType());
            if (iteList[iL] -> getTableRow() -> getGridByName(* wh -> left -> col) -> isNull()) {
                //左边是NULL
                uvL.ty = 0;
            } else {
                switch (suL) {
                case TableDataType::t_long:
                    //左边是整数
                    uvL.ty = 1;
                    uvL.dt.u = iteList[iL] -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataValueNumber();
                    break;
                case TableDataType::t_double:
                    //左边是浮点数
                    uvL.ty = 2;
                    uvL.dt.d = iteList[iL] -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataValueFloat();
                    break;
                case TableDataType::t_string:
                    //左边是字符串
                    uvL.ty = 3;
                    ByteBufType dpL = iteList[iL] -> getTableRow() -> getGridByName(* wh -> left -> col) -> getDataPointer();
                    uvL.dt.s = new std::string((char *) dpL);
                    break;
                }
            }
            //右边的UnionValue
            UnionValue uvR;
            switch (wh -> ty) {
            case 0:
                //右边是NULL
                uvR.ty = 0;
                break;
            case 1:
                //右边是常量
                uvR = * wh -> right.uv;
                break;
            case 2:
                //右边是数据格
                TableDataType suR = getSuperType(wh -> right.uc -> tc -> getDataType());
                if (iteList[iR] -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> isNull()) {
                    //右边是NULL
                    uvR.ty = 0;
                } else {
                    switch (suR) {
                    case TableDataType::t_long:
                        //右边是整数
                        uvR.ty = 1;
                        uvR.dt.u = iteList[iR] -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataValueNumber();
                        break;
                    case TableDataType::t_double:
                        //右边是浮点数
                        uvR.ty = 2;
                        uvR.dt.d = iteList[iR] -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataValueFloat();
                        break;
                    case TableDataType::t_string:
                        //右边是字符串
                        uvR.ty = 3;
                        ByteBufType dpR = iteList[iR] -> getTableRow() -> getGridByName(* wh -> right.uc -> col) -> getDataPointer();
                        uvR.dt.s = new std::string((char *) dpR);
                        break;
                    }
                }
                break;
            }
            //计算
            satisfy = satisfy && cmpUnionValue(& uvL, wh -> op, & uvR);
        }
        //如果满足条件，就按照SELECT语句打印一行
        //std::cout << "runSelect() flag 3 satisfy = " << satisfy << std::endl;
        if (satisfy) {
            printCnt ++;
            for (int i = 0; i < (int) sColList -> size(); i ++) {
                UnionCol * uc = sColList -> at(i);
                //找到它是哪个表
                int iT = 0;
                for (int i = 0; i < (int) tbNameList -> size(); i ++) {
                    if (* tbNameList -> at(i) == * uc -> tb) {
                        iT = i;
                        break;
                    }
                }
                //输出到屏幕
                //std::cout << "runSelect() flag 3 iT = " << iT << std::endl;
                iteList[iT] -> getTableRow() -> getGridByName(* uc -> col) -> stdCout();
                std::cout << (i < (int) sColList -> size() - 1 ? ", " : ".");
            }
            std::cout << std::endl;
        }
        //前进到下一个迭代器组
        //std::cout << "runSelect() flag 3-5" << std::endl;
        int i2;
        for (i2 = 0; i2 < (int) iteList.size(); i2 ++) {
            //std::cout << "runSelect() flag 3-5  i2 = " << i2 << std::endl;
            iteList[i2] -> next();
            if (! iteList[i2] -> isEnd()) {
                break;
            }
        }
        //std::cout << "runSelect() flag 4" << std::endl;
        //没有下一个迭代器组
        if (i2 == (int) iteList.size()) {
            iteFlag = false;
        } else {
            for (int j = 0; j < i2; j ++) {
                delete iteList[j];
                iteList[j] = tbList[j] -> beginIte();
            }
        }
        //std::cout << "runSelect() flag 5" << std::endl;
        //for (int i = 0; i < (int) iteList.size(); i ++) {
            //std::cout << "    iteList[" << i << "]: pageId = " << iteList[i] -> pageId << ", slotId = " << iteList[i] -> slotId << std::endl;
        //}
    }
    std::cout << "共找到" << printCnt << "条符合条件的记录" << std::endl;
    for (int i = 0; i < (int) iteList.size(); i ++) {
        delete iteList[i];
    }
}

bool runCreateIndex(std::string * tbName, std::string * colName) {
    std::stringstream ssbuf;
    //检查是否存在这个数据列
    Table * table = cur.database -> getTableByName(* tbName);
    if (!table -> getTableHeader() -> hasColumn(* colName)) {
        std::cout << "数据表" << * tbName << "中没有数据列:" << * colName << std::endl;
        return false;
    }
    cur.table = table;
    //检查这个数据列是否已经有索引
    TableColumn * tc = table -> getTableHeader() -> getColumnByName(* colName);
    if (tc -> hasTreeIndex() || tc -> hasHashIndex()) {
        std::cout << "数据表" << * tbName << "的数据列" << * colName << "已经拥有索引" << std::endl;
        return false;
    }
    //在数据表中标记这一列已有索引
    tc -> setHasTreeIndex(true);
    table -> writeBackTableHeader();
    //创建索引
    //std::cout << "runCreateIndex(...) flag 1" << std::endl;
    TreeIndex * trIdx = new TreeIndex(cur.bufPageManager, *tbName, tc);
    return false;
    //std::cout << "runCreateIndex(...) flag 2" << std::endl;
    TableIterator * ite = table -> beginIte();
    while (!ite -> isEnd()) {
        uint64 value = ite -> getTableRow() -> getGridByName(* colName) -> getDataValueNumber();
        TreeNodeKeyCell keyCell(
            ite -> getTableRow() -> getGridByName(* colName) -> getDataValueNumber(), 
            ite -> getPageId(), 
            ite -> getSlotId()
        );
        trIdx -> insertKey(& keyCell);
    }
    //std::cout << "runCreateIndex(...) flag 3" << std::endl;
    //真的添加索引
    table -> getIndexManager() -> addIndex(trIdx, *colName);
    //std::cout << "runCreateIndex(...) flag 4" << std::endl;
}

bool runRemoveIndex(std::string * tbName, std::string * colName) {
    std::stringstream ssbuf;
    //检查是否存在这个数据列
    Table * table = cur.database -> getTableByName(* tbName);
    if (!table -> getTableHeader() -> hasColumn(* colName)) {
        std::cout << "数据表" << * tbName << "中没有数据列:" << * colName << std::endl;
        return false;
    }
    cur.table = table;
    //检查这个数据列是否还没有索引
    TableColumn * tc = table -> getTableHeader() -> getColumnByName(* colName);
    if (!tc -> hasTreeIndex() && !tc -> hasHashIndex()) {
        std::cout << "数据表" << * tbName << "的数据列" << * colName << "尚未拥有索引" << std::endl;
        return false;
    }
    //真的删除索引，并删除文件
    std::string idxFileName = table -> getIndexManager() -> getIndexByName(* colName) -> getFileName();
    table -> getIndexManager() -> removeIndex(* colName);
    remove(idxFileName.c_str());
}












#endif // SHELL_ASSISTANT_H_
