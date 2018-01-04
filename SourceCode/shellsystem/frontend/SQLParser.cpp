
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "SQLParser.y"

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
    
    //删除该文件夹，包括其中所有的文件和文件夹，可以是相对路径也可以是绝对路径
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
    


/* Line 189 of yacc.c  */
#line 119 "SQLParser.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     DELETE = 273,
     FROM = 274,
     WHERE = 275,
     UPDATE = 276,
     SET = 277,
     SELECT = 278,
     IS = 279,
     INTEGER = 280,
     VARCHAR = 281,
     DESC = 282,
     REFERENCES = 283,
     INDEX = 284,
     AND = 285,
     DATE = 286,
     FLOAT = 287,
     FOREIGN = 288,
     VALUE_UINT64 = 289,
     VALUE_STRING = 290,
     VALUE_DOUBLE = 291,
     IDENTIFIER = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 92 "SQLParser.y"

    unsigned long long v_u;
    double v_d;
    TableDataType v_t;
    std::string * v_s;
    TableColumn * v_tc;
    std::vector<TableColumn *> * v_th;



/* Line 214 of yacc.c  */
#line 203 "SQLParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 215 "SQLParser.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   144

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  155

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      46,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,     2,     2,    35,     2,    38,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
      40,    39,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    42,
      43,    44,    45
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,     8,    10,    12,    14,    16,    17,
      21,    26,    31,    35,    39,    47,    52,    56,    63,    70,
      78,    86,    94,   102,   104,   108,   111,   116,   122,   133,
     135,   137,   139,   141,   145,   151,   153,   157,   159,   161,
     163,   165,   169,   171,   175,   179,   184,   186,   190,   192,
     195,   198,   201,   203,   205,   207,   209,   213,   219,   221,
     223,   227,   229,   233,   235,   237
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    48,    49,    46,    -1,    -1,    50,    -1,
      51,    -1,    52,    -1,    53,    -1,    -1,     7,     4,    34,
      -1,     8,     3,    69,    34,    -1,     9,     3,    69,    34,
      -1,    10,    69,    34,    -1,     7,     6,    34,    -1,     8,
       5,    70,    36,    54,    37,    34,    -1,     9,     5,    70,
      34,    -1,    27,    70,    34,    -1,    15,    16,    70,    17,
      57,    34,    -1,    18,    19,    70,    20,    60,    34,    -1,
      21,    70,    22,    65,    20,    60,    34,    -1,    23,    66,
      19,    67,    20,    60,    34,    -1,     8,    29,    70,    36,
      71,    37,    34,    -1,     9,    29,    70,    36,    71,    37,
      34,    -1,    55,    -1,    54,    35,    55,    -1,    71,    56,
      -1,    71,    56,    13,    14,    -1,    11,    12,    36,    68,
      37,    -1,    33,    12,    36,    71,    37,    28,    70,    36,
      71,    37,    -1,    25,    -1,    26,    -1,    31,    -1,    32,
      -1,    36,    58,    37,    -1,    57,    35,    36,    58,    37,
      -1,    59,    -1,    58,    35,    59,    -1,    42,    -1,    44,
      -1,    43,    -1,    14,    -1,    60,    30,    61,    -1,    61,
      -1,    62,    63,    64,    -1,    62,    24,    14,    -1,    62,
      24,    13,    14,    -1,    71,    -1,    70,    38,    71,    -1,
      39,    -1,    40,    41,    -1,    40,    39,    -1,    41,    39,
      -1,    40,    -1,    41,    -1,    59,    -1,    62,    -1,    71,
      39,    59,    -1,    65,    35,    71,    39,    59,    -1,    62,
      -1,    70,    -1,    67,    35,    70,    -1,    71,    -1,    68,
      35,    71,    -1,    45,    -1,    45,    -1,    45,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   107,   111,   113,   115,   117,   118,   122,
     129,   150,   172,   192,   212,   237,   255,   259,   263,   267,
     271,   277,   281,   287,   295,   303,   313,   322,   326,   332,
     337,   342,   347,   355,   359,   365,   369,   375,   379,   383,
     387,   393,   397,   402,   406,   410,   416,   420,   426,   430,
     434,   438,   442,   446,   452,   456,   462,   466,   472,   478,
     482,   485,   489,   495,   502,   509
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DATABASE", "DATABASES", "TABLE",
  "TABLES", "SHOW", "CREATE", "DROP", "USE", "PRIMARY", "KEY", "NOT",
  "NNULL", "INSERT", "INTO", "VALUES", "DELETE", "FROM", "WHERE", "UPDATE",
  "SET", "SELECT", "IS", "INTEGER", "VARCHAR", "DESC", "REFERENCES",
  "INDEX", "AND", "DATE", "FLOAT", "FOREIGN", "';'", "','", "'('", "')'",
  "'.'", "'='", "'<'", "'>'", "VALUE_UINT64", "VALUE_STRING",
  "VALUE_DOUBLE", "IDENTIFIER", "'\\n'", "$accept", "program", "stmt",
  "sysStmt", "dbStmt", "tbStmt", "idxStmt", "fieldList", "field", "type",
  "valueLists", "valueList", "value", "whereClause", "filterItem", "col",
  "op", "expr", "setClause", "selector", "tableList", "columnList",
  "dbName", "tbName", "colName", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,    59,    44,    40,    41,    46,    61,
      60,    62,   289,   290,   291,   292,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    49,    49,    49,    49,    49,    50,
      51,    51,    51,    51,    52,    52,    52,    52,    52,    52,
      52,    53,    53,    54,    54,    55,    55,    55,    55,    56,
      56,    56,    56,    57,    57,    58,    58,    59,    59,    59,
      59,    60,    60,    61,    61,    61,    62,    62,    63,    63,
      63,    63,    63,    63,    64,    64,    65,    65,    66,    67,
      67,    68,    68,    69,    70,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     1,     1,     1,     1,     0,     3,
       4,     4,     3,     3,     7,     4,     3,     6,     6,     7,
       7,     7,     7,     1,     3,     2,     4,     5,    10,     1,
       1,     1,     1,     3,     5,     1,     3,     1,     1,     1,
       1,     3,     1,     3,     3,     4,     1,     3,     1,     2,
       2,     2,     1,     1,     1,     1,     3,     5,     1,     1,
       3,     1,     3,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     8,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,    63,     0,     0,     0,    64,
       0,    65,    58,     0,     0,    46,     0,     2,     9,    13,
       0,     0,     0,     0,     0,     0,    12,     0,     0,     0,
       0,     0,    16,    10,     0,     0,    11,    15,     0,     0,
       0,    65,     0,     0,     0,    59,    47,     0,     0,     0,
      23,     0,     0,     0,     0,     0,     0,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    29,    30,
      31,    32,    25,     0,     0,    40,    37,    39,    38,     0,
      35,    17,     0,     0,    18,     0,    48,    52,    53,     0,
       0,     0,    56,     0,    60,     0,     0,    24,    14,     0,
      21,    22,     0,    33,     0,    41,     0,    44,    50,    49,
      51,    54,    55,    43,    19,     0,    20,     0,    61,     0,
      26,    36,     0,    45,    57,     0,    27,     0,    34,    62,
       0,     0,     0,     0,    28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    12,    13,    14,    15,    16,    69,    70,    92,
      75,    99,   100,    76,    77,    78,   109,   133,    62,    33,
      64,   137,    26,    34,    35
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -77
static const yytype_int8 yypact[] =
{
     -77,    55,   -77,    71,    18,    31,   -28,    24,    53,    26,
      50,    26,    38,   -77,   -77,   -77,   -77,    62,    64,   -28,
      26,    26,   -28,    26,    26,   -77,    65,    26,    26,   -77,
      78,    63,   -77,    83,    67,   -77,    72,   -77,   -77,   -77,
      73,    74,    75,    79,    80,    76,   -77,    91,    89,    70,
      26,    70,   -77,   -77,    -3,    70,   -77,   -77,    70,    81,
      50,   -77,    -4,    77,     2,   -77,   -77,   106,   107,    46,
     -77,    54,    84,    85,    10,    -8,   -21,   -77,     4,    50,
      70,    10,    50,    26,    87,    88,    -3,    86,   -77,   -77,
     -77,   -77,   112,    92,    93,   -77,   -77,   -77,   -77,    52,
     -77,   -77,    94,    50,   -77,    43,   -77,    49,    90,     6,
      -5,    95,   -77,     5,   -77,    70,    70,   -77,   -77,   114,
     -77,   -77,    10,   -77,    10,   -77,   117,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,    10,   -77,    56,   -77,    96,
     -77,   -77,    57,   -77,   -77,    70,   -77,   104,   -77,   -77,
      26,    99,    70,   100,   -77
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,    58,   -77,
     -77,    12,   -76,   -13,    35,    -6,   -77,   -77,   -77,   -77,
     -77,   -77,    39,    -9,   -48
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -65
static const yytype_int16 yytable[] =
{
      30,    63,    36,    66,    32,   112,    71,    72,    67,   103,
      73,    41,    42,   104,    44,    45,    79,    25,    47,    48,
      95,    19,    82,    20,    95,   103,   101,   102,   105,   134,
      68,    80,   111,   131,    22,   103,    23,    83,    71,   136,
      27,    65,    61,   106,   107,   108,   141,    21,    96,    97,
      98,    31,    96,    97,    98,     2,   126,   127,    40,   144,
      24,    43,     3,     4,     5,     6,   110,   138,   139,   113,
       7,    29,    28,     8,   114,    17,     9,    18,    10,    88,
      89,    86,    11,    87,    37,    90,    91,   122,   128,   123,
     129,   145,   122,   146,   148,    31,    38,   149,    39,    46,
      49,   -64,    50,   132,   153,    51,    52,    53,    59,    60,
      54,    55,    58,    56,    57,    61,    81,    74,    84,    85,
     118,    93,    94,   115,   116,   119,   120,   121,   140,   130,
     124,   143,   150,   147,   135,   152,   142,   154,   125,     0,
       0,   151,     0,     0,   117
};

static const yytype_int16 yycheck[] =
{
       9,    49,    11,    51,    10,    81,    54,    55,    11,    30,
      58,    20,    21,    34,    23,    24,    20,    45,    27,    28,
      14,     3,    20,     5,    14,    30,    34,    35,    24,    34,
      33,    35,    80,   109,     3,    30,     5,    35,    86,    34,
      16,    50,    45,    39,    40,    41,   122,    29,    42,    43,
      44,    45,    42,    43,    44,     0,    13,    14,    19,   135,
      29,    22,     7,     8,     9,    10,    79,   115,   116,    82,
      15,    45,    19,    18,    83,     4,    21,     6,    23,    25,
      26,    35,    27,    37,    46,    31,    32,    35,    39,    37,
      41,    35,    35,    37,    37,    45,    34,   145,    34,    34,
      22,    38,    19,   109,   152,    38,    34,    34,    17,    20,
      36,    36,    36,    34,    34,    45,    39,    36,    12,    12,
      34,    37,    37,    36,    36,    13,    34,    34,    14,    39,
      36,    14,    28,    37,    39,    36,   124,    37,   103,    -1,
      -1,   150,    -1,    -1,    86
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,     0,     7,     8,     9,    10,    15,    18,    21,
      23,    27,    49,    50,    51,    52,    53,     4,     6,     3,
       5,    29,     3,     5,    29,    45,    69,    16,    19,    45,
      70,    45,    62,    66,    70,    71,    70,    46,    34,    34,
      69,    70,    70,    69,    70,    70,    34,    70,    70,    22,
      19,    38,    34,    34,    36,    36,    34,    34,    36,    17,
      20,    45,    65,    71,    67,    70,    71,    11,    33,    54,
      55,    71,    71,    71,    36,    57,    60,    61,    62,    20,
      35,    39,    20,    35,    12,    12,    35,    37,    25,    26,
      31,    32,    56,    37,    37,    14,    42,    43,    44,    58,
      59,    34,    35,    30,    34,    24,    39,    40,    41,    63,
      60,    71,    59,    60,    70,    36,    36,    55,    34,    13,
      34,    34,    35,    37,    36,    61,    13,    14,    39,    41,
      39,    59,    62,    64,    34,    39,    34,    68,    71,    71,
      14,    59,    58,    14,    59,    35,    37,    37,    37,    71,
      28,    70,    36,    71,    37
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 105 "SQLParser.y"
    {
        ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 123 "SQLParser.y"
    {
            std::cout << "show databases!" << std::endl;
        ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 130 "SQLParser.y"
    {
            //新建一个数据库
            //关闭已经打开的数据库
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //如果已有这个数据库，报错
            if (access((yyvsp[(3) - (4)].v_s) -> c_str(), W_OK) == 0) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "已有数据库:" << * (yyvsp[(3) - (4)].v_s) << std::endl;
            } else {
                //新建这个数据库，并打开
                mkdir((yyvsp[(3) - (4)].v_s) -> c_str());
                chdir((yyvsp[(3) - (4)].v_s) -> c_str());
                dbNow = new TableManager(bufPageManager, * (yyvsp[(3) - (4)].v_s));
            }
        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 151 "SQLParser.y"
    {
            //删除一个数据库
            //关闭已经打开的数据库
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //如果不存在这个数据库，报错
            if (access((yyvsp[(3) - (4)].v_s) -> c_str(), W_OK) == -1) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "不存在数据库:" << * (yyvsp[(3) - (4)].v_s) << std::endl;
            } else {
                //删除这个数据库
                int rmrs = removeDir((yyvsp[(3) - (4)].v_s) -> c_str());
                if (rmrs == -1) {
                    std::cout << "删不掉这个数据库" << std::endl;
                }
            }
        ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 173 "SQLParser.y"
    {
            //打开一个数据库
            //关闭已经打开的数据库
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //如果不存在这个数据库，报错
            if (access((yyvsp[(2) - (3)].v_s) -> c_str(), W_OK) == -1) {
                std::cout << "Parser.USE: error" << std::endl;
                std::cout << "不存在数据库:" << * (yyvsp[(2) - (3)].v_s) << std::endl;
            } else {
                //打开这个数据库
                chdir((yyvsp[(2) - (3)].v_s) -> c_str());
                dbNow = new TableManager(bufPageManager, * (yyvsp[(2) - (3)].v_s));
            }
        ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 193 "SQLParser.y"
    {
            //查看这个数据库的所有数据表
            //如果没有打开数据库，报错
            if (dbNow == NULL) {
                std::cout << "Parser.SHOW TABLES: error" << std::endl;
                std::cout << "没有正在使用的数据库" << std::endl;
            } else {
                //打印数据库中的数据表
                int n = dbNow -> getNTable();
                std::cout << "共有" << n << "个数据表: ";
                for (int i = 0; i < n; i ++) {
                    std::cout << dbNow -> getTableById(i) -> getName() << ", ";
                }
                std::cout << std::endl;
            }
        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 213 "SQLParser.y"
    {
            //在已经打开的数据库中创建一个数据表
            //如果没有打开数据库，报错
            if (dbNow == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "没有已经打开的数据库:" << * (yyvsp[(3) - (7)].v_s) << std::endl;
            } else {
                //如果已有同名数据表，报错
                if (dbNow -> hasOpenedTable(* (yyvsp[(3) - (7)].v_s))) {
                    std::cout << "Parser.CREATE TABLE: error" << std::endl;
                    std::cout << "已有这个数据表:" << * (yyvsp[(3) - (7)].v_s) << std::endl;
                } else {
                    //创建数据表
                    TableHeader * tbHd = new TableHeader();
                    tbHd -> setName(* (yyvsp[(3) - (7)].v_s));
                    for (int i = 0; i < (yyvsp[(5) - (7)].v_th) -> size(); i ++) {
                        tbHd -> addColumn((* (yyvsp[(5) - (7)].v_th)) [i]);
                    }
                    tbHd -> setConstant();
                    dbNow -> createTable(tbHd);
                }
            }
        ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 238 "SQLParser.y"
    {
            //在已经打开的数据库中删除一个数据表
            //如果没有打开数据库，报错
            if (dbNow == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "没有已经打开的数据库"<< std::endl;
            } else {
                Table * table = dbNow -> getTableByName(* (yyvsp[(3) - (4)].v_s));
                if (table == NULL) {
                    std::cout << "Parser.DROP TABLE: error" << std::endl;
                    std::cout << "没有这个表:" << * (yyvsp[(3) - (4)].v_s) << std::endl;
                } else {
                    dbNow -> eraseTable(* (yyvsp[(3) - (4)].v_s));
                }
            }
        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 256 "SQLParser.y"
    {
        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 260 "SQLParser.y"
    {
        ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 264 "SQLParser.y"
    {
        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 268 "SQLParser.y"
    {
        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 272 "SQLParser.y"
    {
        ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 278 "SQLParser.y"
    {
        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 282 "SQLParser.y"
    {
        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 288 "SQLParser.y"
    {
            //std::cout << "Parser.fieldList: (" << $1 -> getName() << " " << $1 -> getDataType() << ")" << std::endl;
            (yyval.v_th) = new std::vector<TableColumn *>();
            (yyval.v_th) -> clear();
            (yyval.v_th) -> push_back((yyvsp[(1) - (1)].v_tc));
        ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 296 "SQLParser.y"
    {
            (yyval.v_th) = (yyvsp[(1) - (3)].v_th);
            (yyval.v_th) -> push_back((yyvsp[(3) - (3)].v_tc));
        ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 304 "SQLParser.y"
    {
            //std::cout << "Parser.field: (" << * $1 << " " << $2 << ")" << std::endl;
            (yyval.v_tc) = new TableColumn();
            (yyval.v_tc) -> setName(* (yyvsp[(1) - (2)].v_s));
            (yyval.v_tc) -> setType((yyvsp[(2) - (2)].v_t));
            (yyval.v_tc) -> setAllowNull(true);
            (yyval.v_tc) -> setConstant();
        ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 314 "SQLParser.y"
    {
            //std::cout << "Parser.field: (" << * $1 << " " << $2 << " NOT NULL)" << std::endl;
            (yyval.v_tc) = new TableColumn();
            (yyval.v_tc) -> setName(* (yyvsp[(1) - (4)].v_s));
            (yyval.v_tc) -> setType((yyvsp[(2) - (4)].v_t));
            (yyval.v_tc) -> setConstant();
        ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 323 "SQLParser.y"
    {
        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 327 "SQLParser.y"
    {
        ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 333 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_int;
        ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 338 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_string;
        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 343 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_int;
        ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 348 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_float;
        ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 356 "SQLParser.y"
    {
        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 360 "SQLParser.y"
    {
        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 366 "SQLParser.y"
    {
        ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 370 "SQLParser.y"
    {
        ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 376 "SQLParser.y"
    {
        ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 380 "SQLParser.y"
    {
        ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 384 "SQLParser.y"
    {
        ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 388 "SQLParser.y"
    {
        ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 394 "SQLParser.y"
    {
        ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 398 "SQLParser.y"
    {
        ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 403 "SQLParser.y"
    {
        ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 407 "SQLParser.y"
    {
        ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 411 "SQLParser.y"
    {
        ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 417 "SQLParser.y"
    {
        ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 421 "SQLParser.y"
    {
        ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 427 "SQLParser.y"
    {
        ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 431 "SQLParser.y"
    {
        ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 435 "SQLParser.y"
    {
        ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 439 "SQLParser.y"
    {
        ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 443 "SQLParser.y"
    {
        ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 447 "SQLParser.y"
    {
        ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 453 "SQLParser.y"
    {
        ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 457 "SQLParser.y"
    {
        ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 463 "SQLParser.y"
    {
        ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 467 "SQLParser.y"
    {
        ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 473 "SQLParser.y"
    {
        ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 479 "SQLParser.y"
    {
        ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 486 "SQLParser.y"
    {
        ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 490 "SQLParser.y"
    {
        ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 496 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 503 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 510 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(1) - (1)].v_s);
        ;}
    break;



/* Line 1455 of yacc.c  */
#line 2114 "SQLParser.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 515 "SQLParser.y"


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

