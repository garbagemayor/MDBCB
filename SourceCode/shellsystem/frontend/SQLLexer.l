%{
  #include <iostream> 
  #include <cstring>
  #include "test.tab.h"
  extern int yyerror(const char *);
  using namespace std;
%}
%%
DATABASE		{return DATABASE;}
DATABASES		{return DATABASES;}
TABLE			{return TABLE;}
TABLES			{return TABLES;}
SHOW			{return SHOW;}
CREATE			{return CREATE;}
DROP			{return DROP;}
USE				{return USE;}
PRIMARY			{return PRIMARY;}
KEY				{return KEY;}
NOT				{return NOT;}
NULL			{return NNULL;}
INSERT			{return INSERT;}
INTO			{return INTO;}
VALUES			{return VALUES;}
DELETE			{return DELETE;}
FROM			{return FROM;}
WHERE			{return WHERE;}
UPDATE			{return UPDATE;}
SET				{return SET;}
SELECT			{return SELECT;}
IS				{return IS;}
INT				{return INT;}
VARCHAR			{return VARCHAR;}
DESC			{return DESC;}
REFERENCES		{return REFERENCES;}
INDEX			{return INDEX;}
AND				{return AND;}
DATE      		{return DATE;}
FLOAT			{return FLOAT;}
FOREIGN			{return FOREIGN;}

[;,\(\)\.]		{return *yytext;}
\=				{return *yytext;}
\<\>			{return *yytext;}
\<\=			{return *yytext;}
\>\=			{return *yytext;}
\<				{return *yytext;}
\>				{return *yytext;}

[A-Za-z][_0-9A-Za-z]* 	{ 	yylval.sv = strdup(yytext); 
				//cout<<"identifier"<<endl;
				return IDENTIFIER;}
[0-9]+        	{ 	yylval.iv = strtol(yytext,0,10); 
				//cout<<"int"<<endl;
				return VALUE_INT; }
’[^’]*’ 		{ 	yylval.sv = strdup(yytext); 
				//cout<<"string"<<endl;
				return VALUE_STRING;}
[ \t]         		; //忽略空格  
\n				{ return *yytext; } //直接返回换行符作为符号给bison
%%
int yywrap()
{
  return 1;
}

