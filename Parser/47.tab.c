/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     FOR = 260,
     WHILE = 261,
     DO = 262,
     BREAK = 263,
     INT = 264,
     CHAR = 265,
     FLOAT = 266,
     DOUBLE = 267,
     VOID = 268,
     RETURN = 269,
     SWITCH = 270,
     CASE = 271,
     DEFAULT = 272,
     CONTINUE = 273,
     CONST_INT = 274,
     CONST_FLOAT = 275,
     CONST_CHAR = 276,
     ADDOP = 277,
     MULOP = 278,
     INCOP = 279,
     DECOP = 280,
     RELOP = 281,
     ASSIGNOP = 282,
     LOGICOP = 283,
     NOT = 284,
     LPAREN = 285,
     RPAREN = 286,
     LCURL = 287,
     RCURL = 288,
     LTHIRD = 289,
     RTHIRD = 290,
     COMMA = 291,
     SEMICOLON = 292,
     ID = 293,
     PRINTLN = 294,
     LOWER_THAN_ELSE = 295
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define FOR 260
#define WHILE 261
#define DO 262
#define BREAK 263
#define INT 264
#define CHAR 265
#define FLOAT 266
#define DOUBLE 267
#define VOID 268
#define RETURN 269
#define SWITCH 270
#define CASE 271
#define DEFAULT 272
#define CONTINUE 273
#define CONST_INT 274
#define CONST_FLOAT 275
#define CONST_CHAR 276
#define ADDOP 277
#define MULOP 278
#define INCOP 279
#define DECOP 280
#define RELOP 281
#define ASSIGNOP 282
#define LOGICOP 283
#define NOT 284
#define LPAREN 285
#define RPAREN 286
#define LCURL 287
#define RCURL 288
#define LTHIRD 289
#define RTHIRD 290
#define COMMA 291
#define SEMICOLON 292
#define ID 293
#define PRINTLN 294
#define LOWER_THAN_ELSE 295




/* Copy the first part of user declarations.  */
#line 1 "47.y"


#include "bits/stdc++.h"
#include "symbolTable.h"

// #define YYSTYPE symbolInfo*

using namespace std;

symbolTable table(30);
FILE *errorout = fopen("error.txt", "w");
FILE *logout = fopen("log.txt", "w");
FILE *parseout = fopen("parseTree.txt", "w");

bool ErrFunc = false;
int yyparse(void);
int yylex(void);


extern int line_count;
extern int errorCount;
extern FILE* yyin;

vector< pair<string,string> > paramsList;
vector<symbolInfo*>func;

void yyerror(string s)
{
	//write your code
    //cout<<s<<endl;
	fprintf(logout, "Error at line no %d : syntax error \n", line_count);
    //if(s!="syntax error")
    fprintf(errorout, "line# %d : %s\n", line_count, s.c_str());
    //else{
    //cout<<line_count<<endl;
    //cout<<s<<endl;
    //errorCount++;
   // }
}


bool checkAssignOp(string type1, string type2){
    bool arrayType1 = false;
    bool arrayType2 = false;
    if(type1.size()>=2){
        if(type1[type1.size()-2]=='[' && type1[type1.size()-1]==']'){
            arrayType1 = true;
        }
    }
    if(type2.size()>=2){
        if(type2[type2.size()-2]=='[' && type2[type2.size()-1]==']'){
            arrayType2 = true;
        }
    }

    if(type1=="none" || type2=="none") return true;
    else if(type1=="" || type2=="") return true;
    else if(type1=="void" || type2=="void") return false;
    else if(arrayType1) return false;
    else if(arrayType2) return false;
    else if(type1=="float" && type2=="int") return true;
    else if(type1!=type2) return false;
    else return true;

}

void rulePrint(string leftTerm, string rightTerm){
    //fprintf(logout, "Line# %d: %s : %s\n\n", line_count, leftTerm.c_str(), rightTerm.c_str());
    fprintf(logout, "%s : %s\n", leftTerm.c_str(), rightTerm.c_str());
}

void logPrint(string tempName){
    //fprintf(logout, "lexeme %s found\n\n", tempName.c_str());
}

void errorPrint(string errorMsg){
    //fprintf(logout, "Error at line %d: %s\n", line_count, errorMsg.c_str());
    //fprintf(errorout, "line# %d: %s\n", line_count, errorMsg.c_str());
}

void printTree(symbolInfo* head,string space){
    //cout<<space<<head->getSymbolName()<<":"<<head->getsymbolType()<<endl;

    if(head->leaf){
        fprintf(parseout, "%s%s", space.c_str(), head->rule.c_str());
    }
    else{
    fprintf(parseout, "%s %s : %s", space.c_str(), head->getSymbolName().c_str(),head->getsymbolType().c_str());
    }

    if(head->leaf){
        fprintf(parseout,"\t<Line: %d>\n",head->startLine);
    }
    else{
        fprintf(parseout,"\t<Line: %d-%d>\n",head->startLine,head->endLine);
    }


    
    for(int i=0;i<head->childList.size();i++){ 
        //cout<<(head->childList[i])->getsymbolType()<<endl;
        printTree(head->childList[i],space+" ");    
    }
    
}

