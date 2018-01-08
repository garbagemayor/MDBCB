%{
    #include "../ShellAssistant.h"
    #include "lex.yy.c"
    
    int yylex();
    int yyerror(const char *);
%}

%token  DATABASE
%token  DATABASES
%token  TABLE
%token  TABLES
%token  SHOW
%token  CREATE
%token  DROP
%token  USE
%token  PRIMARY
%token  KEY
%token  NOT
%token  NNULL
%token  INSERT
%token  INTO
%token  VALUES
%token  DELETEE
%token  FROM
%token  WHERE
%token  UPDATE
%token  SET
%token  SELECT
%token  IS
%token  DESC
%token  REFERENCES
%token  INDEX
%token  AND
%token  DATEE
%token  FOREIGN
%token  BOOLL
%token  CHARR
%token  SHORTT
%token  INTEGER
%token  LONGG
%token  FLOATT
%token  DOUBLEE
%token  VARCHAR
%token  LOB
%token  OP_EQ
%token  OP_NE
%token  OP_LE
%token  OP_GE
%token  OP_LT
%token  OP_GT

%token  ';' ',' '(' ')' '.' 
%token <v_u> VALUE_UINT64
%token <v_s> VALUE_STRING
%token <v_d> VALUE_DOUBLE
%token <v_s> IDENTIFIER

%type <v_s> deleteFromTb
%type <v_s> updateTb

%type <u_fl> fieldList
%type <u_fd> field

%type <u_wc> whereClause
%type <u_wc> whereList
%type <u_wi> whereItem
%type <v_u> op

%type <u_cl> selector
%type <u_co> col

%type <u_si> setItem
%type <u_sc> setList
%type <u_sc> setClause

%type <u_vt> valueLists
%type <u_vr> valueList
%type <u_va> value

%type <v_sl> identList
%type <v_s> ident
%type <v_t> type

%union {
    
    UnionFieldList * u_fl;
    UnionField * u_fd;
    StringList * v_sl;
    
    UnionValue * u_va;
    UnionValueList * u_vr;
    UnionValueLists * u_vt;
    
    UnionWhereClause * u_wc;
    UnionWhereItem * u_wi;
    
    UnionSetItem * u_si;
    UnionSetClause * u_sc;
    
    UnionColList * u_cl;
    UnionCol * u_co;
    
    uint64 v_u;
    double v_d;
    std::string * v_s;
    
    TableDataType v_t;
}
%%


program:
        program stmt
        {
            setCmdColor(1);
            std::cout << ">>>";
        }
        |
        /* empty */
        {
            setCmdColor(1);
            if (cur.firstRoundFlag) {
                std::cout << ">>>";
            }
        }
;

stmt:
        sysStmt 
        {
        }
        |
        dbStmt
        {
        }
        |
        tbStmt
        {
        }
        |
        idxStmt
        {
        }
        |
        endLine
        {
        }
;

sysStmt:
        SHOW DATABASES ';' endLine
        {
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
            //遍历所有文件夹
            struct _finddata_t fb;
            int handle = _findfirst("*", &fb);
            std::vector < std::string > dbList;
            if (handle != -1) {
                do {
                    int noFile = strcmp(fb.name, "..");
                    if (0 != noFile && fb.attrib == 16) {
                        std::string name = fb.name;
                        if (name != "." && name != "..") {
                            //找到一个文件夹，就是找到一个数据库
                            dbList.push_back(fb.name);
                        }
                    }
                } while (_findnext(handle, &fb) == 0);
                _findclose(handle);
            }
            std::cout << "当前目录下共有" << dbList.size() << "个数据库:" << std::endl;
            for (int i = 0; i < (int) dbList.size(); i ++) {
                std::cout << dbList[i] << (i < (int) dbList.size() - 1 ? ", " : ".");
            }
            std::cout << std::endl;
        }
;

