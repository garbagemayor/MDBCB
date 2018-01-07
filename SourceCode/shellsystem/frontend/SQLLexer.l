%{
    #include "SQLParser.hpp"
    #include "../ShellLexerAssistant.h"
    
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
PRIMARY                 {   return PRIMARY;     }
KEY                     {   return KEY;         }
NOT                     {   return NOT;         }
NULL                    {   return NNULL;       }
INTO                    {   return INTO;        }
VALUES                  {   return VALUES;      }
FROM                    {   return FROM;        }
WHERE                   {   return WHERE;       }
SET                     {   return SET;         }
IS                      {   return IS;          }
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
SHOW                    {   setCmdColor(0);     return SHOW;        }
CREATE                  {   setCmdColor(0);     return CREATE;      }
DROP                    {   setCmdColor(0);     return DROP;        }
USE                     {   setCmdColor(0);     return USE;         }
INSERT                  {   setCmdColor(0);     return INSERT;      }
DELETE                  {   setCmdColor(0);     return DELETEE;     }
UPDATE                  {   setCmdColor(0);     return UPDATE;      }
SELECT                  {   setCmdColor(0);     return SELECT;      }
DESC                    {   setCmdColor(0);     return DESC;        }

[;,\(\)\.]              {   return *yytext;     }
\=                      {   return OP_EQ;       }
\<\>                    {   return OP_NE;       }
\<\=                    {   return OP_LE;       }
\>\=                    {   return OP_GE;       }
\<                      {   return OP_LT;       }
\>                      {   return OP_GT;       }


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

