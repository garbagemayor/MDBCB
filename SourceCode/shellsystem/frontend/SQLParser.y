%{
    #include "../ShellAssistant.h"
    
    #include "lex.yy.c"
    
    int yylex();
    int yyerror(const char *);
    
    //����ҳ������
    BufPageManager * bufPageManager;
    //�����ﾳ�����ݿ�
    TableManager * dbNow;
    //һ�������ǰ���ָ����һ�����ݱ�
    Table * tbNow;
    
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

%type <v_sl> identList
%type <v_s> ident
%type <v_t> type

%union {
    
    UnionFieldList * u_fl;
    UnionField * u_fd;
    StringList * v_sl;
    
    std::string * v_s;
    unsigned long long v_u;
    double v_d;
    
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
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //�������������ݿ⣬����
            if (access(dbName -> c_str(), W_OK) == 0) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "�������ݿ�:" << * dbName << std::endl;
            } else {
                //�½�������ݿ⣬����
                mkdir(dbName -> c_str());
                chdir(dbName -> c_str());
                dbNow = new TableManager(bufPageManager, * dbName);
            }
        }        
        |
        DROP DATABASE ident ';' endLine
        {
            //ɾ��һ�����ݿ�
            std::string * dbName = $3;
            //�ر��Ѿ��򿪵����ݿ�
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
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
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //���������������ݿ⣬����
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.USE: error" << std::endl;
                std::cout << "���������ݿ�:" << * dbName << std::endl;
            } else {
                //��������ݿ�
                chdir(dbName -> c_str());
                dbNow = new TableManager(bufPageManager, * dbName);
            }
        }
        |
        SHOW TABLES ';' endLine
        {
            //�鿴������ݿ���������ݱ�
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.SHOW TABLES: error" << std::endl;
                std::cout << "û������ʹ�õ����ݿ�" << std::endl;
            } else {
                //��ӡ���ݿ��е����ݱ�
                int nTab = dbNow -> getNTable();
                std::cout << "���ݿ�" << dbNow -> getName() << "����" << nTab << "�����ݱ�:" << std::endl;
                for (int i = 0; i < nTab; i ++) {
                    std::cout << dbNow -> getTableById(i) -> getName() << ( i < nTab - 1 ? ", " : ".");
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
            if (dbNow == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�:" << * tbName << std::endl;
            } else if (dbNow -> hasOpenedTable(* tbName)) {
                //�������ͬ�����ݱ�����
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "����������ݱ�:" << * tbName << std::endl;
            } else {
                //����fieldList����ȡ�����б���ΪPRIMARY KEY������
                StringList pkList;
                for (int i = 0; i < fieldList -> size(); i ++) {
                    if (fieldList -> at(i) -> ty == 2) {
                        StringList * pkListI = fieldList -> at(i) -> dt.pk;
                        for (int j = 0; j < pkListI -> size(); j ++) {
                            pkList.push_back(pkListI -> at(j));
                        }
                    }
                }
                //����fieldList���ѵ�һ�����Ա���ΪPRIMARY KEY��������һ�£�ʣ�µľ����ӵ�
                for (int i = 0; i < pkList.size(); i ++) {
                    int j;
                    for (j = 0; j < fieldList -> size(); j ++) {
                        if ($5 -> at(j) -> ty == 1) {
                            if ($5 -> at(j) -> dt.tc -> getName() == * pkList[i]) {
                                $5 -> at(j) -> dt.tc -> setPrimaryKey(true);
                                break;
                            }
                        }
                    }
                    if (j < fieldList -> size()) {
                        break;
                    }
                }
                //�������ݱ�
                TableHeader * tbHd = new TableHeader();
                tbHd -> setName(* tbName);
                for (int i = 0; i < fieldList -> size(); i ++) {
                    UnionField * fd = fieldList -> at(i);
                    if (fd -> ty == 1) {
                        fd -> dt.tc -> setConstant();
                        tbHd -> addColumn(fd -> dt.tc);
                    }
                }
                tbHd -> setConstant();
                dbNow -> createTable(tbHd);
            }
        }
        |
        DROP TABLE ident ';' endLine
        {
            //���Ѿ��򿪵����ݿ���ɾ��һ�����ݱ�
            std::string * tbName = $3;
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!dbNow -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                //ɾ�����ݱ�
                dbNow -> eraseTable(* tbName);
            }
        }
        |
        DESC ident ';' endLine
        {
            //��ӡ���ݱ��е�������
            std::string * tbName = $2;
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!dbNow -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                //��ӡ���ݱ����
                Table * table = dbNow -> getTableByName(* tbName);
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
        insertIntoTable VALUES valueLists ';' endLine
        {
        }
        |
        DELETEE FROM ident WHERE whereClause  ';' endLine
        {
        }
        |
        UPDATE ident SET setClause WHERE whereClause ';' endLine
        {
        }
        |
        SELECT selector FROM identList WHERE whereClause ';' endLine
        {
        }
;

insertIntoTable:
        INSERT INTO ident
        {
            //ǰ���SQL��䣬ȷ�������ݱ�
            std::string * tbName = $3;
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!dbNow -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                //��ǰSQL������������ݱ�
                tbNow = dbNow -> getTableByName(* tbName);
            }
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
            $$ -> clear();
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
            if (dbNow == NULL) {
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!dbNow -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else if (!dbNow -> getTableByName(* tbName) -> getTableHeader() -> hasColumn(* colName0)) { 
                //���û����������У�����
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "���ݱ�" << * $7 << "��û��������:" << * colName0 << std::endl;
            } else {
                TableColumn * tc = dbNow -> getTableByName(* tbName) -> getTableHeader() -> getColumnByName(* colName0);
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
        }
        |
        valueLists ',' '(' valueList ')'
        {
        }
;

valueList:
        value
        {
        }
        |
        valueList ',' value
        {
        }
;

value:
        VALUE_UINT64
        {
        }
        |
        VALUE_DOUBLE
        {
        }
        |
        VALUE_STRING
        {
        }
        |
        NNULL        
        {
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

col:            
        ident
        {
        }
        |
        ident '.' ident
        {
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

expr:
        value
        {
        }
        |
        col
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

selector:
        col
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

endLine:
        '\n'
        {
            setCmdColor(0);
        }
;

%%

int yyerror(const char *emseg) {
    std::cout << "Parser: Unknown sentence! please try again!" << std::endl;
    //cout << "Error: " << emseg << endl;
}

int main() {
    MyBitMap::initConst();
    FileManager * fileManager = new FileManager();
    bufPageManager = new BufPageManager(fileManager);
    dbNow = NULL;    
    cmdColorHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    //myMain(yyparse);
    yyparse();
}
