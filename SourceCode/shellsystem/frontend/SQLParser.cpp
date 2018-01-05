
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

    #include "../ShellAssistant.h"
    
    #include "lex.yy.c"
    
    int yylex();
    int yyerror(const char *);
    
    BufPageManager * bufPageManager;
    TableManager * dbNow;
    


/* Line 189 of yacc.c  */
#line 87 "SQLParser.cpp"

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
     DELETEE = 273,
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
     DATEE = 286,
     FLOATT = 287,
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
#line 60 "SQLParser.y"

    unsigned long long v_u;
    double v_d;
    TableDataType v_t;
    std::string * v_s;
    TableColumn * v_tc;
    std::vector<TableColumn *> * v_th;



/* Line 214 of yacc.c  */
#line 171 "SQLParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 183 "SQLParser.cpp"

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
#define YYLAST   156

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  170

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
       0,     0,     3,     6,     7,     9,    11,    13,    15,    17,
      22,    28,    34,    39,    44,    53,    59,    64,    72,    80,
      89,    98,   107,   116,   118,   122,   125,   130,   136,   147,
     149,   151,   153,   155,   159,   165,   167,   171,   173,   175,
     177,   179,   183,   185,   189,   193,   198,   200,   204,   206,
     209,   212,   215,   217,   219,   221,   223,   227,   233,   235,
     237,   241,   243,   247,   249,   251,   253
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    48,    49,    -1,    -1,    50,    -1,    51,
      -1,    52,    -1,    53,    -1,    72,    -1,     7,     4,    34,
      72,    -1,     8,     3,    69,    34,    72,    -1,     9,     3,
      69,    34,    72,    -1,    10,    69,    34,    72,    -1,     7,
       6,    34,    72,    -1,     8,     5,    70,    36,    54,    37,
      34,    72,    -1,     9,     5,    70,    34,    72,    -1,    27,
      70,    34,    72,    -1,    15,    16,    70,    17,    57,    34,
      72,    -1,    18,    19,    70,    20,    60,    34,    72,    -1,
      21,    70,    22,    65,    20,    60,    34,    72,    -1,    23,
      66,    19,    67,    20,    60,    34,    72,    -1,     8,    29,
      70,    36,    71,    37,    34,    72,    -1,     9,    29,    70,
      36,    71,    37,    34,    72,    -1,    55,    -1,    54,    35,
      55,    -1,    71,    56,    -1,    71,    56,    13,    14,    -1,
      11,    12,    36,    68,    37,    -1,    33,    12,    36,    71,
      37,    28,    70,    36,    71,    37,    -1,    25,    -1,    26,
      -1,    31,    -1,    32,    -1,    36,    58,    37,    -1,    57,
      35,    36,    58,    37,    -1,    59,    -1,    58,    35,    59,
      -1,    42,    -1,    44,    -1,    43,    -1,    14,    -1,    60,
      30,    61,    -1,    61,    -1,    62,    63,    64,    -1,    62,
      24,    14,    -1,    62,    24,    13,    14,    -1,    71,    -1,
      70,    38,    71,    -1,    39,    -1,    40,    41,    -1,    40,
      39,    -1,    41,    39,    -1,    40,    -1,    41,    -1,    59,
      -1,    62,    -1,    71,    39,    59,    -1,    65,    35,    71,
      39,    59,    -1,    62,    -1,    70,    -1,    67,    35,    70,
      -1,    71,    -1,    68,    35,    71,    -1,    45,    -1,    45,
      -1,    45,    -1,    46,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    72,    72,    78,    84,    88,    92,    96,   100,   106,
     113,   134,   156,   176,   196,   219,   236,   269,   273,   277,
     281,   287,   291,   297,   305,   313,   323,   332,   336,   342,
     347,   352,   357,   365,   369,   375,   379,   385,   389,   393,
     397,   403,   407,   413,   417,   421,   427,   431,   437,   441,
     445,   449,   453,   457,   463,   467,   473,   477,   483,   489,
     493,   496,   500,   506,   513,   520,   527
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DATABASE", "DATABASES", "TABLE",
  "TABLES", "SHOW", "CREATE", "DROP", "USE", "PRIMARY", "KEY", "NOT",
  "NNULL", "INSERT", "INTO", "VALUES", "DELETEE", "FROM", "WHERE",
  "UPDATE", "SET", "SELECT", "IS", "INTEGER", "VARCHAR", "DESC",
  "REFERENCES", "INDEX", "AND", "DATEE", "FLOATT", "FOREIGN", "';'", "','",
  "'('", "')'", "'.'", "'='", "'<'", "'>'", "VALUE_UINT64", "VALUE_STRING",
  "VALUE_DOUBLE", "IDENTIFIER", "'\\n'", "$accept", "program", "stmt",
  "sysStmt", "dbStmt", "tbStmt", "idxStmt", "fieldList", "field", "type",
  "valueLists", "valueList", "value", "whereClause", "filterItem", "col",
  "op", "expr", "setClause", "selector", "tableList", "columnList",
  "dbName", "tbName", "colName", "endLine", 0
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
      67,    68,    68,    69,    70,    71,    72
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     4,
       5,     5,     4,     4,     8,     5,     4,     7,     7,     8,
       8,     8,     8,     1,     3,     2,     4,     5,    10,     1,
       1,     1,     1,     3,     5,     1,     3,     1,     1,     1,
       1,     3,     1,     3,     3,     4,     1,     3,     1,     2,
       2,     2,     1,     1,     1,     1,     3,     5,     1,     1,
       3,     1,     3,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    66,     2,     4,     5,     6,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,    63,     0,     0,
       0,    64,     0,    65,    58,     0,     0,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,    13,     0,     0,     0,     0,
       0,     0,    12,     0,     0,    65,     0,     0,     0,    59,
      47,    16,    10,     0,     0,     0,    23,     0,     0,    11,
      15,     0,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,    30,    31,    32,
      25,     0,     0,    40,    37,    39,    38,     0,    35,     0,
       0,     0,     0,     0,    48,    52,    53,     0,     0,     0,
      56,     0,    60,     0,     0,    24,     0,     0,     0,     0,
       0,    33,    17,     0,    41,    18,     0,    44,    50,    49,
      51,    54,    55,    43,     0,     0,     0,     0,    61,     0,
      14,    26,    21,    22,    36,     0,    45,    19,    57,    20,
       0,    27,     0,    34,    62,     0,     0,     0,     0,    28
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    13,    14,    15,    16,    17,    75,    76,   100,
      83,   107,   108,    84,    85,    86,   117,   143,    66,    35,
      68,   147,    28,    36,    37,    18
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -84
static const yytype_int16 yypact[] =
{
     -84,    43,   -84,    61,    20,    30,    -8,    25,    27,    10,
      50,    10,   -84,   -84,   -84,   -84,   -84,   -84,   -84,    38,
      47,    -8,    10,    10,    -8,    10,    10,   -84,    62,    10,
      10,   -84,    76,    72,   -84,    90,    78,   -84,    67,    74,
      74,    88,    87,    89,    92,    93,    94,    74,   107,   108,
      86,    10,    86,    74,   -84,   -84,    74,    -7,    86,    74,
      74,    86,   -84,    96,    50,   -84,   -13,    95,     9,   -84,
     -84,   -84,   -84,   117,   121,    36,   -84,    82,    98,   -84,
     -84,    99,    42,    71,   -15,   -84,    63,    50,    86,    42,
      50,    10,   101,   102,    -7,   105,   -84,   -84,   -84,   -84,
     127,   109,   110,   -84,   -84,   -84,   -84,    53,   -84,    74,
     106,    50,    74,    55,   -84,    52,   111,    34,    -2,   112,
     -84,     6,   -84,    86,    86,   -84,    74,   131,    74,    74,
      42,   -84,   -84,    42,   -84,   -84,   132,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,    74,    42,    74,    57,   -84,   104,
     -84,   -84,   -84,   -84,   -84,    84,   -84,   -84,   -84,   -84,
      86,   -84,   119,   -84,   -84,    10,   113,    86,   115,   -84
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -84,   -84,   -84,   -84,   -84,   -84,   -84,   -84,    54,   -84,
     -84,    21,   -83,   -33,    44,    -5,   -84,   -84,   -84,   -84,
     -84,   -84,    39,    -9,   -49,   -29
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -65
static const yytype_int16 yytable[] =
{
      32,    67,    38,    70,    73,    34,   120,    87,    77,    78,
      54,    55,    81,    42,    43,   111,    45,    46,    62,   112,
      48,    49,    88,    21,    71,    22,    74,    72,   111,    90,
      79,    80,   144,    24,   141,    25,   111,    27,    65,   119,
     146,    29,    69,     2,    91,    77,    30,   154,   103,    23,
       3,     4,     5,     6,   118,    31,   103,   121,     7,    26,
      41,     8,   158,    44,     9,    19,    10,    20,   136,   137,
      11,    94,    39,    95,   148,   149,   104,   105,   106,    33,
     132,    40,   122,   135,   104,   105,   106,   113,   130,    12,
     131,   138,   160,   139,   161,    33,    47,   150,    50,   152,
     153,    53,   114,   115,   116,   109,   110,    96,    97,    51,
     -64,   164,   142,    98,    99,   157,    52,   159,   168,   130,
      12,   163,    56,    57,    63,    58,    59,    60,    64,    92,
      61,    65,    82,    93,    89,   101,   102,   123,   124,   126,
     127,   162,   133,   128,   129,   151,   156,   165,   125,   167,
     140,   145,   169,     0,   155,   134,   166
};

static const yytype_int16 yycheck[] =
{
       9,    50,    11,    52,    11,    10,    89,    20,    57,    58,
      39,    40,    61,    22,    23,    30,    25,    26,    47,    34,
      29,    30,    35,     3,    53,     5,    33,    56,    30,    20,
      59,    60,    34,     3,   117,     5,    30,    45,    45,    88,
      34,    16,    51,     0,    35,    94,    19,   130,    14,    29,
       7,     8,     9,    10,    87,    45,    14,    90,    15,    29,
      21,    18,   145,    24,    21,     4,    23,     6,    13,    14,
      27,    35,    34,    37,   123,   124,    42,    43,    44,    45,
     109,    34,    91,   112,    42,    43,    44,    24,    35,    46,
      37,    39,    35,    41,    37,    45,    34,   126,    22,   128,
     129,    34,    39,    40,    41,    34,    35,    25,    26,    19,
      38,   160,   117,    31,    32,   144,    38,   146,   167,    35,
      46,    37,    34,    36,    17,    36,    34,    34,    20,    12,
      36,    45,    36,    12,    39,    37,    37,    36,    36,    34,
      13,    37,    36,    34,    34,    14,    14,    28,    94,    36,
      39,    39,    37,    -1,   133,   111,   165
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,     0,     7,     8,     9,    10,    15,    18,    21,
      23,    27,    46,    49,    50,    51,    52,    53,    72,     4,
       6,     3,     5,    29,     3,     5,    29,    45,    69,    16,
      19,    45,    70,    45,    62,    66,    70,    71,    70,    34,
      34,    69,    70,    70,    69,    70,    70,    34,    70,    70,
      22,    19,    38,    34,    72,    72,    34,    36,    36,    34,
      34,    36,    72,    17,    20,    45,    65,    71,    67,    70,
      71,    72,    72,    11,    33,    54,    55,    71,    71,    72,
      72,    71,    36,    57,    60,    61,    62,    20,    35,    39,
      20,    35,    12,    12,    35,    37,    25,    26,    31,    32,
      56,    37,    37,    14,    42,    43,    44,    58,    59,    34,
      35,    30,    34,    24,    39,    40,    41,    63,    60,    71,
      59,    60,    70,    36,    36,    55,    34,    13,    34,    34,
      35,    37,    72,    36,    61,    72,    13,    14,    39,    41,
      39,    59,    62,    64,    34,    39,    34,    68,    71,    71,
      72,    14,    72,    72,    59,    58,    14,    72,    59,    72,
      35,    37,    37,    37,    71,    28,    70,    36,    71,    37
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
#line 73 "SQLParser.y"
    {
            setCmdColor(1);
        ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 78 "SQLParser.y"
    {
            setCmdColor(1);
        ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 85 "SQLParser.y"
    {
        ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 89 "SQLParser.y"
    {
        ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 93 "SQLParser.y"
    {
        ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 97 "SQLParser.y"
    {
        ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 101 "SQLParser.y"
    {
        ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 107 "SQLParser.y"
    {
            std::cout << "show databases!" << std::endl;
        ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 114 "SQLParser.y"
    {
            //�½�һ�����ݿ�
            //�ر��Ѿ��򿪵����ݿ�
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //�������������ݿ⣬����
            if (access((yyvsp[(3) - (5)].v_s) -> c_str(), W_OK) == 0) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "�������ݿ�:" << * (yyvsp[(3) - (5)].v_s) << std::endl;
            } else {
                //�½�������ݿ⣬����
                mkdir((yyvsp[(3) - (5)].v_s) -> c_str());
                chdir((yyvsp[(3) - (5)].v_s) -> c_str());
                dbNow = new TableManager(bufPageManager, * (yyvsp[(3) - (5)].v_s));
            }
        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 135 "SQLParser.y"
    {
            //ɾ��һ�����ݿ�
            //�ر��Ѿ��򿪵����ݿ�
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //���������������ݿ⣬����
            if (access((yyvsp[(3) - (5)].v_s) -> c_str(), W_OK) == -1) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "���������ݿ�:" << * (yyvsp[(3) - (5)].v_s) << std::endl;
            } else {
                //ɾ��������ݿ�
                int rmrs = removeDir((yyvsp[(3) - (5)].v_s) -> c_str());
                if (rmrs == -1) {
                    std::cout << "ɾ����������ݿ�" << std::endl;
                }
            }
        ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 157 "SQLParser.y"
    {
            //��һ�����ݿ�
            //�ر��Ѿ��򿪵����ݿ�
            if (dbNow != NULL) {
                chdir("../");
                delete dbNow;
                dbNow = NULL;
            }
            //���������������ݿ⣬����
            if (access((yyvsp[(2) - (4)].v_s) -> c_str(), W_OK) == -1) {
                std::cout << "Parser.USE: error" << std::endl;
                std::cout << "���������ݿ�:" << * (yyvsp[(2) - (4)].v_s) << std::endl;
            } else {
                //��������ݿ�
                chdir((yyvsp[(2) - (4)].v_s) -> c_str());
                dbNow = new TableManager(bufPageManager, * (yyvsp[(2) - (4)].v_s));
            }
        ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 177 "SQLParser.y"
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
                    std::cout << dbNow -> getTableById(i) -> getName() << ( i < nTab ? ", " : ".");
                }
                std::cout << std::endl;
            }
        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 197 "SQLParser.y"
    {
            //���Ѿ��򿪵����ݿ��д���һ�����ݱ�
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�:" << * (yyvsp[(3) - (8)].v_s) << std::endl;
            } else if (dbNow -> hasOpenedTable(* (yyvsp[(3) - (8)].v_s))) {
                //�������ͬ�����ݱ�����
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "����������ݱ�:" << * (yyvsp[(3) - (8)].v_s) << std::endl;
            } else {
                //�������ݱ�
                TableHeader * tbHd = new TableHeader();
                tbHd -> setName(* (yyvsp[(3) - (8)].v_s));
                for (int i = 0; i < (yyvsp[(5) - (8)].v_th) -> size(); i ++) {
                    tbHd -> addColumn((* (yyvsp[(5) - (8)].v_th)) [i]);
                }
                tbHd -> setConstant();
                dbNow -> createTable(tbHd);
            }
        ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 220 "SQLParser.y"
    {
            //���Ѿ��򿪵����ݿ���ɾ��һ�����ݱ�
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!dbNow -> hasOpenedTable(* (yyvsp[(3) - (5)].v_s))) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * (yyvsp[(3) - (5)].v_s) << std::endl;
            } else {
                //ɾ�����ݱ�
                dbNow -> eraseTable(* (yyvsp[(3) - (5)].v_s));
            }
        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 237 "SQLParser.y"
    {
            //��ӡ���ݱ��е�������
            //���û�д����ݿ⣬����
            if (dbNow == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!dbNow -> hasOpenedTable(* (yyvsp[(2) - (4)].v_s))) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * (yyvsp[(2) - (4)].v_s) << std::endl;
            } else {
                //��ӡ���ݱ����
                Table * table = dbNow -> getTableByName(* (yyvsp[(2) - (4)].v_s));
                int nCol = table -> getNCol();
                std::cout << "���ݱ�" << * (yyvsp[(2) - (4)].v_s) << "����" << nCol << "��������:" << std::endl;
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
        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 270 "SQLParser.y"
    {
        ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 274 "SQLParser.y"
    {
        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 278 "SQLParser.y"
    {
        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 282 "SQLParser.y"
    {
        ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 288 "SQLParser.y"
    {
        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 292 "SQLParser.y"
    {
        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 298 "SQLParser.y"
    {
            //std::cout << "Parser.fieldList: (" << $1 -> getName() << " " << $1 -> getDataType() << ")" << std::endl;
            (yyval.v_th) = new std::vector<TableColumn *>();
            (yyval.v_th) -> clear();
            (yyval.v_th) -> push_back((yyvsp[(1) - (1)].v_tc));
        ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 306 "SQLParser.y"
    {
            (yyval.v_th) = (yyvsp[(1) - (3)].v_th);
            (yyval.v_th) -> push_back((yyvsp[(3) - (3)].v_tc));
        ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 314 "SQLParser.y"
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
#line 324 "SQLParser.y"
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
#line 333 "SQLParser.y"
    {
        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 337 "SQLParser.y"
    {
        ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 343 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_int;
        ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 348 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_string;
        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 353 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_int;
        ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 358 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_float;
        ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 366 "SQLParser.y"
    {
        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 370 "SQLParser.y"
    {
        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 376 "SQLParser.y"
    {
        ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 380 "SQLParser.y"
    {
        ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 386 "SQLParser.y"
    {
        ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 390 "SQLParser.y"
    {
        ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 394 "SQLParser.y"
    {
        ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 398 "SQLParser.y"
    {
        ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 404 "SQLParser.y"
    {
        ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 408 "SQLParser.y"
    {
        ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 414 "SQLParser.y"
    {
        ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 418 "SQLParser.y"
    {
        ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 422 "SQLParser.y"
    {
        ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 428 "SQLParser.y"
    {
        ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 432 "SQLParser.y"
    {
        ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 438 "SQLParser.y"
    {
        ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 442 "SQLParser.y"
    {
        ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 446 "SQLParser.y"
    {
        ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 450 "SQLParser.y"
    {
        ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 454 "SQLParser.y"
    {
        ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 458 "SQLParser.y"
    {
        ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 464 "SQLParser.y"
    {
        ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 468 "SQLParser.y"
    {
        ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 474 "SQLParser.y"
    {
        ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 478 "SQLParser.y"
    {
        ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 484 "SQLParser.y"
    {
        ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 490 "SQLParser.y"
    {
        ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 497 "SQLParser.y"
    {
        ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 501 "SQLParser.y"
    {
        ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 507 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 514 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 521 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 528 "SQLParser.y"
    {
            setCmdColor(0);
        ;}
    break;



/* Line 1455 of yacc.c  */
#line 2174 "SQLParser.cpp"
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
#line 533 "SQLParser.y"


int yyerror(const char *emseg) {
    std::cout << "Parser: Unknown sentence! please try again!" << std::endl;
    //cout << "Error: " << emseg << endl;
}

int main() {
    FileManager * fileManager = new FileManager();
    bufPageManager = new BufPageManager(fileManager);
    dbNow = NULL;    
    cmdColorHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    myMain(yyparse);
}

