%{
    #include "../../DatabaseManager.h"
    
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
    #include <string>
    #include <direct.h>
    #include "lex.yy.c"
    
    int yylex();
    int yyerror(const char *);
    
    BufPageManager * bufPageManager;
    TableManager * dbNow;
    
    //ɾ�����ļ��У������������е��ļ����ļ��У����������·��Ҳ�����Ǿ���·��
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
%token  DELETE
%token  FROM
%token  WHERE
%token  UPDATE
%token  SET
%token  SELECT
%token  IS
%token  INTEGER
%token  VARCHAR
%token  DESC
%token  REFERENCES
%token  INDEX
%token  AND
%token  DATE         
%token  FLOAT
%token  FOREIGN

%token  ';' ',' '(' ')' '.' '=' '<' '>' //'<>' '<=' '>='

%token <v_u> VALUE_UINT64
%token <v_s> VALUE_STRING
%token <v_d> VALUE_DOUBLE
%token <v_s> IDENTIFIER

%type <v_t> type
%type <v_s> dbName
%type <v_s> tbName
%type <v_s> colName
%type <v_tc> field
%type <v_th> fieldList
 
%union {
    unsigned long long v_u;
    double v_d;
    TableDataType v_t;
    std::string * v_s;
    TableColumn * v_tc;
    std::vector<TableColumn *> * v_th;
}
%%


program:
        program stmt '\n'
        {
        }
        |
;

stmt:
        sysStmt
        |
        dbStmt
        |
        tbStmt
        |
        idxStmt
        |
;

sysStmt:
        SHOW DATABASES ';'
        {
            std::cout << "show databases!" << std::endl;
        }
;

dbStmt:
        CREATE DATABASE dbName ';'
        {
            //�½�һ�����ݿ�
            //�ر��Ѿ��򿪵����ݿ�
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //�������������ݿ⣬����
            if (access($3 -> c_str(), W_OK) == 0) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "�������ݿ�:" << * $3 << std::endl;
            } else {
                //�½�������ݿ⣬����
                mkdir($3 -> c_str());
                chdir($3 -> c_str());
                dbNow = new TableManager(bufPageManager, * $3);
            }
        }        
        |
        DROP DATABASE dbName ';'
        {
            //ɾ��һ�����ݿ�
            //�ر��Ѿ��򿪵����ݿ�
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //���������������ݿ⣬����
            if (access($3 -> c_str(), W_OK) == -1) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "���������ݿ�:" << * $3 << std::endl;
            } else {
                //ɾ��������ݿ�
                int rmrs = removeDir($3 -> c_str());
                if (rmrs == -1) {
                    std::cout << "ɾ����������ݿ�" << std::endl;
                }
            }
        }        
        |
        USE dbName ';'
        {
            //��һ�����ݿ�
            //�ر��Ѿ��򿪵����ݿ�
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //���������������ݿ⣬����
            if (access($2 -> c_str(), W_OK) == -1) {
                std::cout << "Parser.USE: error" << std::endl;
                std::cout << "���������ݿ�:" << * $2 << std::endl;
            } else {
                //��������ݿ�
                chdir($2 -> c_str());
                dbNow = new TableManager(bufPageManager, * $2);
            }
        }
        |
        SHOW TABLES ';'
        {
            //�鿴������ݿ���������ݱ�
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.SHOW TABLES: error" << std::endl;
                std::cout << "û������ʹ�õ����ݿ�" << std::endl;
            } else {
                //��ӡ���ݿ��е����ݱ�
                int n = dbNow -> getNTable();
                std::cout << "����" << n << "�����ݱ�: ";
                for (int i = 0; i < n; i ++) {
                    std::cout << dbNow -> getTableById(i) -> getName() << ", ";
                }
                std::cout << std::endl;
            }
        }
;

