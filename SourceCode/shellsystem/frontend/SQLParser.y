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
            //���������ļ���
            struct _finddata_t fb;
            int handle = _findfirst("*", &fb);
            std::vector < std::string > dbList;
            if (handle != -1) {
                do {
                    int noFile = strcmp(fb.name, "..");
                    if (0 != noFile && fb.attrib == 16) {
                        std::string name = fb.name;
                        if (name != "." && name != "..") {
                            //�ҵ�һ���ļ��У������ҵ�һ�����ݿ�
                            dbList.push_back(fb.name);
                        }
                    }
                } while (_findnext(handle, &fb) == 0);
                _findclose(handle);
            }
            std::cout << "��ǰĿ¼�¹���" << dbList.size() << "�����ݿ�:" << std::endl;
            for (int i = 0; i < (int) dbList.size(); i ++) {
                std::cout << dbList[i] << (i < (int) dbList.size() - 1 ? ", " : ".");
            }
            std::cout << std::endl;
        }
;

dbStmt:
        CREATE DATABASE ident ';' endLine
        {
            //�½�һ�����ݿ�
            std::string * dbName = $3;
            //�ر��Ѿ��򿪵����ݿ�
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
            }
            //�������������ݿ⣬����
            if (access(dbName -> c_str(), W_OK) == 0) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "�������ݿ�:" << * dbName << std::endl;
            } else {
                //�½�������ݿ⣬����
                mkdir(dbName -> c_str());
                chdir(dbName -> c_str());
                cur.database = new TableManager(cur.bufPageManager, * dbName);
            }
        }
        |
        DROP DATABASE ident ';' endLine
        {
            //ɾ��һ�����ݿ�
            std::string * dbName = $3;
            //�ر��Ѿ��򿪵����ݿ�
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
            }
            //���������������ݿ⣬����
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "���������ݿ�:" << * dbName << std::endl;
            } else {
                //ɾ��������ݿ�
                int rmrs = removeDir(dbName -> c_str());
                if (rmrs == -1) {
                    std::cout << "ɾ����������ݿ�" << std::endl;
                }
            }
        }
        |
        USE ident ';' endLine
        {
            //��һ�����ݿ�
            std::string * dbName = $2;
            //�ر��Ѿ��򿪵����ݿ�
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
            }
            //���������������ݿ⣬����
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.USE: error" << std::endl;
                std::cout << "���������ݿ�:" << * dbName << std::endl;
            } else {
                //��������ݿ�
                chdir(dbName -> c_str());
                cur.database = new TableManager(cur.bufPageManager, * dbName);
            }
        }
        |
        USE ';' endLine
        {
            //�ر��Ѿ��򿪵����ݿ�
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
            }
        }
        |
        SHOW TABLES ';' endLine
        {
            //�鿴������ݿ���������ݱ�
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.SHOW TABLES: error" << std::endl;
                std::cout << "û������ʹ�õ����ݿ�" << std::endl;
            } else {
                //��ӡ���ݿ��е����ݱ�
                int nTab = cur.database -> getNTable();
                std::cout << "���ݿ�" << cur.database -> getName() << "����" << nTab << "�����ݱ�:" << std::endl;
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
            //���Ѿ��򿪵����ݿ��д���һ�����ݱ�
            std::string * tbName = $3;
            UnionFieldList * fieldList = $5;
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�:" << * tbName << std::endl;
            } else if (cur.database -> hasOpenedTable(* tbName)) {
                //�������ͬ�����ݱ�����
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "����������ݱ�:" << * tbName << std::endl;
            } else {
                //����fieldList����ȡ�����б���ΪPRIMARY KEY������
                StringList pkList;
                for (int i = 0; i < (int) fieldList -> size(); i ++) {
                    if (fieldList -> at(i) -> ty == 2) {
                        StringList * pkListI = fieldList -> at(i) -> dt.pk;
                        for (int j = 0; j < (int) pkListI -> size(); j ++) {
                            pkList.push_back(pkListI -> at(j));
                        }
                    }
                }
                //����fieldList���ѵ�һ�����Ա���ΪPRIMARY KEY��������һ�£�ʣ�µľ����ӵ�
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
                //�������ݱ�
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
            //���Ѿ��򿪵����ݿ���ɾ��һ�����ݱ�
            std::string * tbName = $3;
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                //ɾ�����ݱ�
                cur.database -> eraseTable(* tbName);
                //���ļ�����ɾ��
                std::string fileName = * tbName + ".table";
                remove(fileName.c_str());
            }
        }
        |
        DESC ident ';' endLine
        {
            //��ӡ���ݱ��е�������
            std::string * tbName = $2;
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                //��ӡ���ݱ����
                Table * table = cur.database -> getTableByName(* tbName);
                int nCol = table -> getNCol();
                std::cout << "���ݱ�" << * tbName << "����" << nCol << "��������:" << std::endl;
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
            //�����ݱ��в���������
            std::string * tbName = $3;
            UnionValueTable * rowList = $5;
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                Table * table = cur.database -> getTableByName(* tbName);
                //������һ��һ�еĲ��뵽����
                int insertCnt = 0;
                for (int i = 0; i < (int) rowList -> size(); i ++) {
                    //�������ݿ��е�������
                    UnionValueRow * sqlRow = rowList -> at(i);
                    std::string errMsg;
                    TableRow * tableRow = genTableRow(sqlRow, table, errMsg);
                    if (tableRow == NULL) {
                        std::cout << "Parser.INSERT INTO: error" << std::endl;
                        std::cout << "����ĵ�" << i << "�������в��������ݱ�" << table -> getName() << "�ĸ�ʽҪ��" << std::endl;
                        std::cout << errMsg << std::endl;
                        continue;
                    }
                    table -> insertRow(tableRow);
                    insertCnt += 1;
                }
                std::cout << "�����" << insertCnt << "��������" << std::endl;
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
            //ȥһ���������ݱ��а�һ�������е����Ը��ƹ���
            std::string * colName = $4;
            std::string * tbName = $7;
            std::string * colName0 = $9;
            $$ = new UnionField();
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else if (!cur.database -> getTableByName(* tbName) -> getTableHeader() -> hasColumn(* colName0)) { 
                //���û����������У�����
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "���ݱ�" << * $7 << "��û��������:" << * colName0 << std::endl;
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
