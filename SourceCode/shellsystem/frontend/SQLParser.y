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

%token  ';' ',' '(' ')' '.' '=' '<' '>' //'<>' '<=' '>='
%token <v_u> VALUE_UINT64
%token <v_s> VALUE_STRING
%token <v_d> VALUE_DOUBLE
%token <v_s> IDENTIFIER

%type <u_fl> fieldList
%type <u_fd> field

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
    UnionValueRow * u_vr;
    UnionValueTable * u_vt;
    
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
            std::cout << ">>>";
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
            }
        }
        |
        DROP TABLE ident ';' endLine
        {
            //在已经打开的数据库中删除一个数据表
            std::string * tbName = $3;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                //删除数据表
                cur.database -> eraseTable(* tbName);
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
        INSERT INTO ident VALUES valueLists ';' endLine
        {
            //在数据表中插入若干行
            std::string * tbName = $3;
            UnionValueTable * rowList = $5;
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
                //把数据一行一行的插入到表中
                int insertCnt = 0;
                for (int i = 0; i < (int) rowList -> size(); i ++) {
                    //创建数据库中的数据行
                    UnionValueRow * sqlRow = rowList -> at(i);
                    std::string errMsg;
                    TableRow * tableRow = genTableRow(sqlRow, table, errMsg);
                    if (tableRow == NULL) {
                        std::cout << "Parser.INSERT INTO: error" << std::endl;
                        std::cout << "输入的第" << i << "个数据行不符合数据表" << table -> getName() << "的格式要求" << std::endl;
                        std::cout << errMsg << std::endl;
                        continue;
                    }
                    table -> insertRow(tableRow);
                    insertCnt += 1;
                }
                std::cout << "共添加" << insertCnt << "个数据行" << std::endl;
            }
        }
        |
        DELETEE FROM ident ident WHERE whereClause  ';' endLine
        {
            std::string * tbName = $3;
        }
        |
        UPDATE ident SET setClause WHERE whereClause ';' endLine
        {
            std::string * tbName = $2;
        }
        |
        SELECT selector FROM identList WHERE whereClause ';' endLine
        {
        }
;

idxStmt:
        CREATE INDEX ident '(' ident ')' ';' endLine
        {
        }
        |
        DROP INDEX ident '(' ident ')' ';' endLine
        {
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
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else if (!cur.database -> getTableByName(* tbName) -> getTableHeader() -> hasColumn(* colName0)) { 
                //如果没有这个数据列，报错
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
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
;

valueLists:
        '(' valueList ')'
        {
            $$ = new UnionValueTable();
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
            $$ = new UnionValueRow();
            $$ -> push_back($1);
        }
        |
        valueList ',' value
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

whereClause:
        whereClause AND filterItem
        {
        }
        |
        filterItem
        {
        }
;
        
filterItem:
        col op expr
        {
        }
        |
        col IS NNULL
        {
        }
        |
        col IS NOT NNULL
        {
        }
;

expr:
        value
        {
        }
        |
        col
        {
        }
;

selector:
        col
        {
        }
        |
        selector ',' col
        {
        }
;

col:            
        ident
        {
        }
        |
        ident '.' ident
        {
        }
;

setClause:
        ident '=' value
        {
        }
        |
        setClause ',' ident '=' value
        {
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

ident:
        IDENTIFIER
        {
            $$ = $1;
        }
;

op:
        '='
        {
        }
        |
        '<' '>'
        {
        }
        |
        '<' '='
        {
        }
        |
        '>' '='
        {
        }
        |
        '<'
        {
        }
        |
        '>'
        {
        }
;

endLine:
        '\n'
        {
            setCmdColor(0);
            cur.table = NULL;
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
    }
}