tbStmt:
        CREATE TABLE tbName '(' fieldList ')' ';'
        {
            //���Ѿ��򿪵����ݿ��д���һ�����ݱ�
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�:" << * $3 << std::endl;
            } else {
                //�������ͬ�����ݱ�����
                if (dbNow -> hasOpenedTable(* $3)) {
                    std::cout << "Parser.CREATE TABLE: error" << std::endl;
                    std::cout << "����������ݱ�:" << * $3 << std::endl;
                } else {
                    //�������ݱ�
                    TableHeader * tbHd = new TableHeader();
                    tbHd -> setName(* $3);
                    for (int i = 0; i < $5 -> size(); i ++) {
                        tbHd -> addColumn((* $5) [i]);
                    }
                    tbHd -> setConstant();
                    dbNow -> createTable(tbHd);
                }
            }
        }
        |
        DROP TABLE tbName ';'
        {
            //���Ѿ��򿪵����ݿ���ɾ��һ�����ݱ�
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�"<< std::endl;
            } else {
                Table * table = dbNow -> getTableByName(* $3);
                if (table == NULL) {
                    std::cout << "Parser.DROP TABLE: error" << std::endl;
                    std::cout << "û�������:" << * $3 << std::endl;
                } else {
                    dbNow -> eraseTable(* $3);
                }
            }
        }
        |
        DESC tbName ';'
        {
        }
        |
        INSERT INTO tbName VALUES valueLists ';'
        {
        }
        |
        DELETE FROM tbName WHERE whereClause  ';'
        {
        }
        |
        UPDATE tbName SET setClause WHERE whereClause ';'
        {
        }
        |
        SELECT selector FROM tableList WHERE whereClause ';'
        {
        }
;

idxStmt:
        CREATE INDEX tbName '(' colName ')' ';'
        {
        }
        |
        DROP INDEX tbName '(' colName ')' ';'
        {
        }
;

fieldList:
        field
        {
            //std::cout << "Parser.fieldList: (" << $1 -> getName() << " " << $1 -> getDataType() << ")" << std::endl;
            $$ = new std::vector<TableColumn *>();
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
        colName type
        {
            //std::cout << "Parser.field: (" << * $1 << " " << $2 << ")" << std::endl;
            $$ = new TableColumn();
            $$ -> setName(* $1);
            $$ -> setType($2);
            $$ -> setAllowNull(true);
            $$ -> setConstant();
        }
        |
        colName type NOT NNULL
        {
            //std::cout << "Parser.field: (" << * $1 << " " << $2 << " NOT NULL)" << std::endl;
            $$ = new TableColumn();
            $$ -> setName(* $1);
            $$ -> setType($2);
            $$ -> setConstant();
        }
        |
        PRIMARY KEY '(' columnList ')'
        {
        }
        |
        FOREIGN KEY '(' colName ')' REFERENCES tbName '(' colName ')'
        {
        }
;        

type:
        INTEGER
        {
            $$ = TableDataType::t_int;
        }
        |
        VARCHAR        
        {
            $$ = TableDataType::t_string;
        }
        |
        DATE
        {
            $$ = TableDataType::t_int;
        }
        |
        FLOAT
        {
            $$ = TableDataType::t_float;
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
        colName
        {
        }
        |
        tbName '.' colName
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
        colName '=' value
        {
        }
        |
        setClause ',' colName '=' value
        {
        }
;

selector:
        col
        {
        }
;

tableList:
        tbName
        {
        }
        |
        tableList ',' tbName

columnList:
        colName        
        {
        }
        |
        columnList ',' colName
        {
        }
;

dbName:
        IDENTIFIER
        {
            $$ = $1;
        }
;  

tbName:
        IDENTIFIER
        {
            $$ = $1;
        }
;  

colName:
        IDENTIFIER
        {
            $$ = $1;
        }
;

%%

int yyerror(const char *emseg) {
    std::cout << "Parser: Unknown sentence! please try again!" << std::endl;
    //cout << "Error: " << emseg << endl;
}

int main() {
    FileManager * fileManager = new FileManager();
    bufPageManager = new BufPageManager(fileManager);
    dbNow = NULL;

    myMain(yyparse);
}