dbStmt:
        CREATE DATABASE ident ';' endLine
        {
            //新建一个数据库
            std::string * dbName = $3;
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
            //如果已有这个数据库，报错
            if (access(dbName -> c_str(), W_OK) == 0) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "已有数据库:" << * dbName << std::endl;
            } else {
                //新建这个数据库，并打开
                mkdir(dbName -> c_str());
                chdir(dbName -> c_str());
                cur.database = new TableManager(cur.bufPageManager, * dbName);
            }
        }
        |
        DROP DATABASE ident ';' endLine
        {
            //删除一个数据库
            std::string * dbName = $3;
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
            //如果不存在这个数据库，报错
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "不存在数据库:" << * dbName << std::endl;
            } else {
                //删除这个数据库
                int rmrs = removeDir(dbName -> c_str());
                if (rmrs == -1) {
                    std::cout << "删不掉这个数据库" << std::endl;
                }
            }
        }
        |
        USE ident ';' endLine
        {
            //打开一个数据库
            std::string * dbName = $2;
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
            //如果不存在这个数据库，报错
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.USE: error" << std::endl;
                std::cout << "不存在数据库:" << * dbName << std::endl;
            } else {
                //打开这个数据库
                chdir(dbName -> c_str());
                cur.database = new TableManager(cur.bufPageManager, * dbName);
            }
        }
        |
        USE ';' endLine
        {
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
        }
        |
        SHOW TABLES ';' endLine
        {
            //查看这个数据库的所有数据表
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.SHOW TABLES: error" << std::endl;
                std::cout << "没有正在使用的数据库" << std::endl;
            } else {
                //打印数据库中的数据表
                int nTab = cur.database -> getNTable();
                std::cout << "数据库" << cur.database -> getName() << "共有" << nTab << "个数据表:" << std::endl;
                for (int i = 0; i < nTab; i ++) {
                    std::cout << cur.database -> getTableById(i) -> getName() << ( i < nTab - 1 ? ", " : ".");
                }
                std::cout << std::endl;
            }
        }
;