void deleteTree(symbolInfo* root){
    if(root==nullptr) return;

    vector<symbolInfo*>childList=root->getChildList();

    for(symbolInfo* child:childList){
        deleteTree(child); 
    }
    delete root;
}



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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 121 "47.y"
{
    symbolInfo* treeNode;
}
/* Line 193 of yacc.c.  */
#line 299 "47.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 312 "47.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   268

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  86
/* YYNRULES -- Number of states.  */
#define YYNSTATES  160

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    10,    12,    14,    16,    23,
      30,    38,    46,    52,    58,    65,    72,    79,    87,    93,
      99,   106,   109,   114,   120,   124,   129,   132,   134,   139,
     143,   149,   155,   156,   160,   162,   164,   166,   170,   175,
     182,   190,   192,   197,   204,   209,   213,   215,   218,   222,
     224,   226,   228,   236,   242,   250,   256,   262,   266,   268,
     271,   273,   278,   282,   284,   288,   290,   294,   296,   300,
     302,   306,   308,   312,   315,   318,   320,   322,   327,   331,
     333,   335,   338,   341,   343,   344,   348
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    43,    -1,    43,    44,    -1,    44,    -1,
      50,    -1,    45,    -1,    46,    -1,    51,    38,    30,    47,
      31,    37,    -1,    51,    38,    30,    47,    31,     1,    -1,
      51,    38,    30,    47,     1,    31,    37,    -1,    51,    38,
      30,    47,     1,    31,     1,    -1,    51,    38,    30,    31,
      37,    -1,    51,    38,    30,    31,     1,    -1,    51,    38,
      30,     1,    31,    37,    -1,    51,    38,    30,     1,    31,
       1,    -1,    51,    38,    30,    47,    31,    48,    -1,    51,
      38,    30,    47,     1,    31,    48,    -1,     1,    30,    47,
      31,    48,    -1,    51,    38,    30,    31,    48,    -1,    51,
      38,    30,     1,    31,    48,    -1,     1,    48,    -1,    47,
      36,    51,    38,    -1,    47,     1,    36,    51,    38,    -1,
      47,    36,    51,    -1,    47,     1,    36,    51,    -1,    51,
      38,    -1,    51,    -1,    32,    49,    53,    33,    -1,    32,
      49,    33,    -1,    32,    49,    53,     1,    33,    -1,    32,
      49,     1,    53,    33,    -1,    -1,    51,    52,    37,    -1,
       9,    -1,    11,    -1,    13,    -1,    52,    36,    38,    -1,
      52,     1,    36,    38,    -1,    52,    36,    38,    34,    19,
      35,    -1,    52,     1,    36,    38,    34,    19,    35,    -1,
      38,    -1,    38,    34,    19,    35,    -1,    52,    36,    38,
      34,    20,    35,    -1,    38,    34,    20,    35,    -1,    38,
      34,    35,    -1,    54,    -1,    53,    54,    -1,    53,     1,
      54,    -1,    50,    -1,    55,    -1,    48,    -1,     5,    30,
      55,    55,    57,    31,    54,    -1,     3,    30,    57,    31,
      54,    -1,     3,    30,    57,    31,    54,     4,    54,    -1,
       6,    30,    57,    31,    54,    -1,    39,    30,    38,    31,
      37,    -1,    14,    57,    37,    -1,    37,    -1,    57,    37,
      -1,    38,    -1,    38,    34,    57,    35,    -1,    38,    34,
      35,    -1,    58,    -1,    56,    27,    58,    -1,    59,    -1,
      59,    28,    59,    -1,    60,    -1,    60,    26,    60,    -1,
      61,    -1,    60,    22,    61,    -1,    62,    -1,    61,    23,
      62,    -1,    22,    62,    -1,    29,    62,    -1,    63,    -1,
      56,    -1,    38,    30,    64,    31,    -1,    30,    57,    31,
      -1,    19,    -1,    20,    -1,    56,    24,    -1,    56,    25,
      -1,    65,    -1,    -1,    65,    36,    58,    -1,    58,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   138,   138,   149,   162,   172,   181,   192,   202,   260,
     311,   367,   420,   461,   496,   534,   570,   644,   715,   729,
     783,   835,   851,   874,   898,   916,   939,   954,   968,   984,
     998,  1013,  1030,  1048,  1092,  1102,  1112,  1123,  1140,  1159,
    1179,  1203,  1220,  1237,  1257,  1276,  1296,  1307,  1321,  1333,
    1344,  1354,  1365,  1383,  1398,  1415,  1431,  1451,  1465,  1475,
    1489,  1516,  1529,  1572,  1582,  1615,  1625,  1656,  1666,  1721,
    1731,  1790,  1801,  1864,  1886,  1906,  1918,  1928,  2006,  2020,
    2033,  2046,  2066,  2086,  2103,  2109,  2124
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "FOR", "WHILE", "DO",
  "BREAK", "INT", "CHAR", "FLOAT", "DOUBLE", "VOID", "RETURN", "SWITCH",
  "CASE", "DEFAULT", "CONTINUE", "CONST_INT", "CONST_FLOAT", "CONST_CHAR",
  "ADDOP", "MULOP", "INCOP", "DECOP", "RELOP", "ASSIGNOP", "LOGICOP",
  "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD", "COMMA",
  "SEMICOLON", "ID", "PRINTLN", "LOWER_THAN_ELSE", "$accept", "start",
  "program", "unit", "func_declaration", "func_definition",
  "parameter_list", "compound_statement", "scopeController",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "expression_statement", "variable", "expression",
  "logic_expression", "rel_expression", "simple_expression", "term",
  "unary_expression", "factor", "argument_list", "arguments", 0
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
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    45,    45,
      45,    45,    45,    45,    45,    45,    46,    46,    46,    46,
      46,    46,    47,    47,    47,    47,    47,    47,    48,    48,
      48,    48,    49,    50,    51,    51,    51,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    53,    53,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    55,
      56,    56,    56,    57,    57,    58,    58,    59,    59,    60,
      60,    61,    61,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     6,
       7,     7,     5,     5,     6,     6,     6,     7,     5,     5,
       6,     2,     4,     5,     3,     4,     2,     1,     4,     3,
       5,     5,     0,     3,     1,     1,     1,     3,     4,     6,
       7,     1,     4,     6,     4,     3,     1,     2,     3,     1,
       1,     1,     7,     5,     7,     5,     5,     3,     1,     2,
       1,     4,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    34,    35,    36,     0,     0,     4,     6,     7,
       5,     0,     0,    32,    21,     1,     3,    41,     0,     0,
      27,     0,     0,     0,     0,     0,    33,     0,     0,     0,
      26,     0,     0,     0,     0,     0,    79,    80,     0,     0,
       0,    29,    58,    60,     0,    51,    49,     0,     0,    46,
      50,    76,     0,    63,    65,    67,    69,    71,    75,     0,
       0,     0,     0,     0,    45,     0,    37,     0,    18,    24,
       0,     0,     0,     0,     0,    76,    73,    74,     0,    84,
       0,     0,    41,     0,    28,    47,    81,    82,     0,    59,
       0,     0,     0,     0,     0,    13,    12,    19,     0,     0,
      42,    44,    38,     0,    25,    22,     0,    31,     0,     0,
       0,    57,    78,    86,     0,    83,    62,     0,     0,    30,
      48,    64,    66,    70,    68,    72,    15,    14,    20,     0,
       9,     8,    16,     0,     0,     0,    23,     0,     0,     0,
      77,     0,    61,     0,    11,    10,    17,     0,    39,    43,
      53,     0,    55,    85,    56,    40,     0,     0,    54,    52
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     5,     6,     7,     8,     9,    19,    45,    21,    46,
      47,    18,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,   114,   115
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -76
static const yytype_int16 yypact[] =
{
     130,    57,   -76,   -76,   -76,    26,   244,   -76,   -76,   -76,
     -76,   -23,    66,   -76,   -76,   -76,   -76,    40,    21,    13,
      -4,    77,   131,    65,     4,     7,   -76,    12,    39,    66,
     -76,   229,    46,    51,    83,   151,   -76,   -76,   151,   151,
     151,   -76,   -76,    71,    88,   -76,   -76,    85,   116,   -76,
     -76,   212,    58,   -76,   109,    98,   103,   -76,   -76,   119,
      15,    36,   112,   117,   -76,   113,   123,    66,   -76,   121,
     155,   151,   180,   151,   126,    78,   -76,   -76,   134,   151,
       1,   129,   138,   192,   -76,   -76,   -76,   -76,   151,   -76,
     151,   151,   151,   151,    28,   -76,   -76,   -76,   -12,    31,
     -76,   -76,   142,   114,   140,   -76,   229,   -76,   148,   180,
     152,   -76,   -76,   -76,   159,   146,   -76,   156,   165,   -76,
     -76,   -76,   -76,   103,   164,   -76,   -76,   -76,   -76,    32,
     -76,   -76,   -76,   185,   172,   173,   -76,   229,   151,   229,
     -76,   151,   -76,   176,   -76,   -76,   -76,   181,   -76,   -76,
     211,   188,   -76,   -76,   -76,   -76,   229,   229,   -76,   -76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -76,   -76,   -76,   214,   -76,   -76,   201,    -1,   -76,    11,
       6,   -76,   195,   -45,   -63,   -37,   -30,   -75,   137,   136,
     150,   -31,   -76,   -76,   -76
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -3
static const yytype_int16 yytable[] =
{
      14,    75,    75,    85,   113,    74,    11,    76,    77,   109,
      78,    10,    11,   121,    27,    17,    95,    10,    20,   129,
      36,    37,    24,    38,    67,    85,    15,    68,    20,   126,
      39,    40,   130,   144,    30,    69,   116,    98,   120,    43,
      65,   108,    75,   110,    28,    66,   138,    13,    67,    29,
     117,    75,    96,    75,    75,    75,    75,    25,    26,    97,
      13,   120,   125,    13,    13,   127,   153,    99,   131,   145,
      22,    13,    29,   104,    23,     2,    71,     3,    31,     4,
      32,    72,    33,    34,    62,    63,     2,    12,     3,    13,
       4,    35,   150,   128,   152,    89,    36,    37,   132,    38,
      64,    79,    86,    87,    75,    80,    39,    40,   151,    13,
      41,   158,   159,    73,    42,    43,    44,    83,    81,    32,
      91,    33,    34,    82,    92,     2,    93,     3,   146,     4,
      35,     1,    59,   134,   135,    36,    37,    90,    38,     2,
       2,     3,     3,     4,     4,    39,    40,   100,    13,    84,
      94,   102,   101,    42,    43,    44,   106,   103,    32,   105,
      33,    34,    60,   111,     2,   112,     3,   118,     4,    35,
      36,    37,    23,    38,    36,    37,   133,    38,   136,   137,
      39,    40,   141,   139,    39,    40,    91,    13,   107,    43,
     140,   142,    42,    43,    44,    32,   143,    33,    34,    36,
      37,     2,    38,     3,   147,     4,    35,   148,   149,    39,
      40,    36,    37,   154,    38,   156,   155,    42,    43,   157,
      16,    39,    40,    61,    13,   119,    70,   122,   124,    42,
      43,    44,    32,     0,    33,    34,    86,    87,     2,    88,
       3,   123,     4,    35,    -2,     1,     0,     0,    36,    37,
       0,    38,     0,     2,     0,     3,     0,     4,    39,    40,
       0,    13,     0,     0,     0,     0,    42,    43,    44
};

static const yytype_int16 yycheck[] =
{
       1,    38,    39,    48,    79,    35,     0,    38,    39,    72,
      40,     0,     6,    88,     1,    38,     1,     6,    12,    31,
      19,    20,     1,    22,    36,    70,     0,    28,    22,     1,
      29,    30,     1,     1,    38,    29,    35,     1,    83,    38,
      36,    71,    79,    73,    31,    38,   109,    32,    36,    36,
      80,    88,    37,    90,    91,    92,    93,    36,    37,    60,
      32,   106,    93,    32,    32,    37,   141,    31,    37,    37,
      30,    32,    36,    67,    34,     9,    30,    11,     1,    13,
       3,    30,     5,     6,    19,    20,     9,    30,    11,    32,
      13,    14,   137,    94,   139,    37,    19,    20,    99,    22,
      35,    30,    24,    25,   141,    34,    29,    30,   138,    32,
      33,   156,   157,    30,    37,    38,    39,     1,    30,     3,
      22,     5,     6,    38,    26,     9,    23,    11,   129,    13,
      14,     1,     1,    19,    20,    19,    20,    28,    22,     9,
       9,    11,    11,    13,    13,    29,    30,    35,    32,    33,
      31,    38,    35,    37,    38,    39,     1,    34,     3,    38,
       5,     6,    31,    37,     9,    31,    11,    38,    13,    14,
      19,    20,    34,    22,    19,    20,    34,    22,    38,    31,
      29,    30,    36,    31,    29,    30,    22,    32,    33,    38,
      31,    35,    37,    38,    39,     3,    31,     5,     6,    19,
      20,     9,    22,    11,    19,    13,    14,    35,    35,    29,
      30,    19,    20,    37,    22,     4,    35,    37,    38,    31,
       6,    29,    30,    22,    32,    33,    31,    90,    92,    37,
      38,    39,     3,    -1,     5,     6,    24,    25,     9,    27,
      11,    91,    13,    14,     0,     1,    -1,    -1,    19,    20,
      -1,    22,    -1,     9,    -1,    11,    -1,    13,    29,    30,
      -1,    32,    -1,    -1,    -1,    -1,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     9,    11,    13,    42,    43,    44,    45,    46,
      50,    51,    30,    32,    48,     0,    44,    38,    52,    47,
      51,    49,    30,    34,     1,    36,    37,     1,    31,    36,
      38,     1,     3,     5,     6,    14,    19,    20,    22,    29,
      30,    33,    37,    38,    39,    48,    50,    51,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,     1,
      31,    47,    19,    20,    35,    36,    38,    36,    48,    51,
      53,    30,    30,    30,    57,    56,    62,    62,    57,    30,
      34,    30,    38,     1,    33,    54,    24,    25,    27,    37,
      28,    22,    26,    23,    31,     1,    37,    48,     1,    31,
      35,    35,    38,    34,    51,    38,     1,    33,    57,    55,
      57,    37,    31,    58,    64,    65,    35,    57,    38,    33,
      54,    58,    59,    61,    60,    62,     1,    37,    48,    31,
       1,    37,    48,    34,    19,    20,    38,    31,    55,    31,
      31,    36,    35,    31,     1,    37,    48,    19,    35,    35,
      54,    57,    54,    58,    37,    35,     4,    31,    54,    54
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 138 "47.y"
    {         
                (yyval.treeNode)=new symbolInfo("start","program");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));
                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                rulePrint("start", "program");

                printTree((yyval.treeNode),"");
        ;}
    break;

  case 3:
#line 149 "47.y"
    {
               
                (yyval.treeNode) = new symbolInfo("program", "program unit");
                
                rulePrint("program", "program unit");

                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (2)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (2)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine;

        ;}
    break;

  case 4:
#line 162 "47.y"
    {
                (yyval.treeNode) = new symbolInfo("program", "unit");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                rulePrint("program", "unit");
        ;}
    break;

  case 5:
#line 172 "47.y"
    {
                (yyval.treeNode) = new symbolInfo("unit", "var_declaration");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                rulePrint("unit", "var_declaration");
     ;}
    break;

  case 6:
#line 181 "47.y"
    {
                (yyval.treeNode) = new symbolInfo("unit", "func_declaration");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                rulePrint("unit", "func_declaration");

     ;}
    break;

  case 7:
#line 192 "47.y"
    {
                (yyval.treeNode) = new symbolInfo("unit", "func_definition");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                rulePrint("unit", "func_definition");
     ;}
    break;

  case 8:
#line 202 "47.y"
    {
  
                                (yyval.treeNode) = new symbolInfo("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(6) - (6)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (6)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(6) - (6)].treeNode)->endLine;

                                

                                string _id = (yyvsp[(2) - (6)].treeNode)->getSymbolName();
                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup((yyvsp[(2) - (6)].treeNode)->getSymbolName()); //need to check all scopetables
                                //declaration of same name function
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                            
                                }
                                else{
                                    //symbolInfo *newFunc = new symbolInfo(_id, "ID");
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+(yyvsp[(1) - (6)].treeNode)->getSymbolName());
                            
                                    //symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION");


                                    int paramsNo = paramsList.size();
                                    for(int i=0; i<paramsNo; i++){
                                        /*
                                            param er type list1 e store hobe
                                            param er name list2 e store hobe
                                        */
                                        string _type = paramsList[i].first;
                                        string _name = paramsList[i].second;
                                        newFunc->insertToList1(_type);
                                        newFunc->insertToList2(_name);
                                    }

                                    paramsList.clear();

                                    newFunc->setTypeVar((yyvsp[(1) - (6)].treeNode)->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                    
                                    //func.push_back(newFunc);
                                }



                                rulePrint("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");


                ;}
    break;

  case 9:
#line 260 "47.y"
    {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(string a)
                                */
                                (yyval.treeNode) = new symbolInfo("func_declaration","RPAREN error");
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (6)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (6)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(5) - (6)].treeNode)->endLine;

                                yyerror("RPAREN of func_declaration");
                                errorCount++;
                                string _id = (yyvsp[(2) - (6)].treeNode)->getSymbolName();
                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup((yyvsp[(2) - (6)].treeNode)->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    //symbolInfo *newFunc = new symbolInfo(_id, "ID");
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+(yyvsp[(1) - (6)].treeNode)->getSymbolName());

                                    int paramsNo = paramsList.size();
                                    for(int i=0; i<paramsNo; i++){
                                        /*
                                            param er type list1 e store hobe
                                            param er name list2 e store hobe
                                        */
                                        string _type = paramsList[i].first;
                                        string _name = paramsList[i].second;
                                        newFunc->insertToList1(_type);
                                        newFunc->insertToList2(_name);
                                        
                                    }

                                    paramsList.clear();

                                    newFunc->setTypeVar((yyvsp[(1) - (6)].treeNode)->getSymbolName());
                        
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    //table.insert(newFunc);
                                }
                                

                ;}
    break;

  case 10:
#line 311 "47.y"
    {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(int a+b);
                                */
                                (yyval.treeNode) = new symbolInfo("func_declaration","parameter_list error");
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(6) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(7) - (7)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (7)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(7) - (7)].treeNode)->endLine;

                                yyerror("parameter_list of func_declaration");
                                errorCount++;
                                string _id = (yyvsp[(2) - (7)].treeNode)->getSymbolName();

                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup((yyvsp[(2) - (7)].treeNode)->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+(yyvsp[(1) - (7)].treeNode)->getSymbolName());


                                    int paramsNo = paramsList.size();
                                    for(int i=0; i<paramsNo; i++){
                                        /*
                                            param er type list1 e store hobe
                                            param er name list2 e store hobe
                                        */
                                        string _type = paramsList[i].first;
                                        string _name = paramsList[i].second;
                                        newFunc->insertToList1(_type);
                                        newFunc->insertToList2(_name);
                                        
                                    }

                                    paramsList.clear();

                                    newFunc->setTypeVar((yyvsp[(1) - (7)].treeNode)->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    //table.insert(newFunc);
                                }



                                rulePrint("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
                                

                ;}
    break;

  case 11:
#line 367 "47.y"
    {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(int a+b)*/
                               (yyval.treeNode) = new symbolInfo("func_declaration","parameter_list error RPAREN error");    
                               (yyval.treeNode)->insertToChildList((yyvsp[(1) - (7)].treeNode));
                               (yyval.treeNode)->insertToChildList((yyvsp[(2) - (7)].treeNode));
                               (yyval.treeNode)->insertToChildList((yyvsp[(3) - (7)].treeNode));
                               (yyval.treeNode)->insertToChildList((yyvsp[(4) - (7)].treeNode));
                               (yyval.treeNode)->insertToChildList((yyvsp[(6) - (7)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (7)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(6) - (7)].treeNode)->endLine;

                               yyerror("parameter_list,RPAREN of func_declaration");
                               errorCount++;
                                string _id = (yyvsp[(2) - (7)].treeNode)->getSymbolName();

                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup((yyvsp[(2) - (7)].treeNode)->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+(yyvsp[(1) - (7)].treeNode)->getSymbolName());


                                    int paramsNo = paramsList.size();
                                    for(int i=0; i<paramsNo; i++){
                                        /*
                                            param er type list1 e store hobe
                                            param er name list2 e store hobe
                                        */
                                        string _type = paramsList[i].first;
                                        string _name = paramsList[i].second;
                                        newFunc->insertToList1(_type);
                                        newFunc->insertToList2(_name);
                                        
                                    }

                                    paramsList.clear();

                                    newFunc->setTypeVar((yyvsp[(1) - (7)].treeNode)->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    //table.insert(newFunc);
                                }



                               // rulePrint("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN");
                                
                ;}
    break;

  case 12:
#line 420 "47.y"
    {
         
                                (yyval.treeNode) = new symbolInfo("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine;

                                

                                //string stmt = $1->getSymbolName()+ " " + $2->getSymbolName() + "();";
                                string _id = (yyvsp[(2) - (5)].treeNode)->getSymbolName();
                                
                                //SymbolInfo *checker = new SymbolInfo();
                                symbolInfo *checker = table.lookup((yyvsp[(2) - (5)].treeNode)->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+(yyvsp[(1) - (5)].treeNode)->getSymbolName());                      
                                    //symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION");
                                    newFunc->setTypeVar((yyvsp[(1) - (5)].treeNode)->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                    if(newFunc->getSymbolName()=="foo")
                                    //cout<<"insert address from bison file:"<<newFunc<<endl;
                                    //cout<<newFunc->getSymbolName()<<endl;
                                    func.push_back(newFunc);
                                    
                                }



                                rulePrint("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");

                ;}
    break;

  case 13:
#line 461 "47.y"
    {
                                /*
                                    Error recovery of func_definition like:
                                    int foo()
                                */
                                (yyval.treeNode) = new symbolInfo("func_declaration","RPAREN error");
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(4) - (5)].treeNode)->endLine;

                                yyerror("RPAREN of func_declaration");
                                errorCount++;
                                string stmt = (yyvsp[(1) - (5)].treeNode)->getSymbolName()+ " " + (yyvsp[(2) - (5)].treeNode)->getSymbolName() + "()";
                                string _id = (yyvsp[(2) - (5)].treeNode)->getSymbolName();

                                //$$ = new symbolInfo(stmt,"func_declaration");
                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup((yyvsp[(2) - (5)].treeNode)->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+(yyvsp[(1) - (5)].treeNode)->getSymbolName());
                                    newFunc->setTypeVar((yyvsp[(1) - (5)].treeNode)->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                }

                                rulePrint("func_declaration", "type_specifier ID LPAREN RPAREN");
                ;}
    break;

  case 14:
#line 496 "47.y"
    {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(*);
                                */
                                (yyval.treeNode) = new symbolInfo("func_declaration","LPAREN error");
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(6) - (6)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (6)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(6) - (6)].treeNode)->endLine;

                                yyerror("LPAREN of func_declaration");
                                errorCount++;
                                string _id = (yyvsp[(2) - (6)].treeNode)->getSymbolName();


                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup((yyvsp[(2) - (6)].treeNode)->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+(yyvsp[(1) - (6)].treeNode)->getSymbolName());
                                    newFunc->setTypeVar((yyvsp[(1) - (6)].treeNode)->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                }



                                //rulePrint("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
                                
                ;}
    break;

  case 15:
#line 534 "47.y"
    {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(*)
                                */
                                (yyval.treeNode) = new symbolInfo("func_declaration","LPAREN error RPAREN error");
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (6)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (6)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(5) - (6)].treeNode)->endLine;

                                yyerror("LPAREN,RPAREN of func_declaration");
                                errorCount++;
                                string _id = (yyvsp[(2) - (6)].treeNode)->getSymbolName();

                               
                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup((yyvsp[(2) - (6)].treeNode)->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+(yyvsp[(1) - (6)].treeNode)->getSymbolName());
                                    newFunc->setTypeVar((yyvsp[(1) - (6)].treeNode)->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                }

                                //rulePrint("func_declaration", "type_specifier ID LPAREN RPAREN");
                              
                ;}
    break;

  case 16:
#line 570 "47.y"
    {
                        string _def = (yyvsp[(1) - (6)].treeNode)->getSymbolName() + " " + (yyvsp[(2) - (6)].treeNode)->getSymbolName() + "(" + (yyvsp[(4) - (6)].treeNode)->getSymbolName() + ")";

                                symbolInfo *returnedSym = table.lookup((yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                if(returnedSym!=nullptr){
                                    string retSymFuncST = returnedSym->getFuncSt();
                                    string retSymType = returnedSym->getTypeVar();
                                    if(retSymFuncST!="declaration"){
                                        yyerror("Multiple Declaration of " + (yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType!=(yyvsp[(1) - (6)].treeNode)->getSymbolName()){
                                        yyerror("Return type mismatch with function declaration in function "+(yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType==(yyvsp[(1) - (6)].treeNode)->getSymbolName()){
                                        vector<string> decParamsTypeList = returnedSym->getList1(); //type list of paramsList in declaration
                                        if(decParamsTypeList.size() == paramsList.size()){
                                            bool checker = true;
                                            for(int i=0; i<paramsList.size(); i++){
                                                string _paramType = paramsList[i].first;
                                                if(decParamsTypeList[i]!=_paramType){
                                                    int x = i+1;
                                                    yyerror(x + "th argument mismatch in function "+(yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                                    errorCount++;
                                                    checker = false;
                                                    break;

                                                }
                                            }
                                            if(checker == true){
                                                returnedSym->setFuncSt("definition");
                                            }
                                        }
                                        else{
                                            yyerror("Total number of arguments mismatch with declaration in function "+(yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                            errorCount++;
                                        }
                                        decParamsTypeList.clear();
                                    }
                                }
                                else{
                                    symbolInfo *symbol = new symbolInfo((yyvsp[(2) - (6)].treeNode)->getSymbolName(), "FUNCTION,"+(yyvsp[(1) - (6)].treeNode)->getSymbolName());
                                    
                                    //symbolInfo *symbol = new symbolInfo($2->getSymbolName(), "FUNCTION");
                                    
                                    int params_no = paramsList.size();
  
                                    for(int i=0; i<params_no; i++){
                                        string paramsType = paramsList[i].first;
                                        string paramsName = paramsList[i].second;
                                        symbol->insertToList1(paramsType);
                                        symbol->insertToList2(paramsName);
                                    }
                                    symbol->setTypeVar((yyvsp[(1) - (6)].treeNode)->getSymbolName());
                
                                    symbol->setFuncSt("definition");
                                    table.insert(symbol);
                                    //func.push_back(symbol);
                                    //cout<<symbol->getTypeVar()<<" "<<symbol->getName()<<endl;
                                    
                                }
                                (yyval.treeNode) = new symbolInfo("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");                               
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(6) - (6)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (6)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(6) - (6)].treeNode)->endLine;
                ;}
    break;

  case 17:
#line 644 "47.y"
    {
                                 yyerror("parameter_list of func_definition");
                                 errorCount++;
                                string _def = (yyvsp[(1) - (7)].treeNode)->getSymbolName() + " " + (yyvsp[(2) - (7)].treeNode)->getSymbolName() + "(" + (yyvsp[(4) - (7)].treeNode)->getSymbolName() + ")";

                                symbolInfo *returnedSym = table.lookup((yyvsp[(2) - (7)].treeNode)->getSymbolName());
                                if(returnedSym!=nullptr){
                                    string retSymFuncST = returnedSym->getFuncSt();
                                    string retSymType = returnedSym->getTypeVar();
                                    if(retSymFuncST!="declaration"){
                                        yyerror("Multiple Declaration of " + (yyvsp[(2) - (7)].treeNode)->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType!=(yyvsp[(1) - (7)].treeNode)->getSymbolName()){
                                        yyerror("Return type mismatch with function declaration in function "+(yyvsp[(2) - (7)].treeNode)->getSymbolName());
                                        errorCount++;

                                    }
                                    else if(retSymFuncST=="declaration" && retSymType==(yyvsp[(1) - (7)].treeNode)->getSymbolName()){
                                        vector<string> decParamsTypeList = returnedSym->getList1(); //type list of paramsList in declaration
                                        if(decParamsTypeList.size() == paramsList.size()){
                                            bool checker = true;
                                            for(int i=0; i<paramsList.size(); i++){
                                                string _paramType = paramsList[i].first;
                                                if(decParamsTypeList[i]!=_paramType){
                                                    int x = i+1;
                                                    yyerror(x + "th argument mismatch in function "+(yyvsp[(2) - (7)].treeNode)->getSymbolName());
                                                    errorCount++;
                                                    checker = false;
                                                    break;

                                                }
                                            }
                                            if(checker == true){
                                                returnedSym->setFuncSt("definition");
                                            }
                                        }
                                        else{
                                            yyerror("Total number of arguments mismatch with declaration in function "+(yyvsp[(2) - (7)].treeNode)->getSymbolName());
                                            errorCount++;
                                        }
                                        decParamsTypeList.clear();
                                    }
                                }
                                else{
                                    symbolInfo *symbol = new symbolInfo((yyvsp[(2) - (7)].treeNode)->getSymbolName(), "FUNCTION,"+(yyvsp[(1) - (7)].treeNode)->getSymbolName());
                                    int params_no = paramsList.size();
                                    for(int i=0; i<params_no; i++){
                                        string paramsType = paramsList[i].first;
                                        string paramsName = paramsList[i].second;
                                        symbol->insertToList1(paramsType);
                                        symbol->insertToList2(paramsName);
                                    }
                                    symbol->setTypeVar((yyvsp[(1) - (7)].treeNode)->getSymbolName());
                                    symbol->setFuncSt("definition");
                                    //table.insert(symbol);
                                    
                                }

                                (yyval.treeNode) = new symbolInfo("func_definition", "parameter_list error");
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(6) - (7)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(7) - (7)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (7)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(7) - (7)].treeNode)->endLine;
                ;}
    break;

  case 18:
#line 715 "47.y"
    {
                        yyerror("type specifier of func_definition");
                        errorCount++;
                                ErrFunc = false;
                                (yyval.treeNode) = new symbolInfo("func_definition", "error LPAREN");
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(2) - (5)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine;
                ;}
    break;

  case 19:
#line 729 "47.y"
    {
                                string _def = (yyvsp[(1) - (5)].treeNode)->getSymbolName() + " " + (yyvsp[(2) - (5)].treeNode)->getSymbolName() + "()";
                                
                                symbolInfo *returnedSym = table.lookup((yyvsp[(2) - (5)].treeNode)->getSymbolName());
                                for(auto x:func){
                                    if((yyvsp[(2) - (5)].treeNode)->getSymbolName()==x->getSymbolName()){
                                        returnedSym=x;
                                    }
                                }
                                
                                if(returnedSym!=nullptr){
                                    string retSymFuncST = returnedSym->getFuncSt();
                                    string retSymType = returnedSym->getTypeVar();
                                    if(retSymFuncST!="declaration"){
                                        errorCount++;
                                        yyerror("Multiple Declaration of " + (yyvsp[(2) - (5)].treeNode)->getSymbolName());
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType!=(yyvsp[(1) - (5)].treeNode)->getSymbolName()){
                                        yyerror("Return type mismatch with function declaration in function "+(yyvsp[(2) - (5)].treeNode)->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType==(yyvsp[(1) - (5)].treeNode)->getSymbolName()){
                                        vector<string> decParamsTypeList = returnedSym->getList1(); //type list of paramsList in declaration
                                        if(decParamsTypeList.size() == 0){
                                            returnedSym->setFuncSt("definition");     
                                        }
                                        else{
                                            errorCount++;
                                            yyerror("Total number of arguments mismatch with declaration in function "+(yyvsp[(2) - (5)].treeNode)->getSymbolName());
                                        }
                                        decParamsTypeList.clear();
                                    }
                                }
                                else{
                                    symbolInfo *symbol = new symbolInfo((yyvsp[(2) - (5)].treeNode)->getSymbolName(), "FUNCTION,"+(yyvsp[(1) - (5)].treeNode)->getSymbolName());
                                    int params_no = paramsList.size();

                                    symbol->setTypeVar((yyvsp[(1) - (5)].treeNode)->getSymbolName());
                                    symbol->setFuncSt("definition");
                                    table.insert(symbol);
                                }

                                (yyval.treeNode) = new symbolInfo("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
                                
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine;                              
                ;}
    break;

  case 20:
#line 783 "47.y"
    {
                                yyerror("LPAREN of func_definition");
                                errorCount++;
                                string _def = (yyvsp[(1) - (6)].treeNode)->getSymbolName() + " " + (yyvsp[(2) - (6)].treeNode)->getSymbolName() + "()";

                                symbolInfo *returnedSym = table.lookup((yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                if(returnedSym!=nullptr){
                                    string retSymFuncST = returnedSym->getFuncSt();
                                    string retSymType = returnedSym->getTypeVar();
                                    if(retSymFuncST!="declaration"){
                                        yyerror("Multiple Declaration of " + (yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType!=(yyvsp[(1) - (6)].treeNode)->getSymbolName()){
                                        yyerror("Return type mismatch with function declaration in function "+(yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                        errorCount++;

                                    }
                                    else if(retSymFuncST=="declaration" && retSymType==(yyvsp[(1) - (6)].treeNode)->getSymbolName()){
                                        vector<string> decParamsTypeList = returnedSym->getList1(); //type list of paramsList in declaration
                                        if(decParamsTypeList.size() == 0){
                                            returnedSym->setFuncSt("definition");
                                            
                                        }
                                        else{
                                            yyerror("Total number of arguments mismatch with declaration in function "+(yyvsp[(2) - (6)].treeNode)->getSymbolName());
                                            errorCount++;
                                        }
                                        decParamsTypeList.clear();
                                    }
                                }
                                else{
                                    symbolInfo *symbol = new symbolInfo((yyvsp[(2) - (6)].treeNode)->getSymbolName(), "FUNCTION,"+(yyvsp[(1) - (6)].treeNode)->getSymbolName());
                                    int params_no = paramsList.size();

                                    symbol->setTypeVar((yyvsp[(1) - (6)].treeNode)->getSymbolName());
                                    symbol->setFuncSt("definition");
                                    table.insert(symbol);
                                    
                                }
                                (yyval.treeNode) = new symbolInfo("func_definition", "LPAREN error");
                                
                                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (6)].treeNode));
                                (yyval.treeNode)->insertToChildList((yyvsp[(6) - (6)].treeNode));

                                (yyval.treeNode)->startLine=(yyvsp[(1) - (6)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(6) - (6)].treeNode)->endLine; 
                ;}
    break;

  case 21:
#line 835 "47.y"
    {        

                                yyerror("error of func_definition");
                                errorCount++;
                                if(ErrFunc==false){
                                    ErrFunc = true;
                                    paramsList.clear();
                                } 
                                ErrFunc = false;
                                (yyval.treeNode) = new symbolInfo("func_definition", "error compound_statement"); 
                                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));  

                                (yyval.treeNode)->startLine=(yyvsp[(2) - (2)].treeNode)->startLine;
                                (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine; 
                ;}
    break;

  case 22:
#line 851 "47.y"
    {
                        

                      
                        (yyval.treeNode) = new symbolInfo("parameter_list", "parameter_list COMMA type_specifier ID");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (4)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(2) - (4)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (4)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(4) - (4)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (4)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(4) - (4)].treeNode)->endLine; 

                        pair<string, string> newParam;
                        newParam.first = (yyvsp[(3) - (4)].treeNode)->getSymbolName(); //type
                        newParam.second = (yyvsp[(4) - (4)].treeNode)->getSymbolName(); //var_name
                        paramsList.push_back(newParam);
                        //cout<<paramsList.size()<<endl;
                        rulePrint("parameter_list", "parameter_list COMMA type_specifier ID");


                ;}
    break;

  case 23:
#line 874 "47.y"
    {
                        /*
                            Error recovery of parameter_list like:
                            int foo(int a+b, float c)
                        */
                       
                        (yyval.treeNode) = new symbolInfo("parameter_list", "parameter_list error");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine; 
                        
                        yyerror("parameter_list of parameter_list");
                        errorCount++;
                        pair<string, string> newParam;
                        newParam.first = (yyvsp[(4) - (5)].treeNode)->getSymbolName(); //type
                        newParam.second = (yyvsp[(5) - (5)].treeNode)->getSymbolName(); //var_name
                        paramsList.push_back(newParam);

                ;}
    break;

  case 24:
#line 898 "47.y"
    {
 
                        (yyval.treeNode) = new symbolInfo("parameter_list", "parameter_list COMMA type_specifier");   
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine; 
                        
                        pair<string, string> newParam;
                        newParam.first = (yyvsp[(3) - (3)].treeNode)->getSymbolName(); //type
                        newParam.second = ""; //var_name=empty
                        paramsList.push_back(newParam);
                        rulePrint("parameter_list", "parameter_list COMMA type_specifier");

                ;}
    break;

  case 25:
#line 916 "47.y"
    {
                        /*
                            Error recovery of parameter_list like:
                            int foo(int a+b, float)
                        */
                        (yyval.treeNode) = new symbolInfo("parameter_list", "parameter_list error");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (4)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (4)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(4) - (4)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (4)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(4) - (4)].treeNode)->endLine; 

                        yyerror("parameter_list of parameter_list");
                        errorCount++;
                        pair<string, string> newParam;
                        newParam.first = (yyvsp[(4) - (4)].treeNode)->getSymbolName(); //type
                        newParam.second = ""; //var_name=empty
                        paramsList.push_back(newParam);
                        

                ;}
    break;

  case 26:
#line 939 "47.y"
    {   
                        (yyval.treeNode) = new symbolInfo("parameter_list", "type_specifier ID");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (2)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (2)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine; 

                        pair<string, string> newParam;
                        newParam.first = (yyvsp[(1) - (2)].treeNode)->getSymbolName(); //type
                        newParam.second = (yyvsp[(2) - (2)].treeNode)->getSymbolName(); //var_name=empty
                        paramsList.push_back(newParam);
                        rulePrint("parameter_list", "type_specifier ID");
                        
                ;}
    break;

  case 27:
#line 954 "47.y"
    {
                        (yyval.treeNode) = new symbolInfo("parameter_list", "type_specifier");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine; 

                        pair<string, string> newParam;
                        newParam.first = (yyvsp[(1) - (1)].treeNode)->getSymbolName(); //type
                        newParam.second = ""; //var_name=empty
                        paramsList.push_back(newParam);
                        rulePrint("parameter_list", "type_specifier");
                ;}
    break;

  case 28:
#line 968 "47.y"
    {
                           
                        (yyval.treeNode) = new symbolInfo("compound_statement", "LCURL statements RCURL");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (4)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (4)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(4) - (4)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (4)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(4) - (4)].treeNode)->endLine; 


                        rulePrint("compound_statement", "LCURL statements RCURL");
                        table.printAllScope(logout);
                        table.exitScope();
            
                    ;}
    break;

  case 29:
#line 984 "47.y"
    {
                        (yyval.treeNode) = new symbolInfo("compound_statement", "LCURL RCURL");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine; 
                        

                        rulePrint("compound_statement", "LCURL RCURL");
                        table.printAllScope(logout);
                        table.exitScope();
                        
                    ;}
    break;

  case 30:
#line 998 "47.y"
    {
                        (yyval.treeNode) = new symbolInfo("compound_statement", "statements error");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine; 

                        yyerror("statements of compound_statement");
                        errorCount++;
                        table.printAllScope(logout);
                        table.exitScope();
                        
                    ;}
    break;

  case 31:
#line 1013 "47.y"
    {
  
                        (yyval.treeNode) = new symbolInfo("compound_statement", "scopeController error");  
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine; 

                        //rulePrint("compound_statement", "LCURL statements RCURL");
                        table.printAllScope(logout);
                        table.exitScope();
                    
                    ;}
    break;

  case 32:
#line 1030 "47.y"
    {

                table.enterScope();
                for(int i=0; i<paramsList.size(); i++){
                    string _varType = paramsList[i].first;
                    string _name = paramsList[i].second;
                    symbolInfo *symbol = new symbolInfo(_name, "ID");
                    symbol->setTypeVar(_varType);
                    if(table.insert(symbol)==false){
                        yyerror("Multiple Declaration of "+ _name);
                        errorCount++;
                    }
                }
 
                paramsList.clear();

            ;}
    break;

  case 33:
#line 1048 "47.y"
    {
  
                    (yyval.treeNode) = new symbolInfo("var_declaration", "type_specifier declaration_list SEMICOLON");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine; 
                    
                    string varType = (yyvsp[(1) - (3)].treeNode)->getSymbolName();
                    string varName = (yyvsp[(2) - (3)].treeNode)->getSymbolName();

                    // Error check: varType = void
                    if(varType=="void"){
                        string errormsg = "Variable type can't be void";
                        yyerror(errormsg);
                        errorCount++;
                    }
                    else{
                        vector<string> list1 = (yyvsp[(2) - (3)].treeNode)->getList1();
                        vector<string> list2 = (yyvsp[(2) - (3)].treeNode)->getList2();

                        for(int i=0; i<list1.size(); i++){
                            
                            string idType=(yyvsp[(1) - (3)].treeNode)->getSymbolName();
                            if(list2[i]=="[]") idType="ARRAY,"+(yyvsp[(1) - (3)].treeNode)->getSymbolName();
                            symbolInfo *symbol = new symbolInfo(list1[i],idType);
                            symbol->setTypeVar(varType+list2[i]);
                            
                            if(table.insert(symbol)==false){
                                yyerror("Multiple declaration of "+list1[i]);
                                errorCount++;
                            }

                        }

                        
                    }

            
                    rulePrint("var_declaration", "type_specifier declaration_list SEMICOLON");
                ;}
    break;

  case 34:
#line 1092 "47.y"
    {
                    
                    (yyval.treeNode) = new symbolInfo("type_specifier", "INT");     
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine; 
                    
                     rulePrint("type_specifier", "INT");
                ;}
    break;

  case 35:
#line 1102 "47.y"
    {
                   
                    (yyval.treeNode) = new symbolInfo("type_specifier", "FLOAT");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine; 
                    
                    rulePrint("type_specifier", "FLOAT");
                ;}
    break;

  case 36:
#line 1112 "47.y"
    {
                    
                    (yyval.treeNode) = new symbolInfo("type_specifier", "VOID");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine; 
                    
                    rulePrint("type_specifier", "VOID");
                ;}
    break;

  case 37:
#line 1123 "47.y"
    {

                    (yyval.treeNode)=new symbolInfo("declaration_list","declaration_list COMMA ID");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;

                    string new_list = (yyvsp[(1) - (3)].treeNode)->getSymbolName()+ "," + (yyvsp[(3) - (3)].treeNode)->getSymbolName();
                    (yyvsp[(1) - (3)].treeNode)->insertToList1((yyvsp[(3) - (3)].treeNode)->getSymbolName()); //append new id to parent list
                    (yyvsp[(1) - (3)].treeNode)->insertToList2("");
                    (yyvsp[(1) - (3)].treeNode)->setSymbolName(new_list);
                    rulePrint("declaration_list", "declaration_list COMMA ID");
                    table.insert((yyvsp[(3) - (3)].treeNode));
                ;}
    break;

  case 38:
#line 1140 "47.y"
    {
   
                    (yyval.treeNode)=new symbolInfo("declaration_list","declaration_list error");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (4)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (4)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(4) - (4)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (4)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(4) - (4)].treeNode)->endLine;

                    yyerror("declaration_list of variable declaration");
                    errorCount++;
                    string new_list = (yyvsp[(1) - (4)].treeNode)->getSymbolName()+ "," + (yyvsp[(4) - (4)].treeNode)->getSymbolName();
                    (yyvsp[(1) - (4)].treeNode)->insertToList1((yyvsp[(4) - (4)].treeNode)->getSymbolName()); //append new id to parent list
                    (yyvsp[(1) - (4)].treeNode)->insertToList2("");
                    (yyvsp[(1) - (4)].treeNode)->setSymbolName(new_list);
                    

                ;}
    break;

  case 39:
#line 1159 "47.y"
    {
                    (yyval.treeNode)=new symbolInfo("declaration_list","declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(4) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(5) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(6) - (6)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (6)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(6) - (6)].treeNode)->endLine;

                    string new_list = (yyvsp[(1) - (6)].treeNode)->getSymbolName() + "," + (yyvsp[(3) - (6)].treeNode)->getSymbolName() + "[" + (yyvsp[(5) - (6)].treeNode)->getSymbolName() + "]";
                    (yyvsp[(1) - (6)].treeNode)->insertToList1((yyvsp[(3) - (6)].treeNode)->getSymbolName()); //append new id to parent list
                    (yyvsp[(1) - (6)].treeNode)->insertToList2("[]"); //mark as array
                    (yyvsp[(1) - (6)].treeNode)->setSymbolName(new_list);
                    rulePrint("declaration_list", "declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
                    table.insert((yyvsp[(3) - (6)].treeNode));
                    
                ;}
    break;

  case 40:
#line 1179 "47.y"
    {
                    /*
                        Error recovery of declaration_list like:
                        int a+b, c[10];
                    // */
                    (yyval.treeNode)=new symbolInfo("declaration_list","declaration_list error");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (7)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (7)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(4) - (7)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(5) - (7)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(6) - (7)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(7) - (7)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (7)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(7) - (7)].treeNode)->endLine;

                    yyerror("declaration_list of declaration_list");
                    errorCount++;
                    string new_list = (yyvsp[(1) - (7)].treeNode)->getSymbolName() + "," + (yyvsp[(4) - (7)].treeNode)->getSymbolName() + "[" + (yyvsp[(6) - (7)].treeNode)->getSymbolName() + "]";
                    (yyvsp[(1) - (7)].treeNode)->insertToList1((yyvsp[(4) - (7)].treeNode)->getSymbolName()); //append new id to parent list
                    (yyvsp[(1) - (7)].treeNode)->insertToList2("[]"); //mark as array
                    (yyvsp[(1) - (7)].treeNode)->setSymbolName(new_list);
                                  
                ;}
    break;

  case 41:
#line 1203 "47.y"
    {
                    
                    symbolInfo *newSymbol = new symbolInfo("declaration_list", "ID");
                    (yyval.treeNode) = newSymbol;
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                    string new_id = (yyvsp[(1) - (1)].treeNode)->getSymbolName();
                    //$$->insertToList1(new_id); //started a new declaration_list
                    //$$->insertToList2("");
                    rulePrint("declaration_list", "ID");
                    if(!table.lookup((yyvsp[(1) - (1)].treeNode)->getSymbolName())){
                        table.insert((yyvsp[(1) - (1)].treeNode));
                    }
                ;}
    break;

  case 42:
#line 1220 "47.y"
    {
                   
                    symbolInfo *newSymbol = new symbolInfo("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
                    (yyval.treeNode) = newSymbol;
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (4)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (4)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (4)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(4) - (4)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (4)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(4) - (4)].treeNode)->endLine;

                    (yyval.treeNode)->insertToList1((yyvsp[(1) - (4)].treeNode)->getSymbolName()); //started a new declaration_list
                    (yyval.treeNode)->insertToList2("[]");
                    rulePrint("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
                    
                ;}
    break;

  case 43:
#line 1237 "47.y"
    {
        
                    (yyval.treeNode) = new symbolInfo("declaration_list","declaration_list COMMA ID LTHIRD CONST_FLOAT RTHIRD");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(4) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(5) - (6)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(6) - (6)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (6)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(6) - (6)].treeNode)->endLine;
                    
                    string new_list = (yyvsp[(1) - (6)].treeNode)->getSymbolName() + "," + (yyvsp[(3) - (6)].treeNode)->getSymbolName() + "[" + (yyvsp[(5) - (6)].treeNode)->getSymbolName() + "]";
                    (yyvsp[(1) - (6)].treeNode)->insertToList1((yyvsp[(3) - (6)].treeNode)->getSymbolName()); //append new id to parent list
                    (yyvsp[(1) - (6)].treeNode)->insertToList2("[]"); //mark as array
                    (yyvsp[(1) - (6)].treeNode)->setSymbolName(new_list);
                    yyerror("Non-Integer Array Size");
                    errorCount++;      
                ;}
    break;

  case 44:
#line 1257 "47.y"
    {
                    
                    symbolInfo *newSymbol = new symbolInfo("declaration_list", "ID LTHIRD CONST_FLOAT RTHIRD");
                    (yyval.treeNode) = newSymbol;
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (4)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (4)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (4)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(4) - (4)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (4)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(4) - (4)].treeNode)->endLine;

                    (yyval.treeNode)->insertToList1((yyvsp[(1) - (4)].treeNode)->getSymbolName()); //started a new declaration_list
                    (yyval.treeNode)->insertToList2("[]");
                    yyerror("Non-Integer Array Size");
                    errorCount++;
 

                ;}
    break;

  case 45:
#line 1276 "47.y"
    {
                    
                    symbolInfo *newSymbol = new symbolInfo("declaration_list", "ID LSQUARE RSQUARE");
                    (yyval.treeNode) = newSymbol;
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;


                    (yyval.treeNode)->insertToList1((yyvsp[(1) - (3)].treeNode)->getSymbolName()); //started a new declaration_list
                    (yyval.treeNode)->insertToList2("[]");
                    rulePrint("declaration_list", "ID LSQUARE RSQUARE");
                    yyerror("Undefined Array Size");
                    errorCount++;
                    
                ;}
    break;

  case 46:
#line 1296 "47.y"
    {
                   
                    (yyval.treeNode) = new symbolInfo("statements", "statement");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                    rulePrint("statements","statement");
                
           ;}
    break;

  case 47:
#line 1307 "47.y"
    {
                    
                    (yyval.treeNode) = new symbolInfo("statements", "statements statement");
                  
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (2)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (2)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine;

                    rulePrint("statements","statements statement");
                    

           ;}
    break;

  case 48:
#line 1321 "47.y"
    {

                    (yyval.treeNode) = new symbolInfo("statements", "statements error");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;
                    
           ;}
    break;

  case 49:
#line 1333 "47.y"
    {
               
                (yyval.treeNode) = new symbolInfo("statement", "var_declaration");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                
                rulePrint("statement", "var_declaration");

        ;}
    break;

  case 50:
#line 1344 "47.y"
    {
               
                (yyval.treeNode) = new symbolInfo("statement", "expression_statement");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                
                rulePrint("statement", "expression_statement");
        ;}
    break;

  case 51:
#line 1354 "47.y"
    {
              
                (yyval.treeNode) = new symbolInfo("statement", "compound_statement");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                
                rulePrint("statement", "compound_statement");

        ;}
    break;

  case 52:
#line 1365 "47.y"
    {
               
                (yyval.treeNode) = new symbolInfo("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(6) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(7) - (7)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (7)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(7) - (7)].treeNode)->endLine;

                rulePrint("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
                

        ;}
    break;

  case 53:
#line 1383 "47.y"
    {
              
                (yyval.treeNode) = new symbolInfo("statement", "IF LPAREN expression RPAREN statement");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine;

                rulePrint("statement", "IF LPAREN expression RPAREN statement");
                
        ;}
    break;

  case 54:
#line 1398 "47.y"
    {
  
                (yyval.treeNode) = new symbolInfo("statement", "IF LPAREN expression RPAREN statement ELSE statement");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(6) - (7)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(7) - (7)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (7)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(7) - (7)].treeNode)->endLine;

                rulePrint("statement", "IF LPAREN expression RPAREN statement ELSE statement");
                
        ;}
    break;

  case 55:
#line 1415 "47.y"
    {
                //string _stmt = "while(" + $3->getSymbolName() + ") " + $5->getSymbolName();
                (yyval.treeNode) = new symbolInfo("statement", "WHILE LPAREN expression RPAREN statement");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine;

                rulePrint("statement", "WHILE LPAREN expression RPAREN statement");
                

        ;}
    break;

  case 56:
#line 1431 "47.y"
    {

               (yyval.treeNode) = new symbolInfo("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (5)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(5) - (5)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (5)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(5) - (5)].treeNode)->endLine;

                symbolInfo *retSymbol = table.lookup((yyvsp[(3) - (5)].treeNode)->getSymbolName());
                if(retSymbol==nullptr){
                    yyerror("Undeclared Variable: " + (yyvsp[(3) - (5)].treeNode)->getSymbolName());
                    errorCount++;
                }
                rulePrint("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
            
        ;}
    break;

  case 57:
#line 1451 "47.y"
    {
                
                (yyval.treeNode) = new symbolInfo("statement", "RETURN expression SEMICOLON");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;
                
                rulePrint("statement", "RETURN expression SEMICOLON");
  
        ;}
    break;

  case 58:
#line 1465 "47.y"
    {
                            (yyval.treeNode) = new symbolInfo("expression_statement", "SEMICOLON"); 
                            (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                            (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                            (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                            
                            rulePrint("expression_statement", "SEMICOLON");

                    ;}
    break;

  case 59:
#line 1475 "47.y"
    {
                            
                            (yyval.treeNode) = new symbolInfo("expression_statement", "expression SEMICOLON");
                            (yyval.treeNode)->insertToChildList((yyvsp[(1) - (2)].treeNode));
                            (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));

                            (yyval.treeNode)->startLine=(yyvsp[(1) - (2)].treeNode)->startLine;
                            (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine;

                            rulePrint("expression_statement", "expression SEMICOLON");
                            
                    ;}
    break;

  case 60:
#line 1489 "47.y"
    {
                (yyval.treeNode)=new symbolInfo("variable","ID");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                
                string _name = (yyvsp[(1) - (1)].treeNode)->getSymbolName();
                
                symbolInfo *existingVar = table.lookup(_name); //find if variable is declared

                if(existingVar!=nullptr){
                    //$$ = existingVar;
                }
                else{
                    symbolInfo *errorVar = new symbolInfo(_name, "variable");
                    //$$ = errorVar;
                    //$$->setTypeVar("none");
                    string eMsg = "Undeclared Variable '"+ _name +"'";
                    
                    yyerror(eMsg);
                    errorCount++;
                    //cout<<errorVar->getTypeVar()<<endl;
                }
                rulePrint("Variable", "ID");

        ;}
    break;

  case 61:
#line 1516 "47.y"
    {
                (yyval.treeNode)=new symbolInfo("variable","ID LTHIRD expression RTHIRD");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (4)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (4)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (4)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (4)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (4)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(4) - (4)].treeNode)->endLine;

                //fix here    

        ;}
    break;

  case 62:
#line 1529 "47.y"
    {
                (yyval.treeNode)=new symbolInfo("variable"," ID LTHIRD RTHIRD");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;

                string _name = (yyvsp[(1) - (3)].treeNode)->getSymbolName() + "[]";
                symbolInfo *existingVar = table.lookup((yyvsp[(1) - (3)].treeNode)->getSymbolName()); //find if variable is declared
                string existingVarType = existingVar->getTypeVar();
                //string indexType = $3->getTypeVar();
                
                
                if(existingVar!=nullptr){
                    if(existingVarType=="int[]"){
                        (yyval.treeNode)->setTypeVar("int");
                    }
                    else if(existingVarType=="float[]"){
                        (yyval.treeNode)->setTypeVar("float");
                    }
                    else if(existingVarType=="char[]"){
                        (yyval.treeNode)->setTypeVar("char");
                    }
                    else{
                        string eMsg = "Type mismatch. Variable '" + (yyvsp[(1) - (3)].treeNode)->getSymbolName() + "' is not an array";
                        yyerror(eMsg);
                        errorCount++;
                    }
                }
                else{
                    
                    string eMsg = "Undeclared Variable '"+ _name +"'";
                    yyerror(eMsg);
                    errorCount++;
                }
                rulePrint("Variable", "ID LTHIRD RTHIRD");
                yyerror("Invalid Array Index, Array index missing");
                errorCount++;
                
        ;}
    break;

  case 63:
#line 1572 "47.y"
    {
                    (yyval.treeNode) = new symbolInfo("expression","logic_expression");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                    
                    rulePrint("expression","logic_expression");

            ;}
    break;

  case 64:
#line 1582 "47.y"
    {
                            
                    (yyval.treeNode) = new symbolInfo("expression","variable ASSIGNOP logic_expression" );
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;
                   
                    string _exp = (yyvsp[(1) - (3)].treeNode)->getSymbolName() + "=" +(yyvsp[(3) - (3)].treeNode)->getSymbolName();
                    if((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="func_declaration"||(yyvsp[(1) - (3)].treeNode)->getsymbolType()=="func_definition"||(yyvsp[(3) - (3)].treeNode)->getsymbolType()=="func_declaration"||(yyvsp[(3) - (3)].treeNode)->getsymbolType()=="func_definition"){
                        yyerror("= operator can not have function declaration/definition as operands");
                        (yyval.treeNode)->setTypeVar("none");
                        errorCount++;
                    }
                    
                    else if(checkAssignOp((yyvsp[(1) - (3)].treeNode)->getTypeVar(), (yyvsp[(3) - (3)].treeNode)->getTypeVar())==false){
                        //cout<<$1->getTypeVar()<<endl;
                        yyerror("Type mismatch");
                        errorCount++;
                        (yyval.treeNode)->setTypeVar((yyvsp[(1) - (3)].treeNode)->getTypeVar());
                    }
                    else{
                        symbolInfo *syym = table.lookup((yyvsp[(1) - (3)].treeNode)->getSymbolName());
                        if(syym!=nullptr)
                            (yyval.treeNode)->setTypeVar(syym->getTypeVar());
                    }
                    rulePrint("expression", "variable ASSIGNOP logic_expression");
            
            ;}
    break;

  case 65:
#line 1615 "47.y"
    {
                        (yyval.treeNode) = new symbolInfo("logic_expression","rel_expression");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                        
                        rulePrint("logic_expression","rel_expression");

                ;}
    break;

  case 66:
#line 1625 "47.y"
    {
                        (yyval.treeNode) = new symbolInfo("logic_expression", "rel_expression LOGICOP rel_expression");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;

                        string expType = (yyvsp[(1) - (3)].treeNode)->getTypeVar();
                        string expTypeRight = (yyvsp[(3) - (3)].treeNode)->getTypeVar(); 
                        string _exp = (yyvsp[(1) - (3)].treeNode)->getSymbolName() + (yyvsp[(2) - (3)].treeNode)->getSymbolName() + (yyvsp[(3) - (3)].treeNode)->getSymbolName();
                        //cout<<expType<<endl;
                        //cout<<termType<<endl;
     

                        if(expType=="void" || expTypeRight=="void"){
                            yyerror("Void type operand detected!");
                            errorCount++;
                            (yyval.treeNode)->setTypeVar("void");
                        }
                        else{
                            (yyval.treeNode)->setTypeVar("int");
                        }

                        
                        rulePrint("logic_expression", "rel_expression LOGICOP rel_expression");
                       

                ;}
    break;

  case 67:
#line 1656 "47.y"
    {
                        (yyval.treeNode) = new symbolInfo("rel_expression", "simple_expression");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                        
                        rulePrint("rel_expression", "simple_expression");

                ;}
    break;

  case 68:
#line 1666 "47.y"
    {
                        (yyval.treeNode) = new symbolInfo("rel_expression", "simple_expression RELOP simple_expression");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                        (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;
                       
                        string expType = (yyvsp[(1) - (3)].treeNode)->getTypeVar();
                        string expTypeRight = (yyvsp[(3) - (3)].treeNode)->getTypeVar(); 
                        string _exp = (yyvsp[(1) - (3)].treeNode)->getSymbolName() + (yyvsp[(2) - (3)].treeNode)->getSymbolName() + (yyvsp[(3) - (3)].treeNode)->getSymbolName();
                        //cout<<expType<<endl;
                        //cout<<termType<<endl;

                        bool arrayExp = false;
                        bool arrayExpRight = false;
                        
                        if(expType.size()>=2){
                            if(expType[expType.size()-2]=='[' && expType[expType.size()-1]==']'){
                                arrayExp = true;
                            }
                        }

                        if(expTypeRight.size()>=2){
                            if(expTypeRight[expTypeRight.size()-2]=='[' && expTypeRight[expTypeRight.size()-1]==']'){
                                arrayExpRight = true;
                            }
                        }
                        

                        if(expType=="void" || expTypeRight=="void"){
                            yyerror("Void type operand detected!");
                            errorCount++;
                        }
                        else if(arrayExp && arrayExpRight){
                            (yyval.treeNode)->setTypeVar("int");
                        }
                        else if(arrayExp){
                            yyerror("Incompatible Operands");
                            errorCount++;
                        }
                        else if(arrayExpRight){
                            yyerror("Incompatible Operands");
                            errorCount++;
                        }
                        else{
                            (yyval.treeNode)->setTypeVar("int");
                        }
   
                        rulePrint("rel_expression", "simple_expression RELOP simple_expression");

                    
                ;}
    break;

  case 69:
#line 1721 "47.y"
    {
                            (yyval.treeNode) = new symbolInfo("simple_expression", "term");
                            (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                            (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                            (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                            
                            rulePrint("simple_expression", "term");
                            
                    ;}
    break;

  case 70:
#line 1731 "47.y"
    {
                            
                            (yyval.treeNode)=new symbolInfo("simple_expression","simple_expression ADDOP term");
                            (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                            (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                            (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                            (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                            (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;

                            string expType = (yyvsp[(1) - (3)].treeNode)->getTypeVar();
                            string termType = (yyvsp[(3) - (3)].treeNode)->getTypeVar();
                            string _exp = (yyvsp[(1) - (3)].treeNode)->getSymbolName() + (yyvsp[(2) - (3)].treeNode)->getSymbolName() + (yyvsp[(3) - (3)].treeNode)->getSymbolName();
                            //cout<<expType<<endl;
                            //cout<<termType<<endl;

                            bool arrayExp = false;
                            bool arrayTerm = false;
                            
                            if(expType.size()>=2){
                                if(expType[expType.size()-2]=='[' && expType[expType.size()-1]==']'){
                                    arrayExp = true;
                                }
                            }

                            if(termType.size()>=2){
                                if(termType[termType.size()-2]=='[' && termType[termType.size()-1]==']'){
                                    arrayTerm = true;
                                }
                            }

                            if(expType=="void" || termType=="void"){
                                yyerror("Void type operand detected!");
                                errorCount++;
                                
                            }
                            else if(arrayExp && termType=="int"){
                                (yyval.treeNode)->setTypeVar(expType);
                            }
                            else if(expType=="int" && arrayTerm){
                                (yyval.treeNode)->setTypeVar(termType);
                            }
                            else if(arrayExp || arrayTerm){
                                yyerror("Incompatible Operands");
                                errorCount++;
                            }
                            else if(expType=="float" || termType=="float"){
                                (yyval.treeNode)->setTypeVar("float");
                            }
                            else{
                                (yyval.treeNode)->setTypeVar("int");
                            }
                            

                            
                            rulePrint("simple_expression", "simple_expression ADDOP term");
                           
                    ;}
    break;

  case 71:
#line 1790 "47.y"
    {
                (yyval.treeNode) = new symbolInfo("term", "unary_expression");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                (yyval.treeNode)->setTypeVar((yyvsp[(1) - (1)].treeNode)->getTypeVar());
                
                rulePrint("term", "unary_expression");
     ;}
    break;

  case 72:
#line 1801 "47.y"
    {
                
                (yyval.treeNode) = new symbolInfo("term", "term MULOP unary_expression");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;

                
                string expType = (yyvsp[(3) - (3)].treeNode)->getTypeVar(); //unary_expression type
                string termType = (yyvsp[(1) - (3)].treeNode)->getTypeVar();
                string _term = (yyvsp[(1) - (3)].treeNode)->getSymbolName() + (yyvsp[(2) - (3)].treeNode)->getSymbolName() + (yyvsp[(3) - (3)].treeNode)->getSymbolName();
                //cout<<_term<<endl;
                //cout<<termType<<endl;
                //cout<<expType<<endl;

                bool arrayExp = false;
                bool arrayTerm = false;
                
                if(expType.size()>=2){
                    if(expType[expType.size()-2]=='[' && expType[expType.size()-1]==']'){
                        arrayExp = true;
                    }
                }

                if(termType.size()>=2){
                    if(termType[termType.size()-2]=='[' && termType[termType.size()-1]==']'){
                        arrayTerm = true;
                    }
                }
                

                if(termType=="void" || expType=="void"){
                    yyerror("Void type operand detected!");
                    errorCount++;
                }
                else if(arrayTerm || arrayExp){
                    yyerror("Incompatible Operands");
                    errorCount++;
                }
                else if((termType!="int" || expType!="int") && (yyvsp[(2) - (3)].treeNode)->getSymbolName()=="%"){
                    yyerror("Modulus operator cannot have non-integer operands");
                    (yyval.treeNode)->setTypeVar("int");
                    errorCount++;
                }
                else if(((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="%") && (yyvsp[(3) - (3)].treeNode)->getSymbolName()=="0"){
                    yyerror("Modulus by Zero");
                    errorCount++;
                    (yyval.treeNode)->setTypeVar("int");
                }
                else if(termType=="float" || expType=="float"){
                    (yyval.treeNode)->setTypeVar("float");
                }
                else{
                    (yyval.treeNode)->setTypeVar("int");
                }

                rulePrint("term", "term MULOP unary_expression");

     ;}
    break;

  case 73:
#line 1864 "47.y"
    {


                    (yyval.treeNode) = new symbolInfo("unary_expression", "ADDOP unary_expression");  
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (2)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (2)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine;

                    string _exp = (yyvsp[(1) - (2)].treeNode)->getSymbolName() + (yyvsp[(2) - (2)].treeNode)->getSymbolName();
                    string _expType = (yyvsp[(2) - (2)].treeNode)->getTypeVar();
                    if(_expType=="void"){
                        yyerror("Void type operand detected!");
                        errorCount++;
                    }

                    (yyval.treeNode)->setTypeVar(_expType);
                    rulePrint("unary_expression", "ADDOP unary_expression");
                    

                ;}
    break;

  case 74:
#line 1886 "47.y"
    {
   
                    (yyval.treeNode) = new symbolInfo("unary_expression", "NOT unary_expression");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (2)].treeNode));
                    (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (2)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine;

                    string _exp = "!" + (yyvsp[(2) - (2)].treeNode)->getSymbolName();
                    string _expType = (yyvsp[(2) - (2)].treeNode)->getTypeVar();
                    if(_expType=="void"){
                        yyerror("Void type operand detected!");
                        errorCount++;
                    }
                    (yyval.treeNode)->setTypeVar(_expType);

                    rulePrint("unary_expression", "NOT unary_expression");
                    
                ;}
    break;

  case 75:
#line 1906 "47.y"
    {
                        (yyval.treeNode) = new symbolInfo("unary_expression", "factor");
                        (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                        (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                        (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                        
                        (yyval.treeNode)->setTypeVar((yyvsp[(1) - (1)].treeNode)->getTypeVar());
                        rulePrint("unary_expression", "factor");
                        
                ;}
    break;

  case 76:
#line 1918 "47.y"
    {
                (yyval.treeNode) = new symbolInfo("factor", "variable");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;
                
                rulePrint("factor", "variable");   

        ;}
    break;

  case 77:
#line 1928 "47.y"
    {

                (yyval.treeNode) = new symbolInfo("factor", "ID LPAREN argument_list RPAREN");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (4)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (4)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (4)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(4) - (4)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (4)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(4) - (4)].treeNode)->endLine;

                string _id = (yyvsp[(1) - (4)].treeNode)->getSymbolName();
                
                //cout<<"factor"<<$$->getTypeVar()<<endl;
                
                symbolInfo *declaredFunc = table.lookup(_id);

                // for(auto x:func){
                //     if(x->getSymbolName()==_id){
                //         declaredFunc=x;
                //         cout<<x->getSymbolName()<<endl;
                //         break;
                //     }
                // }
                string declaredFunc_st;
                if(declaredFunc!=nullptr){
                    declaredFunc_st = declaredFunc->getFuncSt();
                    (yyval.treeNode)->setTypeVar(declaredFunc->getTypeVar());
                }

                if(declaredFunc==nullptr){
                    yyerror("Undeclared Function: " + _id);
                    errorCount++;
                }
                else if(declaredFunc_st!="declaration" && declaredFunc_st!="definition"){ //eta function na
                    yyerror(_id + " not a function");
                    errorCount++;
                }
                else{
                    vector<string> expectedTypes = declaredFunc->getList1();
                    //if(declaredFunc->getSymbolName()=="var")
                    //cout<<"expected:"<<expectedTypes.size()<<endl;
                    vector<string> argTypes = (yyvsp[(3) - (4)].treeNode)->getList1();
                    int _expSize = expectedTypes.size();
                    int _argSize = argTypes.size();
                    //if(declaredFunc->getSymbolName()=="var")
                    //cout<<"arg size:"<<_argSize<<endl;
  
                    if(_expSize!=_argSize){
                        yyerror("Total number of arguments mismatch in function "+ _id);
                        errorCount++;
                    }
                    else{
                        for(int i=0; i<_argSize; i++){
                            //string intt = "int";
                            //string floatt = "float";
                            if(expectedTypes[i]=="int" && argTypes[i]!="int"){
                                string eMsg = to_string(i+1) + "th argument mismatch in function "+_id;
                                //string eMsg = "th argument mismatch in function";
                                yyerror(eMsg);
                                errorCount++;
                                //cout<<expectedTypes[i]<<" "<<argTypes[i]<<endl;
                            }
                            else if(expectedTypes[i]=="float" && argTypes[i]!="float" && argTypes[i]!="int"){
                                string eMsg = to_string(i+1) + "th argument mismatch in function "+_id;
                                //string eMsg = "th argument mismatch in function";
                                yyerror(eMsg);
                                errorCount++;
                            }
                        }
                    }
                    
                }

                rulePrint("factor", "ID LPAREN argument_list RPAREN");
               

        ;}
    break;

  case 78:
#line 2006 "47.y"
    {
 
                (yyval.treeNode) = new symbolInfo("factor", "LPAREN expression RPAREN");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (3)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(3) - (3)].treeNode)->endLine;

                string expType = (yyvsp[(2) - (3)].treeNode)->getTypeVar();
                (yyval.treeNode)->setTypeVar(expType);
                rulePrint("factor", "LPAREN expression RPAREN");
                

        ;}
    break;

  case 79:
#line 2020 "47.y"
    {
              
                (yyval.treeNode) = new symbolInfo("CONST_INT",(yyvsp[(1) - (1)].treeNode)->getSymbolName());
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                (yyval.treeNode)->setTypeVar("int");
                rulePrint("factor", "CONST_INT");
               

        ;}
    break;

  case 80:
#line 2033 "47.y"
    {
               
                (yyval.treeNode) = new symbolInfo("CONST_FLOAT",(yyvsp[(1) - (1)].treeNode)->getSymbolName());
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                (yyval.treeNode)->setTypeVar("float");
                rulePrint("factor", "CONST_FLOAT");
            

        ;}
    break;

  case 81:
#line 2046 "47.y"
    {

                (yyval.treeNode) = new symbolInfo("factor", "variable INCOP");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (2)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (2)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine;

                string _factr = (yyvsp[(1) - (2)].treeNode)->getSymbolName() + "++";
                string varType = (yyvsp[(1) - (2)].treeNode)->getTypeVar();
                if(varType == "void"){
                    yyerror("Invalid Operand Type for ++ operator");
                    errorCount++;
                }
                (yyval.treeNode)->setTypeVar(varType);
                rulePrint("factor", "variable INCOP");
               

        ;}
    break;

  case 82:
#line 2066 "47.y"
    {
  
                (yyval.treeNode) = new symbolInfo("factor", "variable DECOP");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (2)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (2)].treeNode));

                (yyval.treeNode)->startLine=(yyvsp[(1) - (2)].treeNode)->startLine;
                (yyval.treeNode)->endLine=(yyvsp[(2) - (2)].treeNode)->endLine;

                string _factr = (yyvsp[(1) - (2)].treeNode)->getSymbolName() + "--";
                string varType = (yyvsp[(1) - (2)].treeNode)->getTypeVar();
                if(varType == "void"){
                    yyerror("Invalid Operand Type for -- operator");
                    errorCount++;
                }
                (yyval.treeNode)->setTypeVar(varType);
                rulePrint("factor", "variable DECOP");
                
        ;}
    break;

  case 83:
#line 2086 "47.y"
    {
                   
                    (yyval.treeNode) = new symbolInfo("argument_list", "arguments");
                    (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                    (yyval.treeNode)->startLine=(yyvsp[(1) - (1)].treeNode)->startLine;
                    (yyval.treeNode)->endLine=(yyvsp[(1) - (1)].treeNode)->endLine;

                    string _argmnts = (yyvsp[(1) - (1)].treeNode)->getSymbolName();
                    vector<string> argTypeList = (yyvsp[(1) - (1)].treeNode)->getList1();
                    for(int i=0; i<argTypeList.size(); i++){
                        (yyval.treeNode)->insertToList1(argTypeList[i]);
                    }
                    //$$->insertToList1($3->getTypeVar());
                    rulePrint("argument_list", "arguments");
                   
              ;}
    break;

  case 84:
#line 2103 "47.y"
    {
                    (yyval.treeNode) = new symbolInfo("argument_list", "");
                    rulePrint("argument_list", "");

              ;}
    break;

  case 85:
#line 2109 "47.y"
    {
                (yyval.treeNode) = new symbolInfo("arguments", "arguments COMMA logic_expression");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (3)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(2) - (3)].treeNode));
                (yyval.treeNode)->insertToChildList((yyvsp[(3) - (3)].treeNode));

                string _argmnts = (yyvsp[(1) - (3)].treeNode)->getSymbolName() + "," + (yyvsp[(3) - (3)].treeNode)->getSymbolName();
                vector<string> argTypeList = (yyvsp[(1) - (3)].treeNode)->getList1();
                for(int i=0; i<argTypeList.size(); i++){
                    (yyval.treeNode)->insertToList1(argTypeList[i]);
                }
                (yyval.treeNode)->insertToList1((yyvsp[(3) - (3)].treeNode)->getTypeVar());
                rulePrint("arguments", "arguments COMMA logic_expression");
                
          ;}
    break;

  case 86:
#line 2124 "47.y"
    {
                   
                (yyval.treeNode) = new symbolInfo("arguments", "logic_expression");
                (yyval.treeNode)->insertToChildList((yyvsp[(1) - (1)].treeNode));

                string _argmnts = (yyvsp[(1) - (1)].treeNode)->getSymbolName();
                rulePrint("arguments", "logic_expression");
                
          ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3974 "47.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 2135 "47.y"


int main(int argc,char *argv[])
{

	if(argc!=2) {
		cout << "Please provide input file name and try again\n";
		return 0;
	}

	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL) {
		cout << "Cannot open specified file\n";
		return 0;
	}

	yyin = fin;
	
	

	yyparse();
	
	fclose(yyin);
    table.printAllScope(logout);
    fprintf(logout, "Total Lines: %d\n", line_count);
    fprintf(logout, "Total Errors: %d\n", errorCount);
    fprintf(errorout, "Total Errors: %d\n", errorCount);
	fclose(logout);
	fclose(errorout);
    fclose(parseout);
	
	return 0;
}

