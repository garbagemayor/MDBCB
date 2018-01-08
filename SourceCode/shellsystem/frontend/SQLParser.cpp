
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


/* Line 189 of yacc.c  */
#line 82 "SQLParser.cpp"

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
     OP_EQ = 295,
     OP_NE = 296,
     OP_LE = 297,
     OP_GE = 298,
     OP_LT = 299,
     OP_GT = 300,
     VALUE_UINT64 = 301,
     VALUE_STRING = 302,
     VALUE_DOUBLE = 303,
     IDENTIFIER = 304
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 85 "SQLParser.y"

    
    UnionFieldList * u_fl;
    UnionField * u_fd;
    StringList * v_sl;
    
    UnionValue * u_va;
    UnionValueList * u_vr;
    UnionValueLists * u_vt;
    
    UnionWhereClause * u_wc;
    UnionWhereItem * u_wi;
    
    UnionSetItem * u_si;
    UnionSetClause * u_sc;
    
    UnionColList * u_cl;
    UnionCol * u_co;
    
    uint64 v_u;
    double v_d;
    std::string * v_s;
    
    TableDataType v_t;



/* Line 214 of yacc.c  */
#line 195 "SQLParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 207 "SQLParser.cpp"

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
#define YYLAST   178

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  80
/* YYNRULES -- Number of states.  */
#define YYNSTATES  186

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      55,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      48,    49,     2,     2,    47,     2,    50,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    51,    52,    53,    54
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    11,    13,    15,    17,
      22,    28,    34,    39,    43,    48,    57,    63,    68,    72,
      80,    86,    94,   103,   107,   110,   119,   128,   130,   134,
     137,   142,   148,   159,   163,   169,   171,   175,   177,   178,
     180,   184,   188,   192,   196,   201,   203,   207,   209,   213,
     215,   216,   218,   222,   226,   228,   232,   234,   236,   238,
     240,   242,   244,   246,   248,   250,   252,   254,   256,   258,
     260,   265,   270,   275,   277,   279,   281,   283,   285,   287,
     289
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      57,     0,    -1,    57,    58,    -1,    -1,    59,    -1,    60,
      -1,    61,    -1,    64,    -1,    82,    -1,     7,     4,    46,
      82,    -1,     8,     3,    80,    46,    82,    -1,     9,     3,
      80,    46,    82,    -1,    10,    80,    46,    82,    -1,    10,
      46,    82,    -1,     7,     6,    46,    82,    -1,     8,     5,
      80,    48,    65,    49,    46,    82,    -1,     9,     5,    80,
      46,    82,    -1,    25,    80,    46,    82,    -1,    25,    46,
      82,    -1,    15,    16,    80,    17,    67,    46,    82,    -1,
      62,    20,    69,    46,    82,    -1,    63,    22,    74,    20,
      69,    46,    82,    -1,    23,    72,    19,    77,    20,    69,
      46,    82,    -1,    18,    19,    80,    -1,    21,    80,    -1,
       8,    27,    80,    48,    80,    49,    46,    82,    -1,     9,
      27,    80,    48,    80,    49,    46,    82,    -1,    66,    -1,
      65,    47,    66,    -1,    80,    79,    -1,    80,    79,    13,
      14,    -1,    11,    12,    48,    77,    49,    -1,    30,    12,
      48,    80,    49,    26,    80,    48,    80,    49,    -1,    48,
      68,    49,    -1,    67,    47,    48,    68,    49,    -1,    78,
      -1,    68,    47,    78,    -1,    70,    -1,    -1,    71,    -1,
      69,    28,    71,    -1,    73,    81,    78,    -1,    73,    81,
      73,    -1,    73,    24,    14,    -1,    73,    24,    13,    14,
      -1,    73,    -1,    72,    47,    73,    -1,    80,    -1,    80,
      50,    80,    -1,    75,    -1,    -1,    76,    -1,    75,    47,
      76,    -1,    80,    40,    78,    -1,    80,    -1,    77,    47,
      80,    -1,    14,    -1,    51,    -1,    53,    -1,    52,    -1,
      31,    -1,    32,    -1,    33,    -1,    34,    -1,    35,    -1,
      36,    -1,    37,    -1,    38,    -1,    29,    -1,    39,    -1,
      34,    48,    51,    49,    -1,    38,    48,    51,    49,    -1,
      32,    48,    51,    49,    -1,    54,    -1,    40,    -1,    41,
      -1,    44,    -1,    45,    -1,    42,    -1,    43,    -1,    55,
      -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   114,   114,   121,   130,   134,   138,   142,   146,   152,
     187,   210,   234,   256,   267,   287,   342,   369,   407,   443,
     482,   505,   533,   559,   573,   587,   605,   625,   631,   639,
     651,   662,   670,   705,   711,   719,   725,   733,   739,   745,
     753,   763,   776,   789,   801,   815,   823,   833,   855,   888,
     894,   901,   907,   915,   924,   930,   938,   943,   950,   957,
     966,   971,   976,   981,   986,   991,   996,  1001,  1006,  1011,
    1016,  1029,  1038,  1049,  1056,  1061,  1066,  1071,  1076,  1081,
    1088
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
  "UPDATE", "SET", "SELECT", "IS", "DESC", "REFERENCES", "INDEX", "AND",
  "DATEE", "FOREIGN", "BOOLL", "CHARR", "SHORTT", "INTEGER", "LONGG",
  "FLOATT", "DOUBLEE", "VARCHAR", "LOB", "OP_EQ", "OP_NE", "OP_LE",
  "OP_GE", "OP_LT", "OP_GT", "';'", "','", "'('", "')'", "'.'",
  "VALUE_UINT64", "VALUE_STRING", "VALUE_DOUBLE", "IDENTIFIER", "'\\n'",
  "$accept", "program", "stmt", "sysStmt", "dbStmt", "tbStmt",
  "deleteFromTb", "updateTb", "idxStmt", "fieldList", "field",
  "valueLists", "valueList", "whereClause", "whereList", "whereItem",
  "selector", "col", "setClause", "setList", "setItem", "identList",
  "value", "type", "ident", "op", "endLine", 0
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,    59,    44,    40,    41,
      46,   301,   302,   303,   304,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    57,    58,    58,    58,    58,    58,    59,
      60,    60,    60,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    63,    64,    64,    65,    65,    66,
      66,    66,    66,    67,    67,    68,    68,    69,    69,    70,
      70,    71,    71,    71,    71,    72,    72,    73,    73,    74,
      74,    75,    75,    76,    77,    77,    78,    78,    78,    78,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    80,    81,    81,    81,    81,    81,    81,
      82
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     4,
       5,     5,     4,     3,     4,     8,     5,     4,     3,     7,
       5,     7,     8,     3,     2,     8,     8,     1,     3,     2,
       4,     5,    10,     3,     5,     1,     3,     1,     0,     1,
       3,     3,     3,     3,     4,     1,     3,     1,     3,     1,
       0,     1,     3,     3,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     4,     4,     1,     1,     1,     1,     1,     1,     1,
       1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    80,     2,     4,     5,     6,     0,     0,     7,
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      73,     0,     0,     0,    24,     0,    45,    47,     0,     0,
      38,    50,     0,     0,     0,     0,     0,     0,     0,     0,
      13,     0,     0,    23,     0,     0,     0,    18,     0,     0,
      37,    39,     0,     0,    49,    51,     0,     9,    14,     0,
       0,     0,     0,     0,     0,    12,     0,     0,    54,    46,
      48,    17,     0,     0,     0,    74,    75,    78,    79,    76,
      77,     0,    38,     0,     0,    10,     0,     0,     0,    27,
       0,     0,    11,    16,     0,     0,     0,    38,     0,    40,
      20,     0,    43,    56,    57,    59,    58,    42,    41,     0,
      52,    53,     0,     0,     0,     0,    68,    60,    61,    62,
      63,    64,    65,    66,    67,    69,    29,     0,     0,     0,
      35,     0,     0,     0,    55,    44,     0,     0,     0,    28,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    19,
       0,     0,    21,     0,     0,    15,     0,     0,     0,    30,
      25,    26,    36,     0,    22,    31,     0,    72,    70,    71,
      34,     0,     0,     0,     0,    32
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    13,    14,    15,    16,    17,    18,    19,    98,
      99,   106,   139,    59,    60,    61,    35,    62,    63,    64,
      65,    77,   140,   136,    37,    91,    20
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -91
static const yytype_int16 yypact[] =
{
     -91,    51,   -91,     8,    27,    36,    16,    -7,     4,   -16,
     -16,    50,   -91,   -91,   -91,   -91,   -91,    23,    33,   -91,
     -91,    39,    54,   -16,   -16,   -16,   -16,   -16,   -16,    43,
     -91,    63,   -16,   -16,   -91,   -11,   -91,    60,    43,    65,
     -16,   -16,    43,    43,    66,    67,    68,    71,    74,    73,
     -91,    43,    96,   -91,   -16,   -16,   -16,   -91,    43,     1,
     -91,   -91,    49,   102,    77,   -91,    85,   -91,   -91,    43,
      -5,   -16,    43,    43,   -16,   -91,    78,   -10,   -91,   -91,
     -91,   -91,   -16,    43,    20,   -91,   -91,   -91,   -91,   -91,
     -91,    26,   -16,   -16,    30,   -91,   115,   118,    37,   -91,
     114,    82,   -91,   -91,    83,    30,    61,   -16,   -16,   -91,
     -91,   119,   -91,   -91,   -91,   -91,   -91,   -91,   -91,    25,
     -91,   -91,    87,    88,    -5,    91,   -91,   -91,    90,   -91,
      92,   -91,   -91,   -91,   106,   -91,   126,    98,   109,    48,
     -91,    43,   108,    29,   -91,   -91,    43,   -16,   -16,   -91,
      43,   107,   110,   111,   143,    43,    43,    30,   -91,   -91,
      30,    43,   -91,    52,   116,   -91,   117,   120,   121,   -91,
     -91,   -91,   -91,    56,   -91,   -91,   133,   -91,   -91,   -91,
     -91,   -16,   112,   -16,   122,   -91
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,   -91,
      40,   -91,     3,   -79,   -91,    86,   -91,    -3,   -91,   -91,
      79,    31,   -90,   -91,    -6,   -91,   -27
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      31,   118,    50,    34,   121,    39,    96,    36,    54,    32,
     107,    57,    21,   119,    22,    67,    68,    44,    45,    46,
      47,    48,    49,    33,    75,    97,    52,    53,   143,    82,
      23,    81,    24,   111,   112,    66,    55,   108,    30,    26,
     113,    27,    95,    40,   113,   102,   103,    83,    78,    30,
      80,     2,    79,    82,    25,    41,   110,    82,     3,     4,
       5,     6,    29,    28,   100,   101,     7,   172,   104,     8,
      30,   146,     9,    84,    10,   161,    11,   114,   115,   116,
      30,   114,   115,   116,   124,    42,   125,    66,   117,    85,
      86,    87,    88,    89,    90,   157,    38,   158,    12,   108,
      43,   175,   144,   157,    30,   180,    12,   141,   142,    51,
      56,    58,    69,    76,   159,    70,    71,    72,   100,   162,
      73,    74,    92,   165,    93,    94,   105,   122,   170,   171,
     123,   137,   138,   145,   174,   147,   148,   150,   151,   154,
     152,    78,   164,   126,   155,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   153,   156,   160,   169,   166,   181,
     183,   167,   168,   173,   149,   176,   177,     0,   109,   178,
     179,   185,   120,     0,     0,   182,     0,   184,   163
};