tbStmt:
        CREATE TABLE ident '(' fieldList ')' ';' endLine
        {
            //在已经打开的数据库中创建一个数据表
            std::string * tbName = $3;
            UnionFieldList * fieldList = $5;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "没有已经打开的数据库:" << * tbName << std::endl;
            } else if (cur.database -> hasOpenedTable(* tbName)) {
                //如果已有同名数据表，报错
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "已有这个数据表:" << * tbName << std::endl;
            } else {
                //整理fieldList，获取到所有被设为PRIMARY KEY的列名
                StringList pkList;
                for (int i = 0; i < (int) fieldList -> size(); i ++) {
                    if (fieldList -> at(i) -> ty == 2) {
                        StringList * pkListI = fieldList -> at(i) -> dt.pk;
                        for (int j = 0; j < (int) pkListI -> size(); j ++) {
                            pkList.push_back(pkListI -> at(j));
                        }
                    }
                }
                //整理fieldList，把第一个可以被设为PRIMARY KEY的列设置一下，剩下的就无视掉
                for (int i = 0; i < (int) pkList.size(); i ++) {
                    int j;
                    for (j = 0; j < (int) fieldList -> size(); j ++) {
                        if ($5 -> at(j) -> ty == 1) {
                            if ($5 -> at(j) -> dt.tc -> getName() == * pkList[i]) {
                                $5 -> at(j) -> dt.tc -> setPrimaryKey(true);
                                break;
                            }
                        }
                    }
                    if (j < (int) fieldList -> size()) {
                        break;
                    }
                }
                //创建数据表
                TableHeader * tbHd = new TableHeader();
                tbHd -> setName(* tbName);
                for (int i = 0; i < (int) fieldList -> size(); i ++) {
                    UnionField * fd = fieldList -> at(i);
                    if (fd -> ty == 1) {
                        fd -> dt.tc -> setConstant();
                        tbHd -> addColumn(fd -> dt.tc);
                    }
                }
                tbHd -> setConstant();
                cur.database -> createTable(tbHd);
                cur.table = cur.database -> getTableByName(* tbName);
            }
        }
        |
        DROP TABLE ident ';' endLine
        {
            //在已经打开的数据库中删除一个数据表
            std::string * tbName = $3;
            std::cout << "DropTable flag 1" << std::endl;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                if (cur.table != NULL && cur.table -> getName() == * tbName) {
                    cur.table = NULL;
                }
                //删除数据表
                std::cout << "DropTable flag 2" << std::endl;
                cur.database -> eraseTable(* tbName);
                std::cout << "DropTable flag 3" << std::endl;
                //从文件夹中删除
                std::string fileName = * tbName + ".table";
                remove(fileName.c_str());
            }
        }
        |
        DESC ident ';' endLine
        {
            //打印数据表中的所有列
            std::string * tbName = $2;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                //打印数据表的列
                Table * table = cur.database -> getTableByName(* tbName);
                cur.table = table;
                int nCol = table -> getNCol();
                std::cout << "数据表" << * tbName << "共有" << nCol << "个数据列:" << std::endl;
                TableHeader * tbHd = table -> getTableHeader();
                for (int i = 0; i < nCol; i ++) {
                    TableColumn * tbCol = tbHd -> getColumnById(i);
                    std::cout << tbCol -> getName();
                    std::cout << " " << getTypeNameInSQL(tbCol -> getDataType());
                    if (!tbCol -> allowNull()) {
                        std::cout << " NOT NULL";
                    }
                    if (tbCol -> hasTreeIndex() || tbCol -> hasHashIndex()) {
                        std::cout << " WITH INDEX";
                    }
                    if (tbCol -> isPrimaryKey()) {
                        std::cout << " PRIMARY KEY";
                    }
                    std::cout << (i < nCol - 1 ? ", " : ".");
                }
                std::cout << std::endl;
            }
        }
        |
        DESC ';' endLine
        {
            //打印活跃的数据表中的所有列
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (cur.table == NULL) {
                //如果没有活跃的数据表，报错
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有活跃的数据表" << std::endl;
            } else {
                //打印数据表的列
                Table * table = cur.table;
                int nCol = table -> getNCol();
                std::cout << "数据表" << cur.table -> getName() << "共有" << nCol << "个数据列:" << std::endl;
                TableHeader * tbHd = table -> getTableHeader();
                for (int i = 0; i < nCol; i ++) {
                    TableColumn * tbCol = tbHd -> getColumnById(i);
                    std::cout << tbCol -> getName();
                    std::cout << " " << getTypeNameInSQL(tbCol -> getDataType());
                    if (!tbCol -> allowNull()) {
                        std::cout << " NOT NULL";
                    }
                    if (tbCol -> hasTreeIndex() || tbCol -> hasHashIndex()) {
                        std::cout << " WITH INDEX";
                    }
                    if (tbCol -> isPrimaryKey()) {
                        std::cout << " PRIMARY KEY";
                    }
                    std::cout << (i < nCol - 1 ? ", " : ".");
                }
                std::cout << std::endl;
            }
        }
        |
        INSERT INTO ident VALUES valueLists ';' endLine
        {
            //在数据表中插入若干行
            std::string * tbName = $3;
            UnionValueLists * rowList = $5;
            std::cout << "INSERT flag 1 " << std::endl;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                Table * table = cur.database -> getTableByName(* tbName);
                cur.table = table;
                //把数据一行一行的插入到表中
                int insertCnt = 0;
                for (int i = 0; i < (int) rowList -> size(); i ++) {
                    //创建数据库中的数据行
                    std::cout << "INSERT flag 2 " << std::endl;
                    UnionValueList * sqlRow = rowList -> at(i);
                    std::string errMsg;
                    TableRow * tableRow = genTableRow(sqlRow, table, errMsg);
                    if (tableRow == NULL) {
                        std::cout << "Parser.INSERT INTO: error" << std::endl;
                        std::cout << "输入的第" << i << "个数据行不符合数据表" << table -> getName() << "的格式要求" << std::endl;
                        std::cout << errMsg << std::endl;
                        continue;
                    }
                    std::cout << "INSERT flag 3 " << std::endl;
                    table -> insertRow(tableRow);
                    insertCnt += 1;
                }
                std::cout << "共添加" << insertCnt << "个数据行" << std::endl;
            }
        }
        |
        deleteFromTb WHERE whereClause ';' endLine
        {
            //删除一些数据行
            //把数据表放到vector里面，可以调用SELECT操作的检查函数
            std::string * tbName = $1;
            StringList * tbNameList = new StringList();
            tbNameList -> push_back(tbName);
            UnionWhereClause * whList = $3;
            std::string errMsg;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := DELETEE FROM ident WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!checkTableNameList(tbNameList, whList, errMsg)) {
                //检查whList和tbNameList的数据表是同一个集合
                std::cout << "Parser.<tbStmt := DELETEE FROM ident WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else {
                cur.table = cur.database -> getTableByName(* tbName);
                runDelete(tbName, whList);
            }
        }
        |
        updateTb SET setClause WHERE whereClause ';' endLine
        {
            //更新一些数据行
            //把数据表放到vector里面，可以调用SELECT操作的检查函数
            std::string * tbName = $1;
            StringList * tbNameList = new StringList();
            tbNameList -> push_back(tbName);
            UnionSetClause * scList = $3;
            UnionWhereClause * whList = $5;
            std::string errMsg;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := UPDATE ident SET setClause WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!checkTableNameList(tbNameList, whList, errMsg)) {
                //检查whList和tbNameList的数据表是同一个集合
                std::cout << "Parser.<tbStmt := UPDATE ident SET setClause WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else if (!checkSetClause(tbName, scList, errMsg)) {
                //检查setClause的数据列都是这个表中数据列，以及数据类型的兼容性
                std::cout << "Parser.<tbStmt := UPDATE ident SET setClause WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else {
                cur.table = cur.database -> getTableByName(* tbName);
                runUpdate(tbName, scList, whList);
            }
        }
        |
        SELECT selector FROM identList WHERE whereClause ';' endLine
        {
            //在数据表中查询
            UnionColList * sColList = $2;
            StringList * tbNameList = $4;
            UnionWhereClause * whList = $6;
            std::string errMsg;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!checkTableNameList(tbNameList, whList, errMsg)) {
                //检查whList和tbNameList的数据表是同一个集合
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else if (!checkSelector(sColList, tbNameList,errMsg)){
                //检查sColList的数据表是tbNameList的子集
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else {
                runSelect(sColList, tbNameList, whList);
            }
        }
;

deleteFromTb:
        DELETEE FROM ident
        {
            $$ = $3;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else {
                cur.table = cur.database -> getTableByName(* $3);
            }
        }
;

updateTb:
        UPDATE ident
        {
            $$ = $2;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else {
                cur.table = cur.database -> getTableByName(* $2);
            }
        }
;

idxStmt:
        CREATE INDEX ident '(' ident ')' ';' endLine
        {
            //给某列添加索引
            std::string * tbName = $3;
            std::string * colName = $5;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<idxStmt := CREATE INDEX ident '(' ident ')' ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.<idxStmt := CREATE INDEX ident '(' ident ')' ';' endLine>: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                runCreateIndex(tbName, colName);
            }
        }
        |
        DROP INDEX ident '(' ident ')' ';' endLine
        {
            //删除某列的索引
            std::string * tbName = $3;
            std::string * colName = $5;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<idxStmt := DROP INDEX ident '(' ident ')' ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.<idxStmt := DROP INDEX ident '(' ident ')' ';' endLine>: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                runRemoveIndex(tbName, colName);
            }
        }
