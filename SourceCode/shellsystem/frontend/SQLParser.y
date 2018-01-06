%{
    #include "../ShellAssistant.h"
    
    #include "lex.yy.c"
    
    int yylex();
    int yyerror(const char *);
    
    BufPageManager * bufPageManager;
    TableManager * dbNow;
    
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
%token  INTEGER
%token  VARCHAR
%token  DESC
%token  REFERENCES
%token  INDEX
%token  AND
%token  DATEE
%token  FLOATT
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
        CREATE DATABASE dbName ';' endLine
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
        DROP DATABASE dbName ';' endLine
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
        USE dbName ';' endLine
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
        CREATE TABLE tbName '(' fieldList ')' ';' endLine
        {
            //���Ѿ��򿪵����ݿ��д���һ�����ݱ�
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�:" << * $3 << std::endl;
            } else if (dbNow -> hasOpenedTable(* $3)) {
                //�������ͬ�����ݱ�����
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
        |
        DROP TABLE tbName ';' endLine
        {
            //���Ѿ��򿪵����ݿ���ɾ��һ�����ݱ�
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!dbNow -> hasOpenedTable(* $3)) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * $3 << std::endl;
            } else {
                //ɾ�����ݱ�
                dbNow -> eraseTable(* $3);
            }
        }
        |
        DESC tbName ';' endLine
        {
            //��ӡ���ݱ��е�������
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!dbNow -> hasOpenedTable(* $2)) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * $2 << std::endl;
            } else {
                //��ӡ���ݱ����
                Table * table = dbNow -> getTableByName(* $2);
                int nCol = table -> getNCol();
                std::cout << "���ݱ�" << * $2 << "����" << nCol << "��������:" << std::endl;
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
                    std::cout << (i < nCol - 1 ? ", " : ".");
                }
                std::cout << std::endl;
            }
        }
        |
        INSERT INTO tbName VALUES valueLists ';' endLine
        {
        }
        |
        DELETEE FROM tbName WHERE whereClause  ';' endLine
        {
        }
        |
        UPDATE tbName SET setClause WHERE whereClause ';' endLine
        {
        }
        |
        SELECT selector FROM tableList WHERE whereClause ';' endLine
        {
        }
;

idxStmt:
        CREATE INDEX tbName '(' colName ')' ';' endLine
        {
        }
        |
        DROP INDEX tbName '(' colName ')' ';' endLine
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
        DATEE
        {
            $$ = TableDataType::t_int;
        }
        |
        FLOATT
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

    myMain(yyparse);
}
