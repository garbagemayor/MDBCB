
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
     VALUE_UINT64 = 295,
     VALUE_STRING = 296,
     VALUE_DOUBLE = 297,
     IDENTIFIER = 298
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 64 "SQLParser.y"

    
    UnionFieldList * u_fl;
    UnionField * u_fd;
    StringList * v_sl;
    
    UnionValue * u_va;
    UnionValueRow * u_vr;
    UnionValueTable * u_vt;
    
    uint64 v_u;
    double v_d;
    std::string * v_s;
    
    TableDataType v_t;



/* Line 214 of yacc.c  */
#line 180 "SQLParser.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 192 "SQLParser.cpp"

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
#define YYLAST   163

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNRULES -- Number of states.  */
#define YYNSTATES  172

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      52,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      42,    43,     2,     2,    41,     2,    44,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      46,    45,    47,     2,     2,     2,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    48,    49,    50,    51
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    11,    13,    15,    17,
      22,    28,    34,    39,    43,    48,    57,    63,    68,    76,
      85,    94,   103,   112,   121,   123,   127,   130,   135,   141,
     152,   154,   156,   158,   160,   162,   164,   166,   168,   170,
     172,   176,   182,   184,   188,   190,   192,   194,   196,   200,
     202,   206,   210,   215,   217,   221,   223,   226,   229,   232,
     234,   236,   238,   240,   244,   250,   252,   254,   258,   260
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      54,     0,    -1,    54,    55,    -1,    -1,    56,    -1,    57,
      -1,    58,    -1,    59,    -1,    75,    -1,     7,     4,    40,
      75,    -1,     8,     3,    74,    40,    75,    -1,     9,     3,
      74,    40,    75,    -1,    10,    74,    40,    75,    -1,    10,
      40,    75,    -1,     7,     6,    40,    75,    -1,     8,     5,
      74,    42,    60,    43,    40,    75,    -1,     9,     5,    74,
      40,    75,    -1,    25,    74,    40,    75,    -1,    15,    16,
      74,    17,    63,    40,    75,    -1,    18,    19,    74,    74,
      20,    66,    40,    75,    -1,    21,    74,    22,    71,    20,
      66,    40,    75,    -1,    23,    72,    19,    73,    20,    66,
      40,    75,    -1,     8,    27,    74,    42,    74,    43,    40,
      75,    -1,     9,    27,    74,    42,    74,    43,    40,    75,
      -1,    61,    -1,    60,    41,    61,    -1,    74,    62,    -1,
      74,    62,    13,    14,    -1,    11,    12,    42,    73,    43,
      -1,    30,    12,    42,    74,    43,    26,    74,    42,    74,
      43,    -1,    31,    -1,    32,    -1,    33,    -1,    34,    -1,
      35,    -1,    36,    -1,    37,    -1,    38,    -1,    29,    -1,
      39,    -1,    42,    64,    43,    -1,    63,    41,    42,    64,
      43,    -1,    65,    -1,    64,    41,    65,    -1,    14,    -1,
      48,    -1,    50,    -1,    49,    -1,    66,    28,    67,    -1,
      67,    -1,    68,    69,    70,    -1,    68,    24,    14,    -1,
      68,    24,    13,    14,    -1,    74,    -1,    74,    44,    74,
      -1,    45,    -1,    46,    47,    -1,    46,    45,    -1,    47,
      45,    -1,    46,    -1,    47,    -1,    65,    -1,    68,    -1,
      74,    45,    65,    -1,    71,    41,    74,    45,    65,    -1,
      68,    -1,    74,    -1,    73,    41,    74,    -1,    51,    -1,
      52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    84,    84,    91,    98,   102,   106,   110,   114,   120,
     148,   170,   193,   214,   224,   244,   298,   319,   356,   391,
     396,   401,   407,   411,   417,   423,   431,   443,   454,   462,
     497,   502,   507,   512,   517,   522,   527,   532,   537,   542,
     549,   555,   563,   569,   577,   582,   589,   596,   605,   609,
     615,   619,   623,   629,   633,   639,   643,   647,   651,   655,
     659,   665,   669,   675,   679,   685,   691,   697,   705,   712
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
  "FLOATT", "DOUBLEE", "VARCHAR", "LOB", "';'", "','", "'('", "')'", "'.'",
  "'='", "'<'", "'>'", "VALUE_UINT64", "VALUE_STRING", "VALUE_DOUBLE",
  "IDENTIFIER", "'\\n'", "$accept", "program", "stmt", "sysStmt", "dbStmt",
  "tbStmt", "idxStmt", "fieldList", "field", "type", "valueLists",
  "valueList", "value", "whereClause", "filterItem", "col", "op", "expr",
  "setClause", "selector", "identList", "ident", "endLine", 0
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
      59,    44,    40,    41,    46,    61,    60,    62,   295,   296,
     297,   298,    10
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    54,    55,    55,    55,    55,    55,    56,
      57,    57,    57,    57,    57,    58,    58,    58,    58,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    61,    61,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      63,    63,    64,    64,    65,    65,    65,    65,    66,    66,
      67,    67,    67,    68,    68,    69,    69,    69,    69,    69,
      69,    70,    70,    71,    71,    72,    73,    73,    74,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     1,     1,     1,     1,     4,
       5,     5,     4,     3,     4,     8,     5,     4,     7,     8,
       8,     8,     8,     8,     1,     3,     2,     4,     5,    10,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     1,     3,     1,     1,     1,     1,     3,     1,
       3,     3,     4,     1,     3,     1,     2,     2,     2,     1,
       1,     1,     1,     3,     5,     1,     1,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    69,     2,     4,     5,     6,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,     0,
       0,     0,     0,    65,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    13,     0,     0,     0,     0,
       0,     0,     0,     9,    14,     0,     0,     0,     0,     0,
       0,    12,     0,     0,     0,     0,     0,    66,    54,    17,
      10,     0,     0,     0,    24,     0,     0,    11,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    30,    31,    32,    33,    34,    35,    36,
      37,    39,    26,     0,     0,    44,    45,    47,    46,     0,
      42,     0,     0,     0,    49,     0,     0,     0,    63,     0,
      67,     0,     0,    25,     0,     0,     0,     0,     0,    40,
      18,     0,     0,     0,     0,    55,    59,    60,     0,     0,
       0,     0,     0,     0,    15,    27,    22,    23,    43,     0,
      48,    19,     0,    51,    57,    56,    58,    61,    62,    50,
      20,    64,    21,    28,     0,    41,    52,     0,     0,     0,
       0,    29
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    13,    14,    15,    16,    17,    73,    74,   102,
      81,   109,   110,   113,   114,   115,   138,   159,    64,    34,
      66,    35,    18
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const yytype_int16 yypact[] =
{
     -76,    62,   -76,    82,     1,     6,    42,    19,    37,    13,
      13,    13,   -76,   -76,   -76,   -76,   -76,   -76,   -76,    49,
      50,    13,    13,    13,    13,    13,    13,    57,   -76,    72,
      13,    13,    81,   -76,    94,    74,    80,    57,    57,    83,
      79,    86,    85,    90,    89,   -76,    57,   105,    13,    13,
      13,    13,    57,   -76,   -76,    57,    -4,    13,    57,    57,
      13,   -76,    92,   112,   -18,    91,    -7,   -76,   -76,   -76,
     -76,   123,   125,   -29,   -76,    63,    95,   -76,   -76,    97,
      18,   -19,    13,    13,    13,    18,    13,    13,   100,   101,
      -4,   104,   -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   132,   106,   107,   -76,   -76,   -76,   -76,    64,
     -76,    57,   108,     8,   -76,   -16,    21,   103,   -76,    51,
     -76,    13,    13,   -76,    57,   135,    57,    57,    18,   -76,
     -76,    18,    13,    57,    27,   -76,    59,   109,    25,    57,
      18,    57,    67,   110,   -76,   -76,   -76,   -76,   -76,    76,
     -76,   -76,   137,   -76,   -76,   -76,   -76,   -76,   -76,   -76,
     -76,   -76,   -76,   -76,   126,   -76,   -76,    13,   113,    13,
     114,   -76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -76,   -76,   -76,   -76,   -76,   -76,   -76,   -76,    66,   -76,
     -76,    28,   -75,   -26,    26,    -9,   -76,   -76,   -76,   -76,
      39,    -6,     0
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      29,    33,    83,    32,    21,    36,    22,    71,   134,    24,
     118,    25,    90,    86,    91,    39,    40,    41,    42,    43,
      44,   111,   112,    84,    47,    48,    72,    45,    23,   135,
     136,   137,   105,    26,    87,    30,   132,    53,    54,   105,
     152,   153,    63,    65,    67,    68,    61,    28,   133,   132,
      75,    76,    69,   148,    79,    70,    31,   116,    77,    78,
     119,   139,     2,   157,    28,   161,   106,   107,   108,     3,
       4,     5,     6,   106,   107,   108,    28,     7,   117,   132,
       8,   120,    27,     9,    75,    10,    19,    11,    20,    37,
      38,   141,    92,    28,    93,    94,    95,    96,    97,    98,
      99,   100,   101,    49,   154,   128,   155,   129,    87,    12,
     163,   130,    46,    50,    12,    67,   143,   128,    51,   165,
      52,    56,    62,    55,   144,    58,   146,   147,    57,   158,
      59,    60,    82,   151,    80,    88,    85,    89,   103,   160,
     104,   162,   121,   122,   124,   125,   126,   127,   140,   145,
     131,   166,   167,   164,   156,   169,   123,   171,   150,   149,
     142,   168,     0,   170
};