;

fieldList:
        field
        {
            $$ = new UnionFieldList();
            $$ -> push_back($1);
        }
        |
        fieldList ',' field
        {
            $$ = $1;
            $$ -> push_back($3);
        }
;

field:
        ident type
        {
            std::string * colName = $1;
            
            $$ = new UnionField();
            $$ -> ty = 1;
            $$ -> dt.tc = new TableColumn();
            $$ -> dt.tc -> setName(* colName);
            $$ -> dt.tc -> setType($2);
            $$ -> dt.tc -> setAllowNull(true);
        }
        |
        ident type NOT NNULL
        {
            std::string * colName = $1;
            
            $$ = new UnionField();
            $$ -> ty = 1;
            $$ -> dt.tc = new TableColumn();
            $$ -> dt.tc -> setName(* colName);
            $$ -> dt.tc -> setType($2);
        }
        |
        PRIMARY KEY '(' identList ')'
        {
            StringList * colList = $4;
            $$ = new UnionField();
            $$ -> ty = 2;
            $$ -> dt.pk = colList;
        }
        |
        FOREIGN KEY '(' ident ')' REFERENCES ident '(' ident ')'
        {
            //去一个已有数据表中把一个数据列的属性复制过来
            std::string * colName = $4;
            std::string * tbName = $7;
            std::string * colName0 = $9;
            $$ = new UnionField();
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<field := FOREIGN KEY '(' ident ')' REFERENCES ident '(' ident ')'>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.<field := FOREIGN KEY '(' ident ')' REFERENCES ident '(' ident ')'>: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else if (!cur.database -> getTableByName(* tbName) -> getTableHeader() -> hasColumn(* colName0)) { 
                //如果没有这个数据列，报错
                std::cout << "Parser.<field := FOREIGN KEY '(' ident ')' REFERENCES ident '(' ident ')'>: error" << std::endl;
                std::cout << "数据表" << * $7 << "中没有数据列:" << * colName0 << std::endl;
            } else {
                TableColumn * tc = cur.database -> getTableByName(* tbName) -> getTableHeader() -> getColumnByName(* colName0);
                $$ -> ty = 1;
                $$ -> dt.tc = new TableColumn();
                $$ -> dt.tc -> setName(* colName);
                $$ -> dt.tc -> setType(tc -> getDataType());
                $$ -> dt.tc -> setUnique(tc -> isUnique());
                $$ -> dt.tc -> setAllowNull(tc -> allowNull());
                $$ -> dt.tc -> setPrimaryKey(tc -> hasDefault());
                $$ -> dt.tc -> setHasTreeIndex(tc -> hasTreeIndex());
                $$ -> dt.tc -> setHasHashIndex(tc -> hasHashIndex());
            }
        }
