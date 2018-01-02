%{
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lex.yy.c"
using namespace std;
int yylex();
int yyerror(const char *);
char db[100];
%}
%token	DATABASE
%token	DATABASES
%token	TABLE
%token	TABLES
%token	SHOW
%token	CREATE
%token	DROP
%token	USE
%token	PRIMARY
%token  KEY
%token	NOT
%token  NNULL
%token	INSERT
%token	INTO
%token	VALUES
%token	DELETE
%token	FROM
%token	WHERE
%token	UPDATE
%token	SET
%token	SELECT
%token	IS
%token	INT
%token	VARCHAR
%token	DESC
%token	REFERENCES
%token	INDEX
%token	AND
%token	DATE         
%token	FLOAT
%token	FOREIGN

%token  ';' ',' '(' ')' '.' '=' '<' '>' //'<>' '<=' '>='

%token <iv> VALUE_INT
%token <sv> VALUE_STRING
%token <sv> IDENTIFIER
%union {
  int iv;
  char *sv;
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
			cout<<"show databases!"<<endl;		
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
		INT
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
		VALUE_INT
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
		|
		whereClause AND whereClause
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
			//$$ = $1;
			strcpy(db, $1);
			//cout<<db<<endl;
			cout<<$1<<endl;
		}
;  

tbName:
		IDENTIFIER
		{
			//$$ = $1;
			strcpy(db, $1);
			//cout<<db<<endl;
			cout<<$1<<endl;
		}
;  

colName:
		IDENTIFIER
		{
			cout<<$1<<endl;
		}
;  



%%


int yyerror(const char *emseg)
{
	cout<<"Unknown sentence! please try again!" ;
	//cout << "Error: " << emseg << endl;
}

int main()
{
  yyparse();
}