static const yytype_int16 yycheck[] =
{
       6,    91,    29,     9,    94,    11,    11,    10,    19,    16,
      20,    38,     4,    92,     6,    42,    43,    23,    24,    25,
      26,    27,    28,    19,    51,    30,    32,    33,   107,    28,
       3,    58,     5,    13,    14,    41,    47,    47,    54,     3,
      14,     5,    69,    20,    14,    72,    73,    46,    54,    54,
      56,     0,    55,    28,    27,    22,    83,    28,     7,     8,
       9,    10,    46,    27,    70,    71,    15,   157,    74,    18,
      54,    46,    21,    24,    23,    46,    25,    51,    52,    53,
      54,    51,    52,    53,    47,    46,    49,    93,    91,    40,
      41,    42,    43,    44,    45,    47,    46,    49,    55,    47,
      46,    49,   108,    47,    54,    49,    55,    46,    47,    46,
      50,    46,    46,    17,   141,    48,    48,    46,   124,   146,
      46,    48,    20,   150,    47,    40,    48,    12,   155,   156,
      12,    49,    49,    14,   161,    48,    48,    46,    48,    13,
      48,   147,   148,    29,    46,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    48,    46,    48,    14,    51,    26,
      48,    51,    51,   160,   124,    49,    49,    -1,    82,    49,
      49,    49,    93,    -1,    -1,   181,    -1,   183,   147
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    57,     0,     7,     8,     9,    10,    15,    18,    21,
      23,    25,    55,    58,    59,    60,    61,    62,    63,    64,
      82,     4,     6,     3,     5,    27,     3,     5,    27,    46,
      54,    80,    16,    19,    80,    72,    73,    80,    46,    80,
      20,    22,    46,    46,    80,    80,    80,    80,    80,    80,
      82,    46,    80,    80,    19,    47,    50,    82,    46,    69,
      70,    71,    73,    74,    75,    76,    80,    82,    82,    46,
      48,    48,    46,    46,    48,    82,    17,    77,    80,    73,
      80,    82,    28,    46,    24,    40,    41,    42,    43,    44,
      45,    81,    20,    47,    40,    82,    11,    30,    65,    66,
      80,    80,    82,    82,    80,    48,    67,    20,    47,    71,
      82,    13,    14,    14,    51,    52,    53,    73,    78,    69,
      76,    78,    12,    12,    47,    49,    29,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    79,    49,    49,    68,
      78,    46,    47,    69,    80,    14,    46,    48,    48,    66,
      46,    48,    48,    48,    13,    46,    46,    47,    49,    82,
      48,    46,    82,    77,    80,    82,    51,    51,    51,    14,
      82,    82,    78,    68,    82,    49,    49,    49,    49,    49,
      49,    26,    80,    48,    80,    49
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
#line 115 "SQLParser.y"
    {
            setCmdColor(1);
            std::cout << ">>>";
        ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 121 "SQLParser.y"
    {
            setCmdColor(1);
            if (cur.firstRoundFlag) {
                std::cout << ">>>";
            }
        ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 131 "SQLParser.y"
    {
        ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 135 "SQLParser.y"
    {
        ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 139 "SQLParser.y"
    {
        ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 143 "SQLParser.y"
    {
        ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 147 "SQLParser.y"
    {
        ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 153 "SQLParser.y"
    {
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
            //遍历所有文件夹
            struct _finddata_t fb;
            int handle = _findfirst("*", &fb);
            std::vector < std::string > dbList;
            if (handle != -1) {
                do {
                    int noFile = strcmp(fb.name, "..");
                    if (0 != noFile && fb.attrib == 16) {
                        std::string name = fb.name;
                        if (name != "." && name != "..") {
                            //找到一个文件夹，就是找到一个数据库
                            dbList.push_back(fb.name);
                        }
                    }
                } while (_findnext(handle, &fb) == 0);
                _findclose(handle);
            }
            std::cout << "当前目录下共有" << dbList.size() << "个数据库:" << std::endl;
            for (int i = 0; i < (int) dbList.size(); i ++) {
                std::cout << dbList[i] << (i < (int) dbList.size() - 1 ? ", " : ".");
            }
            std::cout << std::endl;
        ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 188 "SQLParser.y"
    {
            //新建一个数据库
            std::string * dbName = (yyvsp[(3) - (5)].v_s);
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
            //如果已有这个数据库，报错
            if (access(dbName -> c_str(), W_OK) == 0) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "已有数据库:" << * dbName << std::endl;
            } else {
                //新建这个数据库，并打开
                mkdir(dbName -> c_str());
                chdir(dbName -> c_str());
                cur.database = new TableManager(cur.bufPageManager, * dbName);
            }
        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 211 "SQLParser.y"
    {
            //删除一个数据库
            std::string * dbName = (yyvsp[(3) - (5)].v_s);
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
            //如果不存在这个数据库，报错
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "不存在数据库:" << * dbName << std::endl;
            } else {
                //删除这个数据库
                int rmrs = removeDir(dbName -> c_str());
                if (rmrs == -1) {
                    std::cout << "删不掉这个数据库" << std::endl;
                }
            }
        ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 235 "SQLParser.y"
    {
            //打开一个数据库
            std::string * dbName = (yyvsp[(2) - (4)].v_s);
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
            //如果不存在这个数据库，报错
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.USE: error" << std::endl;
                std::cout << "不存在数据库:" << * dbName << std::endl;
            } else {
                //打开这个数据库
                chdir(dbName -> c_str());
                cur.database = new TableManager(cur.bufPageManager, * dbName);
            }
        ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 257 "SQLParser.y"
    {
            //关闭已经打开的数据库
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
                cur.table = NULL;
            }
        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 268 "SQLParser.y"
    {
            //查看这个数据库的所有数据表
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.SHOW TABLES: error" << std::endl;
                std::cout << "没有正在使用的数据库" << std::endl;
            } else {
                //打印数据库中的数据表
                int nTab = cur.database -> getNTable();
                std::cout << "数据库" << cur.database -> getName() << "共有" << nTab << "个数据表:" << std::endl;
                for (int i = 0; i < nTab; i ++) {
                    std::cout << cur.database -> getTableById(i) -> getName() << ( i < nTab - 1 ? ", " : ".");
                }
                std::cout << std::endl;
            }
        ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 288 "SQLParser.y"
    {
            //在已经打开的数据库中创建一个数据表
            std::string * tbName = (yyvsp[(3) - (8)].v_s);
            UnionFieldList * fieldList = (yyvsp[(5) - (8)].u_fl);
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "没有已经打开的数据库:" << * tbName << std::endl;
            } else if (cur.database -> hasOpenedTable(* tbName)) {
                //如果已有同名数据表，报错
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "已有这个数据表:" << * tbName << std::endl;
            } else {
                //整理fieldList，获取到所有被设为PRIMARY KEY的列名
                StringList pkList;
                for (int i = 0; i < (int) fieldList -> size(); i ++) {
                    if (fieldList -> at(i) -> ty == 2) {
                        StringList * pkListI = fieldList -> at(i) -> dt.pk;
                        for (int j = 0; j < (int) pkListI -> size(); j ++) {
                            pkList.push_back(pkListI -> at(j));
                        }
                    }
                }
                //整理fieldList，把第一个可以被设为PRIMARY KEY的列设置一下，剩下的就无视掉
                for (int i = 0; i < (int) pkList.size(); i ++) {
                    int j;
                    for (j = 0; j < (int) fieldList -> size(); j ++) {
                        if ((yyvsp[(5) - (8)].u_fl) -> at(j) -> ty == 1) {
                            if ((yyvsp[(5) - (8)].u_fl) -> at(j) -> dt.tc -> getName() == * pkList[i]) {
                                (yyvsp[(5) - (8)].u_fl) -> at(j) -> dt.tc -> setPrimaryKey(true);
                                break;
                            }
                        }
                    }
                    if (j < (int) fieldList -> size()) {
                        break;
                    }
                }
                //创建数据表
                TableHeader * tbHd = new TableHeader();
                tbHd -> setName(* tbName);
                for (int i = 0; i < (int) fieldList -> size(); i ++) {
                    UnionField * fd = fieldList -> at(i);
                    if (fd -> ty == 1) {
                        fd -> dt.tc -> setConstant();
                        tbHd -> addColumn(fd -> dt.tc);
                    }
                }
                tbHd -> setConstant();
                cur.database -> createTable(tbHd);
                cur.table = cur.database -> getTableByName(* tbName);
            }
        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 343 "SQLParser.y"
    {
            //在已经打开的数据库中删除一个数据表
            std::string * tbName = (yyvsp[(3) - (5)].v_s);
            std::cout << "DropTable flag 1" << std::endl;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                if (cur.table != NULL && cur.table -> getName() == * tbName) {
                    cur.table = NULL;
                }
                //删除数据表
                std::cout << "DropTable flag 2" << std::endl;
                cur.database -> eraseTable(* tbName);
                std::cout << "DropTable flag 3" << std::endl;
                //从文件夹中删除
                std::string fileName = * tbName + ".table";
                remove(fileName.c_str());
            }
        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 370 "SQLParser.y"
    {
            //打印数据表中的所有列
            std::string * tbName = (yyvsp[(2) - (4)].v_s);
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                //打印数据表的列
                Table * table = cur.database -> getTableByName(* tbName);
                cur.table = table;
                int nCol = table -> getNCol();
                std::cout << "数据表" << * tbName << "共有" << nCol << "个数据列:" << std::endl;
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
                    if (tbCol -> isPrimaryKey()) {
                        std::cout << " PRIMARY KEY";
                    }
                    std::cout << (i < nCol - 1 ? ", " : ".");
                }
                std::cout << std::endl;
            }
        ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 408 "SQLParser.y"
    {
            //打印活跃的数据表中的所有列
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (cur.table == NULL) {
                //如果没有活跃的数据表，报错
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "没有活跃的数据表" << std::endl;
            } else {
                //打印数据表的列
                Table * table = cur.table;
                int nCol = table -> getNCol();
                std::cout << "数据表" << cur.table -> getName() << "共有" << nCol << "个数据列:" << std::endl;
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
                    if (tbCol -> isPrimaryKey()) {
                        std::cout << " PRIMARY KEY";
                    }
                    std::cout << (i < nCol - 1 ? ", " : ".");
                }
                std::cout << std::endl;
            }
        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 444 "SQLParser.y"
    {
            //在数据表中插入若干行
            std::string * tbName = (yyvsp[(3) - (7)].v_s);
            UnionValueLists * rowList = (yyvsp[(5) - (7)].u_vt);
            std::cout << "INSERT flag 1 " << std::endl;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                Table * table = cur.database -> getTableByName(* tbName);
                cur.table = table;
                //把数据一行一行的插入到表中
                int insertCnt = 0;
                for (int i = 0; i < (int) rowList -> size(); i ++) {
                    //创建数据库中的数据行
                    std::cout << "INSERT flag 2 " << std::endl;
                    UnionValueList * sqlRow = rowList -> at(i);
                    std::string errMsg;
                    TableRow * tableRow = genTableRow(sqlRow, table, errMsg);
                    if (tableRow == NULL) {
                        std::cout << "Parser.INSERT INTO: error" << std::endl;
                        std::cout << "输入的第" << i << "个数据行不符合数据表" << table -> getName() << "的格式要求" << std::endl;
                        std::cout << errMsg << std::endl;
                        continue;
                    }
                    std::cout << "INSERT flag 3 " << std::endl;
                    table -> insertRow(tableRow);
                    insertCnt += 1;
                }
                std::cout << "共添加" << insertCnt << "个数据行" << std::endl;
            }
        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 483 "SQLParser.y"
    {
            //删除一些数据行
            //把数据表放到vector里面，可以调用SELECT操作的检查函数
            std::string * tbName = (yyvsp[(1) - (5)].v_s);
            StringList * tbNameList = new StringList();
            tbNameList -> push_back(tbName);
            UnionWhereClause * whList = (yyvsp[(3) - (5)].u_wc);
            std::string errMsg;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := DELETEE FROM ident WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!checkTableNameList(tbNameList, whList, errMsg)) {
                //检查whList和tbNameList的数据表是同一个集合
                std::cout << "Parser.<tbStmt := DELETEE FROM ident WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else {
                cur.table = cur.database -> getTableByName(* tbName);
                runDelete(tbName, whList);
            }
        ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 506 "SQLParser.y"
    {
            //更新一些数据行
            //把数据表放到vector里面，可以调用SELECT操作的检查函数
            std::string * tbName = (yyvsp[(1) - (7)].v_s);
            StringList * tbNameList = new StringList();
            tbNameList -> push_back(tbName);
            UnionSetClause * scList = (yyvsp[(3) - (7)].u_sc);
            UnionWhereClause * whList = (yyvsp[(5) - (7)].u_wc);
            std::string errMsg;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := UPDATE ident SET setClause WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!checkTableNameList(tbNameList, whList, errMsg)) {
                //检查whList和tbNameList的数据表是同一个集合
                std::cout << "Parser.<tbStmt := UPDATE ident SET setClause WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else if (!checkSetClause(tbName, scList, errMsg)) {
                //检查setClause的数据列都是这个表中数据列，以及数据类型的兼容性
                std::cout << "Parser.<tbStmt := UPDATE ident SET setClause WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else {
                cur.table = cur.database -> getTableByName(* tbName);
                runUpdate(tbName, scList, whList);
            }
        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 534 "SQLParser.y"
    {
            //在数据表中查询
            UnionColList * sColList = (yyvsp[(2) - (8)].u_cl);
            StringList * tbNameList = (yyvsp[(4) - (8)].v_sl);
            UnionWhereClause * whList = (yyvsp[(6) - (8)].u_wc);
            std::string errMsg;
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!checkTableNameList(tbNameList, whList, errMsg)) {
                //检查whList和tbNameList的数据表是同一个集合
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else if (!checkSelector(sColList, tbNameList,errMsg)){
                //检查sColList的数据表是tbNameList的子集
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << errMsg << std::endl;
            } else {
                runSelect(sColList, tbNameList, whList);
            }
        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 560 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(3) - (3)].v_s);
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else {
                cur.table = cur.database -> getTableByName(* (yyvsp[(3) - (3)].v_s));
            }
        ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 574 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(2) - (2)].v_s);
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<tbStmt := SELECT selector FROM identList WHERE whereClause ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else {
                cur.table = cur.database -> getTableByName(* (yyvsp[(2) - (2)].v_s));
            }
        ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 588 "SQLParser.y"
    {
            //给某列添加索引
            std::string * tbName = (yyvsp[(3) - (8)].v_s);
            std::string * colName = (yyvsp[(5) - (8)].v_s);
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<idxStmt := CREATE INDEX ident '(' ident ')' ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.<idxStmt := CREATE INDEX ident '(' ident ')' ';' endLine>: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                runCreateIndex(tbName, colName);
            }
        ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 606 "SQLParser.y"
    {
            //删除某列的索引
            std::string * tbName = (yyvsp[(3) - (8)].v_s);
            std::string * colName = (yyvsp[(5) - (8)].v_s);
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<idxStmt := DROP INDEX ident '(' ident ')' ';' endLine>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.<idxStmt := DROP INDEX ident '(' ident ')' ';' endLine>: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else {
                runRemoveIndex(tbName, colName);
            }
        ;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 626 "SQLParser.y"
    {
            (yyval.u_fl) = new UnionFieldList();
            (yyval.u_fl) -> push_back((yyvsp[(1) - (1)].u_fd));
        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 632 "SQLParser.y"
    {
            (yyval.u_fl) = (yyvsp[(1) - (3)].u_fl);
            (yyval.u_fl) -> push_back((yyvsp[(3) - (3)].u_fd));
        ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 640 "SQLParser.y"
    {
            std::string * colName = (yyvsp[(1) - (2)].v_s);
            
            (yyval.u_fd) = new UnionField();
            (yyval.u_fd) -> ty = 1;
            (yyval.u_fd) -> dt.tc = new TableColumn();
            (yyval.u_fd) -> dt.tc -> setName(* colName);
            (yyval.u_fd) -> dt.tc -> setType((yyvsp[(2) - (2)].v_t));
            (yyval.u_fd) -> dt.tc -> setAllowNull(true);
        ;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 652 "SQLParser.y"
    {
            std::string * colName = (yyvsp[(1) - (4)].v_s);
            
            (yyval.u_fd) = new UnionField();
            (yyval.u_fd) -> ty = 1;
            (yyval.u_fd) -> dt.tc = new TableColumn();
            (yyval.u_fd) -> dt.tc -> setName(* colName);
            (yyval.u_fd) -> dt.tc -> setType((yyvsp[(2) - (4)].v_t));
        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 663 "SQLParser.y"
    {
            StringList * colList = (yyvsp[(4) - (5)].v_sl);
            (yyval.u_fd) = new UnionField();
            (yyval.u_fd) -> ty = 2;
            (yyval.u_fd) -> dt.pk = colList;
        ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 671 "SQLParser.y"
    {
            //去一个已有数据表中把一个数据列的属性复制过来
            std::string * colName = (yyvsp[(4) - (10)].v_s);
            std::string * tbName = (yyvsp[(7) - (10)].v_s);
            std::string * colName0 = (yyvsp[(9) - (10)].v_s);
            (yyval.u_fd) = new UnionField();
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<field := FOREIGN KEY '(' ident ')' REFERENCES ident '(' ident ')'>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.<field := FOREIGN KEY '(' ident ')' REFERENCES ident '(' ident ')'>: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
            } else if (!cur.database -> getTableByName(* tbName) -> getTableHeader() -> hasColumn(* colName0)) { 
                //如果没有这个数据列，报错
                std::cout << "Parser.<field := FOREIGN KEY '(' ident ')' REFERENCES ident '(' ident ')'>: error" << std::endl;
                std::cout << "数据表" << * (yyvsp[(7) - (10)].v_s) << "中没有数据列:" << * colName0 << std::endl;
            } else {
                TableColumn * tc = cur.database -> getTableByName(* tbName) -> getTableHeader() -> getColumnByName(* colName0);
                (yyval.u_fd) -> ty = 1;
                (yyval.u_fd) -> dt.tc = new TableColumn();
                (yyval.u_fd) -> dt.tc -> setName(* colName);
                (yyval.u_fd) -> dt.tc -> setType(tc -> getDataType());
                (yyval.u_fd) -> dt.tc -> setUnique(tc -> isUnique());
                (yyval.u_fd) -> dt.tc -> setAllowNull(tc -> allowNull());
                (yyval.u_fd) -> dt.tc -> setPrimaryKey(tc -> hasDefault());
                (yyval.u_fd) -> dt.tc -> setHasTreeIndex(tc -> hasTreeIndex());
                (yyval.u_fd) -> dt.tc -> setHasHashIndex(tc -> hasHashIndex());
            }
        ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 706 "SQLParser.y"
    {
            (yyval.u_vt) = new UnionValueLists();
            (yyval.u_vt) -> push_back((yyvsp[(2) - (3)].u_vr));
        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 712 "SQLParser.y"
    {
            (yyval.u_vt) = (yyvsp[(1) - (5)].u_vt);
            (yyval.u_vt) -> push_back((yyvsp[(4) - (5)].u_vr));
        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 720 "SQLParser.y"
    {
            (yyval.u_vr) = new UnionValueList();
            (yyval.u_vr) -> push_back((yyvsp[(1) - (1)].u_va));
        ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 726 "SQLParser.y"
    {
            (yyval.u_vr) = (yyvsp[(1) - (3)].u_vr);
            (yyval.u_vr) -> push_back((yyvsp[(3) - (3)].u_va));
        ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 734 "SQLParser.y"
    {
            (yyval.u_wc) = (yyvsp[(1) - (1)].u_wc)
        ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 739 "SQLParser.y"
    {
            (yyval.u_wc) = new UnionWhereClause();
        ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 746 "SQLParser.y"
    {
            (yyval.u_wc) = new UnionWhereClause();
            if ((yyvsp[(1) - (1)].u_wi) != NULL) {
                (yyval.u_wc) -> push_back((yyvsp[(1) - (1)].u_wi));
            }
        ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 754 "SQLParser.y"
    {
            (yyval.u_wc) = (yyvsp[(1) - (3)].u_wc);
            if ((yyvsp[(3) - (3)].u_wi) != NULL) {
                (yyval.u_wc) -> push_back((yyvsp[(3) - (3)].u_wi));
            }
        ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 764 "SQLParser.y"
    {
            if ((yyvsp[(1) - (3)].u_co) != NULL) {
                (yyval.u_wi) = new UnionWhereItem();
                (yyval.u_wi) -> op = (UnionWhereItem::OpTag) (yyvsp[(2) - (3)].v_u);
                (yyval.u_wi) -> left = (yyvsp[(1) - (3)].u_co);
                (yyval.u_wi) -> ty = 1;
                (yyval.u_wi) -> right.uv = (yyvsp[(3) - (3)].u_va);
            } else {
                (yyval.u_wi) = NULL;
            }
        ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 777 "SQLParser.y"
    {
            if ((yyvsp[(1) - (3)].u_co) != NULL && (yyvsp[(3) - (3)].u_co) != NULL) {
                (yyval.u_wi) = new UnionWhereItem();
                (yyval.u_wi) -> op = (UnionWhereItem::OpTag) (yyvsp[(2) - (3)].v_u);
                (yyval.u_wi) -> left = (yyvsp[(1) - (3)].u_co);
                (yyval.u_wi) -> ty = 2;
                (yyval.u_wi) -> right.uc = (yyvsp[(3) - (3)].u_co);
            } else {
                (yyval.u_wi) = NULL;
            }
        ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 790 "SQLParser.y"
    {
            if ((yyvsp[(1) - (3)].u_co) != NULL) {
                (yyval.u_wi) = new UnionWhereItem();
                (yyval.u_wi) -> op = UnionWhereItem::OpTag::OP_EQ;
                (yyval.u_wi) -> left = (yyvsp[(1) - (3)].u_co);
                (yyval.u_wi) -> ty = 0;
            } else {
                (yyval.u_wi) = NULL;
            }
        ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 802 "SQLParser.y"
    {
            if ((yyvsp[(1) - (4)].u_co) != NULL) {
                (yyval.u_wi) = new UnionWhereItem();
                (yyval.u_wi) -> op = UnionWhereItem::OpTag::OP_NE;
                (yyval.u_wi) -> left = (yyvsp[(1) - (4)].u_co);
                (yyval.u_wi) -> ty = 0;
            } else {
                (yyval.u_wi) = NULL;
            }
        ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 816 "SQLParser.y"
    {
            (yyval.u_cl) = new UnionColList();
            if ((yyvsp[(1) - (1)].u_co) != NULL) {
                (yyval.u_cl) -> push_back((yyvsp[(1) - (1)].u_co));
            }
        ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 824 "SQLParser.y"
    {
            (yyval.u_cl) = (yyvsp[(1) - (3)].u_cl);
            if ((yyvsp[(3) - (3)].u_co) != NULL) {
                (yyval.u_cl) -> push_back((yyvsp[(3) - (3)].u_co));
            }
        ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 834 "SQLParser.y"
    {
            //从活跃的数据表中得到数据列
            std::string * colName = (yyvsp[(1) - (1)].v_s);
            //没有活跃的数据表，报错
            if (cur.table == NULL) {
                std::cout << "Parser.<col := ident>: error" << std::endl;
                std::cout << "没有活跃的数据表" << std::endl;
                (yyval.u_co) = NULL;
            } else if (!cur.table -> getTableHeader() -> hasColumn(* colName)) {
                //活跃的数据表没有这个列，报错
                std::cout << "Parser.<col := ident>: error" << std::endl;
                std::cout << "活跃的数据表" << cur.table -> getName() << "中没有数据列" << * colName << std::endl;
                (yyval.u_co) = NULL;
            } else {
                (yyval.u_co) = new UnionCol();
                (yyval.u_co) -> tb = new std::string(cur.table -> getName());
                (yyval.u_co) -> col = colName;
                (yyval.u_co) -> tc = cur.table -> getTableHeader() -> getColumnByName(* colName);
            }
        ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 856 "SQLParser.y"
    {
            //从当前数据库中得到数据列
            std::string * tbName = (yyvsp[(1) - (3)].v_s);
            std::string * colName = (yyvsp[(3) - (3)].v_s);
            //如果没有打开数据库，报错
            if (cur.database == NULL) {
                std::cout << "Parser.<col := ident '.' ident>: error" << std::endl;
                std::cout << "没有已经打开的数据库" << std::endl;
                (yyval.u_co) = NULL;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //如果没有这个数据表，报错
                std::cout << "Parser.<col := ident '.' ident>: error" << std::endl;
                std::cout << "没有数据表:" << * tbName << std::endl;
                (yyval.u_co) = NULL;
            } else {
                Table * table = cur.database -> getTableByName(* tbName);
                if (!table -> getTableHeader() -> hasColumn(* colName)) {
                    //这个数据表没有这个列，报错
                    std::cout << "Parser.<col := ident '.' ident>: error" << std::endl;
                    std::cout << "数据表" << table -> getName() << "中没有数据列" << * colName << std::endl;
                    (yyval.u_co) = NULL;
                } else {
                    (yyval.u_co) = new UnionCol();
                    (yyval.u_co) -> tb = tbName; 
                    (yyval.u_co) -> col = colName;
                    (yyval.u_co) -> tc  = table -> getTableHeader() -> getColumnByName(* colName);
                }
            }
        ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 889 "SQLParser.y"
    {
            (yyval.u_sc) = (yyvsp[(1) - (1)].u_sc);
        ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 894 "SQLParser.y"
    {
            (yyval.u_sc) = new UnionSetClause();
        ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 902 "SQLParser.y"
    {
            (yyval.u_sc) = new UnionSetClause();
            (yyval.u_sc) -> push_back((yyvsp[(1) - (1)].u_si));
        ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 908 "SQLParser.y"
    {
            (yyval.u_sc) = (yyvsp[(1) - (3)].u_sc);
            (yyval.u_sc) -> push_back((yyvsp[(3) - (3)].u_si));
        ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 916 "SQLParser.y"
    {
            (yyval.u_si) = new UnionSetItem();
            (yyval.u_si) -> col = (yyvsp[(1) - (3)].v_s);
            (yyval.u_si) -> uv = (yyvsp[(3) - (3)].u_va); 
        ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 925 "SQLParser.y"
    {
            (yyval.v_sl) = new StringList();
            (yyval.v_sl) -> push_back((yyvsp[(1) - (1)].v_s));
        ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 931 "SQLParser.y"
    {
            (yyval.v_sl) = (yyvsp[(1) - (3)].v_sl);
            (yyval.v_sl) -> push_back((yyvsp[(3) - (3)].v_s));
        ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 939 "SQLParser.y"
    {
            (yyval.u_va) = new UnionValue();
        ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 944 "SQLParser.y"
    {
            (yyval.u_va) = new UnionValue();
            (yyval.u_va) -> ty = 1;
            (yyval.u_va) -> dt.u = (yyvsp[(1) - (1)].v_u);
        ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 951 "SQLParser.y"
    {
            (yyval.u_va) = new UnionValue();
            (yyval.u_va) -> ty = 2;
            (yyval.u_va) -> dt.d = (yyvsp[(1) - (1)].v_d);
        ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 958 "SQLParser.y"
    {
            (yyval.u_va) = new UnionValue();
            (yyval.u_va) -> ty = 3;
            (yyval.u_va) -> dt.s = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 967 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_bool;
        ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 972 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_char;
        ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 977 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_short;
        ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 982 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_int;
        ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 987 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_long;
        ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 992 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_float;
        ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 997 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_double;
        ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 1002 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_string;
        ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 1007 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_int;
        ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 1012 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_lob;
        ;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 1017 "SQLParser.y"
    {
            if (1 <= (yyvsp[(3) - (4)].v_u) && (yyvsp[(3) - (4)].v_u) <= 4) {
                (yyval.v_t) = TableDataType::t_short;
            } else if (5 <= (yyvsp[(3) - (4)].v_u) && (yyvsp[(3) - (4)].v_u) <= 9) {
                (yyval.v_t) = TableDataType::t_int;
            } else if (10 <= (yyvsp[(3) - (4)].v_u) && (yyvsp[(3) - (4)].v_u) <= 19) {
                (yyval.v_t) = TableDataType::t_long;
            } else {
                yyerror("INT类型长度出错");
            }
        ;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 1030 "SQLParser.y"
    {
            if (1 <= (yyvsp[(3) - (4)].v_u) && (yyvsp[(3) - (4)].v_u) < MAX_STRING_LENGTH) {
                (yyval.v_t) = TableDataType::t_string;
            } else {
                yyerror("VARCHAR类型长度出错");
            }
        ;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 1039 "SQLParser.y"
    {
            if (1 <= (yyvsp[(3) - (4)].v_u) && (yyvsp[(3) - (4)].v_u) < MAX_STRING_LENGTH) {
                (yyval.v_t) = TableDataType::t_string;
            } else {
                yyerror("CHAR类型长度出错");
            }
        ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 1050 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 1057 "SQLParser.y"
    {
            (yyval.v_u) = UnionWhereItem::OpTag::OP_EQ;
        ;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 1062 "SQLParser.y"
    {
            (yyval.v_u) = UnionWhereItem::OpTag::OP_NE;
        ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 1067 "SQLParser.y"
    {
            (yyval.v_u) = UnionWhereItem::OpTag::OP_LT;
        ;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 1072 "SQLParser.y"
    {
            (yyval.v_u) = UnionWhereItem::OpTag::OP_GT;
        ;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 1077 "SQLParser.y"
    {
            (yyval.v_u) = UnionWhereItem::OpTag::OP_LE;
        ;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 1082 "SQLParser.y"
    {
            (yyval.v_u) = UnionWhereItem::OpTag::OP_GE;
        ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 1089 "SQLParser.y"
    {
            setCmdColor(0);
        ;}
    break;



/* Line 1455 of yacc.c  */
#line 2802 "SQLParser.cpp"
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
#line 1094 "SQLParser.y"


int yyerror(const char * emseg) {
    std::cout << "Parser: Unknown sentence! please try again! " << emseg << std::endl;
    return -1;
}

int main() {
    MyBitMap::initConst();
    FileManager * fileManager = new FileManager();
    cur.bufPageManager = new BufPageManager(fileManager);
    cur.database = NULL;    
    cmdColorHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    //myMain(yyparse);
    while (true) {
        yyparse();
        cur.firstRoundFlag = false;
    }
}