;

valueLists:
        '(' valueList ')'
        {
            $$ = new UnionValueLists();
            $$ -> push_back($2);
        }
        |
        valueLists ',' '(' valueList ')'
        {
            $$ = $1;
            $$ -> push_back($4);
        }
;

valueList:
        value
        {
            $$ = new UnionValueList();
            $$ -> push_back($1);
        }
        |
        valueList ',' value
        {
            $$ = $1;
            $$ -> push_back($3);
        }
;

whereClause:
        whereList
        {
            $$ = $1
        }
        |
        /* empty */
        {
            $$ = new UnionWhereClause();
        }
;

whereList:
        whereItem
        {
            $$ = new UnionWhereClause();
            if ($1 != NULL) {
                $$ -> push_back($1);
            }
        }
        |
        whereClause AND whereItem
        {
            $$ = $1;
            if ($3 != NULL) {
                $$ -> push_back($3);
            }
        }
;

whereItem:
        col op value
        {
            if ($1 != NULL) {
                $$ = new UnionWhereItem();
                $$ -> op = (UnionWhereItem::OpTag) $2;
                $$ -> left = $1;
                $$ -> ty = 1;
                $$ -> right.uv = $3;
            } else {
                $$ = NULL;
            }
        }
        |
        col op col
        {
            if ($1 != NULL && $3 != NULL) {
                $$ = new UnionWhereItem();
                $$ -> op = (UnionWhereItem::OpTag) $2;
                $$ -> left = $1;
                $$ -> ty = 2;
                $$ -> right.uc = $3;
            } else {
                $$ = NULL;
            }
        }
        |
        col IS NNULL
        {
            if ($1 != NULL) {
                $$ = new UnionWhereItem();
                $$ -> op = UnionWhereItem::OpTag::OP_EQ;
                $$ -> left = $1;
                $$ -> ty = 0;
            } else {
                $$ = NULL;
            }
        }
        |
        col IS NOT NNULL
        {
            if ($1 != NULL) {
                $$ = new UnionWhereItem();
                $$ -> op = UnionWhereItem::OpTag::OP_NE;
                $$ -> left = $1;
                $$ -> ty = 0;
            } else {
                $$ = NULL;
            }
        }
;

selector:
        col
        {
            $$ = new UnionColList();
            if ($1 != NULL) {
                $$ -> push_back($1);
            }
        }
        |
        selector ',' col
        {
            $$ = $1;
            if ($3 != NULL) {
                $$ -> push_back($3);
            }
        }
;

col:
        ident
        {
            //从活跃的数据表中得到数据列
            std::string * colName = $1;
            //没有活跃的数据表，报错
            if (cur.table == NULL) {
                std::cout << "Parser.<col := ident>: error" << std::endl;
                std::cout << "没有活跃的数据表" << std::endl;
                $$ = NULL;
            } else if (!cur.table -> getTableHeader() -> hasColumn(* colName)) {
                //活跃的数据表没有这个列，报错
                std::cout << "Parser.<col := ident>: error" << std::endl;
                std::cout << "活跃的数据表" << cur.table -> getName() << "中没有数据列" << * colName << std::endl;
                $$ = NULL;
            } else {
                $$ = new UnionCol();
                $$ -> tb = new std::string(cur.table -> getName());
                $$ -> col = colName;
                $$ -> tc = cur.table -> getTableHeader() -> getColumnByName(* colName);
            }
        }
        |
        ident '.' ident
        {
            //从当前数据库中得到数据列
            std::string * tbName = $1;
            std::string * colName = $3;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<col := ident '.' ident>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
                $$ = NULL;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.<col := ident '.' ident>: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
                $$ = NULL;
            } else {
                Table * table = cur.database -> getTableByName(* tbName);
                if (!table -> getTableHeader() -> hasColumn(* colName)) {
                    //这个数据表没有这个列，报错
                    std::cout << "Parser.<col := ident '.' ident>: error" << std::endl;
                    std::cout << "数据表" << table -> getName() << "中没有数据列" << * colName << std::endl;
                    $$ = NULL;
                } else {
                    $$ = new UnionCol();
                    $$ -> tb = tbName; 
                    $$ -> col = colName;
                    $$ -> tc  = table -> getTableHeader() -> getColumnByName(* colName);
                }
            }
        }
