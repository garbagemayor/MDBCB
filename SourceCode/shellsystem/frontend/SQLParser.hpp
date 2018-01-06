
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DATABASE = 258,
     DATABASES = 259,
     TABLE = 260,
     TABLES = 261,
     SHOW = 262,
     CREATE = 263,
     DROP = 264,
     USE = 265,
     PRIMARY = 266,
     KEY = 267,
     NOT = 268,
     NNULL = 269,
     INSERT = 270,
     INTO = 271,
     VALUES = 272,
     DELETEE = 273,
     FROM = 274,
     WHERE = 275,
     UPDATE = 276,
     SET = 277,
     SELECT = 278,
     IS = 279,
     DESC = 280,
     REFERENCES = 281,
     INDEX = 282,
     AND = 283,
     DATEE = 284,
     FOREIGN = 285,
     BOOLL = 286,
     CHARR = 287,
     SHORTT = 288,
     INTEGER = 289,
     LONGG = 290,
     FLOATT = 291,
     DOUBLEE = 292,
     VARCHAR = 293,
     LOB = 294,
     VALUE_UINT64 = 295,
     VALUE_STRING = 296,
     VALUE_DOUBLE = 297,
     IDENTIFIER = 298
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 69 "SQLParser.y"

    
    UnionFieldList * u_fl;
    UnionField * u_fd;
    StringList * v_sl;
    
    std::string * v_s;
    unsigned long long v_u;
    double v_d;
    
    TableDataType v_t;



/* Line 1676 of yacc.c  */
#line 110 "SQLParser.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


