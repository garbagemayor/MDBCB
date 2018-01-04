%{
    #include "../../DatabaseManager.h"
    
    #include <iostream>
    #include <cstdio>
    #include <cstdlib>
    #include <string>
    #include "lex.yy.c"
    
    int yylex();
    int yyerror(const char *);
    
    std::string dbNameBuf;
    std::string tbNameBuf;
    std::string colNameBuf;
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
 
%union {
    unsigned long long v_u;
    double v_d;
    std::string * v_s;
}
%%


program:
        program stmt '\n'
        {
            //cout<<"command:    ";    
            //cout<<db<<endl;
        }
        |
;

stmt:
        sysStmt ';'
        |
        dbStmt ';'
        |
        tbStmt ';'
        |
        idxStmt ';'
        |
;

sysStmt:
        SHOW DATABASES
        {
            std::cout << "show databases!" << std::endl;
        }
;

dbStmt:
        CREATE DATABASE dbName
        {
        }        
        |
        DROP DATABASE dbName
        {
        }        
        |
        USE dbName
        {
        }        
        |
        SHOW TABLES
        {
        }
;

tbStmt:
        CREATE TABLE tbName '(' fieldList ')'
        {
        }        
        |
        DROP TABLE tbName
        {
        }    
        |
        DESC tbName
        {
        }
        |
        INSERT INTO tbName VALUES valueLists
        {
        }
        |
        DELETE FROM tbName WHERE whereClause        
        {
        }
        |
        UPDATE tbName SET setClause WHERE whereClause
        {
        }
        |
        SELECT selector FROM tableList WHERE whereClause        
        {
        }
;

idxStmt:
        CREATE INDEX tbName '(' colName ')'
        {
        }
        |
        DROP INDEX tbName '(' colName ')'
        {
        }
;

fieldList:
        field
        {
        }
        |
        fieldList ',' field
        {
            //cout << "field" <<endl;
        }
;

field:
        colName type
        {
        }
        |
        colName type NOT NNULL
        {
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
        }
        |
        VARCHAR        
        {
        }
        |
        DATE
        {
        }
        |
        FLOAT
        {
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
            dbNameBuf = * ($1);
            std::cout << dbNameBuf << std::endl;
        }
;  

tbName:
        IDENTIFIER
        {
            tbNameBuf = * ($1);
            std::cout << tbNameBuf << std::endl;
        }
;  

colName:
        IDENTIFIER
        {
            colNameBuf = * ($1);
            std::cout << colNameBuf << std::endl;
        }
;  

%%

int yyerror(const char *emseg) {
    std::cout << "Parser: Unknown sentence! please try again!" << std::endl;
    //cout << "Error: " << emseg << endl;
}

int main() {
    //yyparse();
    myMain(yyparse);
}
