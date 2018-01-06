%{
    #include "SQLParser.hpp"
    
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    #include <sstream>
    #include <string>
    
    extern int yyerror(const char *);
%}

%%
DATABASE                {   return DATABASE;    }
DATABASES               {   return DATABASES;   }
TABLE                   {   return TABLE;       }
TABLES                  {   return TABLES;      }
SHOW                    {   return SHOW;        }
CREATE                  {   return CREATE;      }
DROP                    {   return DROP;        }
USE                     {   return USE;         }
PRIMARY                 {   return PRIMARY;     }
KEY                     {   return KEY;         }
NOT                     {   return NOT;         }
NULL                    {   return NNULL;       }
INSERT                  {   return INSERT;      }
INTO                    {   return INTO;        }
VALUES                  {   return VALUES;      }
DELETE                  {   return DELETEE;     }
FROM                    {   return FROM;        }
WHERE                   {   return WHERE;       }
UPDATE                  {   return UPDATE;      }
SET                     {   return SET;         }
SELECT                  {   return SELECT;      }
IS                      {   return IS;          }
DESC                    {   return DESC;        }
REFERENCES              {   return REFERENCES;  }
INDEX                   {   return INDEX;       }
AND                     {   return AND;         }
FOREIGN                 {   return FOREIGN;     }
BOOL                    {   return BOOLL;       }
CHAR                    {   return CHARR;       }
SHORT                   {   return SHORTT;      }
INT                     {   return INTEGER;     }
LONG                    {   return LONGG;       }
FLOAT                   {   return FLOATT;      }
DOUBLE                  {   return DOUBLEE;     }
VARCHAR                 {   return VARCHAR;     }
LOB                     {   return LOB;         }
DATE                    {   return DATEE;       }

[;,\(\)\.]              {   return *yytext;     }
\=                      {   return *yytext;     }
\<\>                    {   return *yytext;     }
\<\=                    {   return *yytext;     }
\>\=                    {   return *yytext;     }
\<                      {   return *yytext;     }
\>                      {   return *yytext;     }


(true)|(True)|(TRUE)|(false)|(False)|(FALSE) {
    //布尔类型，在这一步中就当成整数0或1
    bool val = (yytext[0] == 't' || yytext[0] == 'T');
    yylval.v_u = val ? 1 : 0;
    return VALUE_UINT64;
}

[A-Za-z][_0-9A-Za-z]* {
    //名称(库名, 表名, 列名)
    std::stringstream buf;
    std::string str;
    buf << yytext;
    buf >> str;
    yylval.v_s = new std::string(str);
    //std::cout << "Lexer.identifier = " << * yylval.v_s << std::endl;
    return IDENTIFIER;
}

[+-]?[0-9]+ {
    //十进制整数，支持前缀正负号
    std::stringstream buf;
    buf << yytext;
    buf >> yylval.v_u;
    //std::cout << "Lexer.VALUE_UINT64 = " << yylval.v_u << std::endl;
    return VALUE_UINT64;
}

[+-]?0[xX][0-9A-Fa-f]+ {
    //十六进制整数，支持大小写混用，支持前缀正负号
    std::stringstream buf;
    buf << yytext;
    buf >> std::hex >> yylval.v_u;
    //std::cout << "Lexer.VALUE_UINT64 = " << yylval.v_u << std::endl;
    return VALUE_UINT64;
}

[+-]?[0-9]+.[0-9]+([eE][+-]?[0-9]+)? {
    //浮点数，支持前缀正负号，支持科学计数法
    std::stringstream buf;
    buf << yytext;
    buf >> yylval.v_d;
    //std::cout << "Lexer.VALUE_DOUBLE = " << yylval.v_d << std::endl;
    return VALUE_DOUBLE;
}

('[^']*')|(\"[^\"]*\")  {
    //字符串，支持单引号和双引号
    std::string str = yytext;
    str = str.substr(1, str.length() - 2);
    yylval.v_s = new std::string(str);
    //std::cout << "Lexer.VALUE_STRING = " << * yylval.v_s << std::endl;
    return VALUE_STRING;
}

[ \t]+ {
    //空格和制表符
    //std::cout << "Lexer.WHITE_SPACE" << std::endl;
}

\n|\r|(\r\n) {
    //直接返回换行符作为符号给bison
    //std::cout << "Lexer.END_LINE" << std::endl;
    //setCmdColor(0);
    return '\n';
}
%%

int yywrap() {
    return 1;
}