;

setClause:
        setList
        {
            $$ = $1;
        }
        |
        /* empty */
        {
            $$ = new UnionSetClause();
        }
;


setList:
        setItem
        {
            $$ = new UnionSetClause();
            $$ -> push_back($1);
        }
        |
        setList ',' setItem
        {
            $$ = $1;
            $$ -> push_back($3);
        }
;

setItem:
        ident OP_EQ value
        {
            $$ = new UnionSetItem();
            $$ -> col = $1;
            $$ -> uv = $3; 
        }
;    

identList:
        ident        
        {
            $$ = new StringList();
            $$ -> push_back($1);
        }
        |
        identList ',' ident
        {
            $$ = $1;
            $$ -> push_back($3);
        }
;

value:
        NNULL
        {
            $$ = new UnionValue();
        }
        |
        VALUE_UINT64
        {
            $$ = new UnionValue();
            $$ -> ty = 1;
            $$ -> dt.u = $1;
        }
        |
        VALUE_DOUBLE
        {
            $$ = new UnionValue();
            $$ -> ty = 2;
            $$ -> dt.d = $1;
        }
        |
        VALUE_STRING
        {
            $$ = new UnionValue();
            $$ -> ty = 3;
            $$ -> dt.s = $1;
        }
;

type:
        BOOLL
        {
            $$ = TableDataType::t_bool;
        }
        |
        CHARR
        {
            $$ = TableDataType::t_char;
        }
        |
        SHORTT
        {
            $$ = TableDataType::t_short;
        }
        |
        INTEGER
        {
            $$ = TableDataType::t_int;
        }
        |
        LONGG
        {
            $$ = TableDataType::t_long;
        }
        |
        FLOATT
        {
            $$ = TableDataType::t_float;
        }
        |
        DOUBLEE
        {
            $$ = TableDataType::t_double;
        }
        |
        VARCHAR        
        {
            $$ = TableDataType::t_string;
        }
        |
        DATEE
        {
            $$ = TableDataType::t_int;
        }
        |
        LOB
        {
            $$ = TableDataType::t_lob;
        }
        |
        INTEGER '(' VALUE_UINT64 ')'
        {
            if (1 <= $3 && $3 <= 4) {
                $$ = TableDataType::t_short;
            } else if (5 <= $3 && $3 <= 9) {
                $$ = TableDataType::t_int;
            } else if (10 <= $3 && $3 <= 19) {
                $$ = TableDataType::t_long;
            } else {
                yyerror("INT类型长度出错");
            }
        }
        |
        VARCHAR '(' VALUE_UINT64 ')'
        {
            if (1 <= $3 && $3 < MAX_STRING_LENGTH) {
                $$ = TableDataType::t_string;
            } else {
                yyerror("VARCHAR类型长度出错");
            }
        }
        |
        CHARR '(' VALUE_UINT64 ')'
        {
            if (1 <= $3 && $3 < MAX_STRING_LENGTH) {
                $$ = TableDataType::t_string;
            } else {
                yyerror("CHAR类型长度出错");
            }
        }
;

ident:
        IDENTIFIER
        {
            $$ = $1;
        }
;

op:
        OP_EQ
        {
            $$ = UnionWhereItem::OpTag::OP_EQ;
        }
        |
        OP_NE
        {
            $$ = UnionWhereItem::OpTag::OP_NE;
        }
        |
        OP_LT
        {
            $$ = UnionWhereItem::OpTag::OP_LT;
        }
        |
        OP_GT
        {
            $$ = UnionWhereItem::OpTag::OP_GT;
        }
        |
        OP_LE
        {
            $$ = UnionWhereItem::OpTag::OP_LE;
        }
        |
        OP_GE
        {
            $$ = UnionWhereItem::OpTag::OP_GE;
        }
;

endLine:
        '\n'
        {
            setCmdColor(0);
        }
;

%%

int yyerror(const char * emseg) {
    std::cout << "Parser: Unknown sentence! please try again! " << emseg << std::endl;
    return -1;
}

int main() {
    MyBitMap::initConst();
    FileManager * fileManager = new FileManager();
    cur.bufPageManager = new BufPageManager(fileManager);
    cur.database = NULL;    
    cmdColorHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    //myMain(yyparse);
    while (true) {
        yyparse();
        cur.firstRoundFlag = false;
    }
}