static const yytype_int16 yycheck[] =
{
       6,    10,    20,     9,     3,    11,     5,    11,    24,     3,
      85,     5,    41,    20,    43,    21,    22,    23,    24,    25,
      26,    40,    41,    41,    30,    31,    30,    27,    27,    45,
      46,    47,    14,    27,    41,    16,    28,    37,    38,    14,
      13,    14,    48,    49,    50,    51,    46,    51,    40,    28,
      56,    57,    52,   128,    60,    55,    19,    83,    58,    59,
      86,    40,     0,   138,    51,   140,    48,    49,    50,     7,
       8,     9,    10,    48,    49,    50,    51,    15,    84,    28,
      18,    87,    40,    21,    90,    23,     4,    25,     6,    40,
      40,    40,    29,    51,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    22,    45,    41,    47,    43,    41,    52,
      43,   111,    40,    19,    52,   121,   122,    41,    44,    43,
      40,    42,    17,    40,   124,    40,   126,   127,    42,   138,
      40,    42,    20,   133,    42,    12,    45,    12,    43,   139,
      43,   141,    42,    42,    40,    13,    40,    40,    45,    14,
      42,    14,    26,    43,    45,    42,    90,    43,   132,   131,
     121,   167,    -1,   169
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    54,     0,     7,     8,     9,    10,    15,    18,    21,
      23,    25,    52,    55,    56,    57,    58,    59,    75,     4,
       6,     3,     5,    27,     3,     5,    27,    40,    51,    74,
      16,    19,    74,    68,    72,    74,    74,    40,    40,    74,
      74,    74,    74,    74,    74,    75,    40,    74,    74,    22,
      19,    44,    40,    75,    75,    40,    42,    42,    40,    40,
      42,    75,    17,    74,    71,    74,    73,    74,    74,    75,
      75,    11,    30,    60,    61,    74,    74,    75,    75,    74,
      42,    63,    20,    20,    41,    45,    20,    41,    12,    12,
      41,    43,    29,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    62,    43,    43,    14,    48,    49,    50,    64,
      65,    40,    41,    66,    67,    68,    66,    74,    65,    66,
      74,    42,    42,    61,    40,    13,    40,    40,    41,    43,
      75,    42,    28,    40,    24,    45,    46,    47,    69,    40,
      45,    40,    73,    74,    75,    14,    75,    75,    65,    64,
      67,    75,    13,    14,    45,    47,    45,    65,    68,    70,
      75,    65,    75,    43,    43,    43,    14,    26,    74,    42,
      74,    43
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
#line 85 "SQLParser.y"
    {
            setCmdColor(1);
            std::cout << ">>>";
        ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 91 "SQLParser.y"
    {
            setCmdColor(1);
            std::cout << ">>>";
        ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 99 "SQLParser.y"
    {
        ;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 103 "SQLParser.y"
    {
        ;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 107 "SQLParser.y"
    {
        ;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 111 "SQLParser.y"
    {
        ;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 115 "SQLParser.y"
    {
        ;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 121 "SQLParser.y"
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
        ;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 149 "SQLParser.y"
    {
            //�½�һ�����ݿ�
            std::string * dbName = (yyvsp[(3) - (5)].v_s);
            //�ر��Ѿ��򿪵����ݿ�
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
            }
            //�������������ݿ⣬����
            if (access(dbName -> c_str(), W_OK) == 0) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "�������ݿ�:" << * dbName << std::endl;
            } else {
                //�½�������ݿ⣬����
                mkdir(dbName -> c_str());
                chdir(dbName -> c_str());
                cur.database = new TableManager(cur.bufPageManager, * dbName);
            }
        ;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 171 "SQLParser.y"
    {
            //ɾ��һ�����ݿ�
            std::string * dbName = (yyvsp[(3) - (5)].v_s);
            //�ر��Ѿ��򿪵����ݿ�
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
            }
            //���������������ݿ⣬����
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.CREATE DATABASE: error" << std::endl;
                std::cout << "���������ݿ�:" << * dbName << std::endl;
            } else {
                //ɾ��������ݿ�
                int rmrs = removeDir(dbName -> c_str());
                if (rmrs == -1) {
                    std::cout << "ɾ����������ݿ�" << std::endl;
                }
            }
        ;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 194 "SQLParser.y"
    {
            //��һ�����ݿ�
            std::string * dbName = (yyvsp[(2) - (4)].v_s);
            //�ر��Ѿ��򿪵����ݿ�
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
            }
            //���������������ݿ⣬����
            if (access(dbName -> c_str(), W_OK) == -1) {
                std::cout << "Parser.USE: error" << std::endl;
                std::cout << "���������ݿ�:" << * dbName << std::endl;
            } else {
                //��������ݿ�
                chdir(dbName -> c_str());
                cur.database = new TableManager(cur.bufPageManager, * dbName);
            }
        ;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 215 "SQLParser.y"
    {
            //�ر��Ѿ��򿪵����ݿ�
            if (cur.database != NULL) {
                chdir("../");
                delete cur.database;
                cur.database = NULL;
            }
        ;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 225 "SQLParser.y"
    {
            //�鿴������ݿ���������ݱ�
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.SHOW TABLES: error" << std::endl;
                std::cout << "û������ʹ�õ����ݿ�" << std::endl;
            } else {
                //��ӡ���ݿ��е����ݱ�
                int nTab = cur.database -> getNTable();
                std::cout << "���ݿ�" << cur.database -> getName() << "����" << nTab << "�����ݱ�:" << std::endl;
                for (int i = 0; i < nTab; i ++) {
                    std::cout << cur.database -> getTableById(i) -> getName() << ( i < nTab - 1 ? ", " : ".");
                }
                std::cout << std::endl;
            }
        ;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 245 "SQLParser.y"
    {
            //���Ѿ��򿪵����ݿ��д���һ�����ݱ�
            std::string * tbName = (yyvsp[(3) - (8)].v_s);
            UnionFieldList * fieldList = (yyvsp[(5) - (8)].u_fl);
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�:" << * tbName << std::endl;
            } else if (cur.database -> hasOpenedTable(* tbName)) {
                //�������ͬ�����ݱ�����
                std::cout << "Parser.CREATE TABLE: error" << std::endl;
                std::cout << "����������ݱ�:" << * tbName << std::endl;
            } else {
                //����fieldList����ȡ�����б���ΪPRIMARY KEY������
                StringList pkList;
                for (int i = 0; i < (int) fieldList -> size(); i ++) {
                    if (fieldList -> at(i) -> ty == 2) {
                        StringList * pkListI = fieldList -> at(i) -> dt.pk;
                        for (int j = 0; j < (int) pkListI -> size(); j ++) {
                            pkList.push_back(pkListI -> at(j));
                        }
                    }
                }
                //����fieldList���ѵ�һ�����Ա���ΪPRIMARY KEY��������һ�£�ʣ�µľ����ӵ�
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
                //�������ݱ�
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
            }
        ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 299 "SQLParser.y"
    {
            //���Ѿ��򿪵����ݿ���ɾ��һ�����ݱ�
            std::string * tbName = (yyvsp[(3) - (5)].v_s);
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.DROP TABLE: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                //ɾ�����ݱ�
                cur.database -> eraseTable(* tbName);
                //���ļ�����ɾ��
                std::string fileName = * tbName + ".table";
                remove(fileName.c_str());
            }
        ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 320 "SQLParser.y"
    {
            //��ӡ���ݱ��е�������
            std::string * tbName = (yyvsp[(2) - (4)].v_s);
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.DESC: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                //��ӡ���ݱ����
                Table * table = cur.database -> getTableByName(* tbName);
                int nCol = table -> getNCol();
                std::cout << "���ݱ�" << * tbName << "����" << nCol << "��������:" << std::endl;
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
#line 357 "SQLParser.y"
    {
            //�����ݱ��в���������
            std::string * tbName = (yyvsp[(3) - (7)].v_s);
            UnionValueTable * rowList = (yyvsp[(5) - (7)].u_vt);
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.INSERT INTO: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else {
                Table * table = cur.database -> getTableByName(* tbName);
                //������һ��һ�еĲ��뵽����
                int insertCnt = 0;
                for (int i = 0; i < (int) rowList -> size(); i ++) {
                    //�������ݿ��е�������
                    UnionValueRow * sqlRow = rowList -> at(i);
                    std::string errMsg;
                    TableRow * tableRow = genTableRow(sqlRow, table, errMsg);
                    if (tableRow == NULL) {
                        std::cout << "Parser.INSERT INTO: error" << std::endl;
                        std::cout << "����ĵ�" << i << "�������в��������ݱ�" << table -> getName() << "�ĸ�ʽҪ��" << std::endl;
                        std::cout << errMsg << std::endl;
                        continue;
                    }
                    table -> insertRow(tableRow);
                    insertCnt += 1;
                }
                std::cout << "�����" << insertCnt << "��������" << std::endl;
            }
        ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 392 "SQLParser.y"
    {
            std::string * tbName = (yyvsp[(3) - (8)].v_s);
        ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 397 "SQLParser.y"
    {
            std::string * tbName = (yyvsp[(2) - (8)].v_s);
        ;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 402 "SQLParser.y"
    {
        ;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 408 "SQLParser.y"
    {
        ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 412 "SQLParser.y"
    {
        ;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 418 "SQLParser.y"
    {
            (yyval.u_fl) = new UnionFieldList();
            (yyval.u_fl) -> push_back((yyvsp[(1) - (1)].u_fd));
        ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 424 "SQLParser.y"
    {
            (yyval.u_fl) = (yyvsp[(1) - (3)].u_fl);
            (yyval.u_fl) -> push_back((yyvsp[(3) - (3)].u_fd));
        ;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 432 "SQLParser.y"
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

  case 27:

/* Line 1455 of yacc.c  */
#line 444 "SQLParser.y"
    {
            std::string * colName = (yyvsp[(1) - (4)].v_s);
            
            (yyval.u_fd) = new UnionField();
            (yyval.u_fd) -> ty = 1;
            (yyval.u_fd) -> dt.tc = new TableColumn();
            (yyval.u_fd) -> dt.tc -> setName(* colName);
            (yyval.u_fd) -> dt.tc -> setType((yyvsp[(2) - (4)].v_t));
        ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 455 "SQLParser.y"
    {
            StringList * colList = (yyvsp[(4) - (5)].v_sl);
            (yyval.u_fd) = new UnionField();
            (yyval.u_fd) -> ty = 2;
            (yyval.u_fd) -> dt.pk = colList;
        ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 463 "SQLParser.y"
    {
            //ȥһ���������ݱ��а�һ�������е����Ը��ƹ���
            std::string * colName = (yyvsp[(4) - (10)].v_s);
            std::string * tbName = (yyvsp[(7) - (10)].v_s);
            std::string * colName0 = (yyvsp[(9) - (10)].v_s);
            (yyval.u_fd) = new UnionField();
            //���û�д����ݿ⣬����
            if (cur.database == NULL) {
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "û���Ѿ��򿪵����ݿ�" << std::endl;
            } else if (!cur.database -> hasOpenedTable(* tbName)) {
                //���û��������ݱ�����
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "û�����ݱ�:" << * tbName << std::endl;
            } else if (!cur.database -> getTableByName(* tbName) -> getTableHeader() -> hasColumn(* colName0)) { 
                //���û����������У�����
                std::cout << "Parser.FOREIGN KEY: error" << std::endl;
                std::cout << "���ݱ�" << * (yyvsp[(7) - (10)].v_s) << "��û��������:" << * colName0 << std::endl;
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

  case 30:

/* Line 1455 of yacc.c  */
#line 498 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_bool;
        ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 503 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_char;
        ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 508 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_short;
        ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 513 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_int;
        ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 518 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_long;
        ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 523 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_float;
        ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 528 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_double;
        ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 533 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_string;
        ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 538 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_int;
        ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 543 "SQLParser.y"
    {
            (yyval.v_t) = TableDataType::t_lob;
        ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 550 "SQLParser.y"
    {
            (yyval.u_vt) = new UnionValueTable();
            (yyval.u_vt) -> push_back((yyvsp[(2) - (3)].u_vr));
        ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 556 "SQLParser.y"
    {
            (yyval.u_vt) = (yyvsp[(1) - (5)].u_vt);
            (yyval.u_vt) -> push_back((yyvsp[(4) - (5)].u_vr));
        ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 564 "SQLParser.y"
    {
            (yyval.u_vr) = new UnionValueRow();
            (yyval.u_vr) -> push_back((yyvsp[(1) - (1)].u_va));
        ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 570 "SQLParser.y"
    {
            (yyval.u_vr) = (yyvsp[(1) - (3)].u_vr);
            (yyval.u_vr) -> push_back((yyvsp[(3) - (3)].u_va));
        ;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 578 "SQLParser.y"
    {
            (yyval.u_va) = new UnionValue();
        ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 583 "SQLParser.y"
    {
            (yyval.u_va) = new UnionValue();
            (yyval.u_va) -> ty = 1;
            (yyval.u_va) -> dt.u = (yyvsp[(1) - (1)].v_u);
        ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 590 "SQLParser.y"
    {
            (yyval.u_va) = new UnionValue();
            (yyval.u_va) -> ty = 2;
            (yyval.u_va) -> dt.d = (yyvsp[(1) - (1)].v_d);
        ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 597 "SQLParser.y"
    {
            (yyval.u_va) = new UnionValue();
            (yyval.u_va) -> ty = 3;
            (yyval.u_va) -> dt.s = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 606 "SQLParser.y"
    {
        ;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 610 "SQLParser.y"
    {
        ;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 616 "SQLParser.y"
    {
        ;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 620 "SQLParser.y"
    {
        ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 624 "SQLParser.y"
    {
        ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 630 "SQLParser.y"
    {
        ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 634 "SQLParser.y"
    {
        ;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 640 "SQLParser.y"
    {
        ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 644 "SQLParser.y"
    {
        ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 648 "SQLParser.y"
    {
        ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 652 "SQLParser.y"
    {
        ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 656 "SQLParser.y"
    {
        ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 660 "SQLParser.y"
    {
        ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 666 "SQLParser.y"
    {
        ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 670 "SQLParser.y"
    {
        ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 676 "SQLParser.y"
    {
        ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 680 "SQLParser.y"
    {
        ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 686 "SQLParser.y"
    {
        ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 692 "SQLParser.y"
    {
            (yyval.v_sl) = new StringList();
            (yyval.v_sl) -> push_back((yyvsp[(1) - (1)].v_s));
        ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 698 "SQLParser.y"
    {
            (yyval.v_sl) = (yyvsp[(1) - (3)].v_sl);
            (yyval.v_sl) -> push_back((yyvsp[(3) - (3)].v_s));
        ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 706 "SQLParser.y"
    {
            (yyval.v_s) = (yyvsp[(1) - (1)].v_s);
        ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 713 "SQLParser.y"
    {
            setCmdColor(0);
            cur.table = NULL;
        ;}
    break;



/* Line 1455 of yacc.c  */
#line 2388 "SQLParser.cpp"
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
#line 719 "SQLParser.y"


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
    yyparse();
}

