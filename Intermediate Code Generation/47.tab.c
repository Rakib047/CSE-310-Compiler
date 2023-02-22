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
FILE *asmout= fopen("code.asm","w");
FILE *tempasmout= fopen("temp.asm","w");

ifstream unoptimized;
ofstream optimized;
//offline 4 code
vector<string> lineVector(1000);
int tempCount=0;
int labelCount=0;
int currentOffset=0; // offset from BP of that particular variable
int parameterCount=0;
bool isMainDefined=false;
string currentFunc="";
string globalVar="";


vector<string> split(const string &s){
    vector<string> elements;
    string item = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ' || s[i] == ',' || s[i] == '\t') {
            if (item != "") {
                elements.push_back(item);
                item = "";
            }
        }
        else {
            item += s[i];
        }
    }

    if (item != "") {
        elements.push_back(item);
    }

    return elements;
}

void resetCurrentOffset(){
	currentOffset=0;
}

string newTemp() {
	return "temp_"+to_string(tempCount++);
}

string newLabel() {
	return "L"+to_string(labelCount++);
}

int ifCount=0;
int whileCount=0;
int forCount=0;

stack<int> ifCountStack;
stack<int> whileCountStack;
stack<int> forCountStack;


void printUtilFunctions() {
	fprintf(tempasmout, "\nPRINT PROC ; PRINTS A WORD INTEGER IN AX\n\
	LEA SI, NUMBER_STRING ; IS 00000\n\
    ADD SI, 5 ; START FROM ONE'S DIGIT\n\
    CMP AX, 0\n\
    JNL PRINT_LOOP\n\
    MOV FLAG, 1\n\
    NEG AX\n\
    PRINT_LOOP:\n\
        DEC SI\n\
        MOV DX, 0 ; DX:AX = 0000:AX\n\
        MOV CX, 10\n\
        DIV CX\n\
        ADD DL, '0'\n\
        MOV [SI], DL\n\
        CMP AX, 0\n\
        JNE PRINT_LOOP\n\
    CMP FLAG, 0\n\
    JNG NOT_NEGATIVE\n\
    MOV AH, 2\n\
    MOV DL, 45\n\
    INT 21H\n\
    MOV FLAG, 0\n\
	NOT_NEGATIVE:\n\
    MOV DX, SI\n\
    MOV AH, 9\n\
    INT 21H\n\
	MOV DX, OFFSET NL   ; NEWLINE\n\
    MOV AH, 9\n\
    INT 21H\n\
    RET\n\
PRINT ENDP\n");
}



vector<string> v;
vector<string> parameterTypeList;
vector<string> parameterNameList;
vector<symbolInfo*>p;
string returnTypeToMatch;

void split(const string s, char delim) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        v.push_back(item);
    }
}

string getArrayName(const string s){
	stringstream ss(s);
	string item;
	while(getline(ss, item, '['))
		return item;
}

int getArraySize(const string s){
	stringstream ss(s);
	string item;
	if(getline(ss, item, '[')){}
	while(getline(ss, item, ']'))
		return stoi(item);
    return 0;
}

void splitParameterTypeList(const string s, char delim) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        parameterTypeList.push_back(item);
    }
}

void extractParameterNameList(const string s, char delim) {
    bool flag;
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        flag=true;
        stringstream ss2(item);
		string paramName;
		if(getline(ss2, paramName, ' ')) {}
        if(getline(ss2, paramName, ' ')) {
            for(string str : parameterNameList){
                if(paramName==str){
                    // multiple parameter same error
					//errorCount++;
					//fprintf(errorout, "Error at line %d: Multiple declaration of %s in parameter\n\n", lineCount, paramName.c_str());
					//fprintf(logout, "Error at line %d: Multiple declaration of %s in parameter\n\n", lineCount, paramName.c_str());
                    flag=false;
                }
            }
			// if(flag)
				parameterNameList.push_back(paramName);
		}
    }
}

void clearVector() {
	v.clear();
}

void clearParameterTypeList() {
	parameterTypeList.clear();
}

void clearParameterNameList() {
	parameterNameList.clear();
}


int yyparse(void);
int yylex(void);


extern int line_count;
extern int errorCount;
extern FILE* yyin;



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




void rulePrint(string leftTerm, string rightTerm){
    //fprintf(logout, "Line# %d: %s : %s\n\n", line_count, leftTerm.c_str(), rightTerm.c_str());
    fprintf(logout, "%s : %s\n", leftTerm.c_str(), rightTerm.c_str());
}



void printTree(symbolInfo* head,string space){
    //cout<<space<<head->getSymbolName()<<":"<<head->getsymbolType()<<endl;

    if(head->leaf){
        fprintf(parseout, "%s%s", space.c_str(), head->rule.c_str());
    }
    else{
    fprintf(parseout, "%s%s", space.c_str(), head->parseRule.c_str());
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

void optimizeCode(){
	string line, nextLine;
	vector<string> portions, nextPortions;
	lineVector.clear();
	unoptimized.open("code.asm");
	optimized.open("optimized_code.asm");
	
	while (getline (unoptimized,line)) 
		lineVector.push_back(line);
    
	if(lineVector.size()==0) {
		unoptimized.close();
		optimized.close();	
	}

    for (int i = 0; i < lineVector.size()-1; i++)
    {
        if((split(lineVector[i]).size()==0))
            continue;
        if((split(lineVector[i])[0].find(";") != string::npos))
            continue;
        
        line=lineVector[i];
        nextLine=lineVector[i+1];
        portions=split(line);
        nextPortions=split(nextLine);
		if(portions[0]=="PUSH"){
            if(nextPortions[0]=="POP"){ 
                if(portions[1]==nextPortions[1]){ // PUSH AX ; POP AX
                    lineVector[i]=";"+lineVector[i];
                    lineVector[i+1]=";"+lineVector[i+1];
                }
                else { // PUSH 7 ; POP AX
                    lineVector[i]=";"+lineVector[i];
                    lineVector[i+1]="MOV "+nextPortions[1]+", "+portions[1];
                }
            }
        } 

        if(portions[0]=="MOV"){
            if(portions[1]==portions[2]){ // MOV AX, AX
                lineVector[i]=";"+lineVector[i];
            }
            if(nextPortions[0]=="MOV"){ 
                if((portions[1]==nextPortions[2]) && (portions[2]==nextPortions[1])){ // MOV AX, BX ; MOV BX, AX
                    lineVector[i+1]=";"+lineVector[i+1];
                }
                if(portions[1]==nextPortions[1]){ // MOV AX, BX ; MOV AX, CX
                    lineVector[i]=";"+lineVector[i];
                }
            }
        }


    }


    for (int i = 0; i < lineVector.size(); i++)
    	optimized<<lineVector[i]<<endl;
    
	
	unoptimized.close();
	optimized.close();
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
#line 325 "47.y"
{
    symbolInfo* treeNode;
}
/* Line 193 of yacc.c.  */
#line 502 "47.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 515 "47.tab.c"

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   187

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  130

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
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,    10,    12,    14,    16,    18,
      25,    31,    32,    40,    41,    48,    53,    57,    60,    62,
      67,    71,    72,    76,    78,    80,    82,    86,    93,    95,
     100,   102,   105,   107,   109,   111,   112,   113,   114,   125,
     128,   129,   135,   136,   137,   145,   151,   155,   160,   162,
     165,   167,   172,   176,   178,   182,   184,   188,   190,   194,
     196,   200,   202,   206,   209,   212,   214,   216,   221,   225,
     227,   229,   232,   235,   237,   238,   242
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    -1,    43,    44,    -1,    44,    45,    -1,
      45,    -1,    53,    -1,    46,    -1,    47,    -1,    54,    38,
      30,    50,    31,    37,    -1,    54,    38,    30,    31,    37,
      -1,    -1,    54,    38,    30,    50,    31,    48,    51,    -1,
      -1,    54,    38,    30,    31,    49,    51,    -1,    50,    36,
      54,    38,    -1,    50,    36,    54,    -1,    54,    38,    -1,
      54,    -1,    32,    52,    56,    33,    -1,    32,    52,    33,
      -1,    -1,    54,    55,    37,    -1,     9,    -1,    11,    -1,
      13,    -1,    55,    36,    38,    -1,    55,    36,    38,    34,
      19,    35,    -1,    38,    -1,    38,    34,    19,    35,    -1,
      57,    -1,    56,    57,    -1,    53,    -1,    65,    -1,    51,
      -1,    -1,    -1,    -1,     5,    30,    65,    58,    65,    59,
      67,    31,    60,    57,    -1,    64,    57,    -1,    -1,    64,
      57,     4,    61,    57,    -1,    -1,    -1,     6,    62,    30,
      67,    31,    63,    57,    -1,    39,    30,    38,    31,    37,
      -1,    14,    67,    37,    -1,     3,    30,    67,    31,    -1,
      37,    -1,    67,    37,    -1,    38,    -1,    38,    34,    67,
      35,    -1,    38,    34,    35,    -1,    68,    -1,    66,    27,
      68,    -1,    69,    -1,    69,    28,    69,    -1,    70,    -1,
      70,    26,    70,    -1,    71,    -1,    70,    22,    71,    -1,
      72,    -1,    71,    23,    72,    -1,    22,    72,    -1,    29,
      72,    -1,    73,    -1,    66,    -1,    38,    30,    74,    31,
      -1,    30,    67,    31,    -1,    19,    -1,    20,    -1,    66,
      24,    -1,    66,    25,    -1,    75,    -1,    -1,    75,    36,
      68,    -1,    68,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   342,   342,   342,   353,   357,   363,   367,   372,   378,
     401,   420,   419,   485,   484,   546,   550,   554,   558,   566,
     576,   584,   605,   669,   673,   677,   683,   688,   696,   701,
     712,   716,   723,   728,   733,   737,   741,   748,   737,   759,
     765,   765,   775,   781,   774,   792,   806,   824,   834,   838,
     845,   872,   896,   915,   919,   955,   959,   984,   988,  1027,
    1031,  1050,  1054,  1087,  1100,  1112,  1118,  1124,  1164,  1169,
    1174,  1178,  1190,  1203,  1208,  1214,  1219
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
  "@1", "program", "unit", "func_declaration", "func_definition", "@2",
  "@3", "parameter_list", "compound_statement", "scopeController",
  "var_declaration", "type_specifier", "declaration_list", "statements",
  "statement", "@4", "@5", "@6", "@7", "@8", "@9", "if_expr",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", 0
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
       0,    41,    43,    42,    44,    44,    45,    45,    45,    46,
      46,    48,    47,    49,    47,    50,    50,    50,    50,    51,
      51,    52,    53,    54,    54,    54,    55,    55,    55,    55,
      56,    56,    57,    57,    57,    58,    59,    60,    57,    57,
      61,    57,    62,    63,    57,    57,    57,    64,    65,    65,
      66,    66,    66,    67,    67,    68,    68,    69,    69,    70,
      70,    71,    71,    72,    72,    72,    73,    73,    73,    73,
      73,    73,    73,    74,    74,    75,    75
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     1,     1,     1,     1,     6,
       5,     0,     7,     0,     6,     4,     3,     2,     1,     4,
       3,     0,     3,     1,     1,     1,     3,     6,     1,     4,
       1,     2,     1,     1,     1,     0,     0,     0,    10,     2,
       0,     5,     0,     0,     7,     5,     3,     4,     1,     2,
       1,     4,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     2,     2,     1,     1,     4,     3,     1,
       1,     2,     2,     1,     0,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,    23,    24,    25,     3,     5,     7,
       8,     6,     0,     4,    28,     0,     0,     0,     0,    22,
      13,     0,    18,     0,    26,    10,     0,    11,     0,    17,
      29,     0,    21,    14,     9,     0,    16,     0,     0,    12,
      15,    27,     0,     0,    42,     0,    69,    70,     0,     0,
       0,    20,    48,    50,     0,    34,    32,     0,     0,    30,
       0,    33,    66,     0,    53,    55,    57,    59,    61,    65,
       0,     0,     0,     0,    66,    63,    64,     0,    74,     0,
       0,    28,    19,    31,    39,    71,    72,     0,    49,     0,
       0,     0,     0,     0,    35,     0,    46,    68,    76,     0,
      73,    52,     0,     0,    40,    54,    56,    60,    58,    62,
      47,     0,     0,    67,     0,    51,     0,     0,    36,    43,
      75,    45,    41,     0,     0,     0,    44,    37,     0,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     7,     8,     9,    10,    35,    26,    21,
      55,    38,    56,    57,    15,    58,    59,   111,   123,   128,
     117,    72,   124,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    99,   100
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -72
static const yytype_int16 yypact[] =
{
     -72,    36,    46,   -72,   -72,   -72,   -72,    46,   -72,   -72,
     -72,   -72,   -32,   -72,    11,    25,     6,   -11,    27,   -72,
      21,   -10,    28,    33,    35,   -72,    38,    37,    46,   -72,
     -72,    53,   -72,   -72,   -72,    38,    48,    40,    74,   -72,
     -72,   -72,    43,    59,   -72,    99,   -72,   -72,    99,    99,
      99,   -72,   -72,    14,    60,   -72,   -72,    57,   111,   -72,
     148,   -72,     8,    61,   -72,    71,    -2,    78,   -72,   -72,
      99,     9,    72,    68,    39,   -72,   -72,    77,    99,    62,
      85,    75,   -72,   -72,   106,   -72,   -72,    99,   -72,    99,
      99,    99,    99,    84,   -72,    99,   -72,   -72,   -72,    95,
      91,   -72,    97,   103,   -72,   -72,   -72,    78,   113,   -72,
     -72,     9,   105,   -72,    99,   -72,   101,   148,   -72,   -72,
     -72,   -72,   -72,    99,   148,   108,   -72,   -72,   148,   -72
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -72,   -72,   -72,   -72,   135,   -72,   -72,   -72,   -72,   -72,
     -12,   -72,    20,     2,   -72,   -72,   -57,   -72,   -72,   -72,
     -72,   -72,   -72,   -72,   -69,   -38,   -45,   -71,    56,    55,
      65,   -36,   -72,   -72,   -72
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      73,    83,    94,    84,    12,    77,    14,    98,    23,    12,
      74,    74,    75,    76,    33,     4,   105,     5,    22,     6,
      90,    27,    11,    39,    91,    93,    28,    11,    46,    47,
      36,    48,    85,    86,   102,    87,     3,    20,    49,    50,
      74,    16,   118,   120,    78,    17,    52,    53,    79,    74,
     112,    74,    74,    74,    74,     4,   109,     5,    25,     6,
     122,    18,    19,    85,    86,    24,    29,   126,    30,    31,
      32,   129,    37,    70,    34,    41,    74,    42,   125,    43,
      44,    46,    47,     4,    48,     5,    40,     6,    45,    71,
      80,    49,    50,    46,    47,    81,    48,   101,    88,    89,
      53,    92,    95,    49,    50,    96,    32,    51,    97,    17,
     104,    52,    53,    54,    42,   110,    43,    44,    46,    47,
       4,    48,     5,   103,     6,    45,   113,   114,    49,    50,
      46,    47,   115,    48,   116,    90,   119,    53,   121,   127,
      49,    50,    13,    32,    82,   106,   108,     0,    52,    53,
      54,    42,     0,    43,    44,   107,     0,     4,     0,     5,
       0,     6,    45,     0,     0,     0,     0,    46,    47,     0,
      48,     0,     0,     0,     0,     0,     0,    49,    50,     0,
      32,     0,     0,     0,     0,    52,    53,    54
};

static const yytype_int16 yycheck[] =
{
      45,    58,    71,    60,     2,    50,    38,    78,    19,     7,
      48,    49,    48,    49,    26,     9,    87,    11,    16,    13,
      22,    31,     2,    35,    26,    70,    36,     7,    19,    20,
      28,    22,    24,    25,    79,    27,     0,    31,    29,    30,
      78,    30,   111,   114,    30,    34,    37,    38,    34,    87,
      95,    89,    90,    91,    92,     9,    92,    11,    37,    13,
     117,    36,    37,    24,    25,    38,    38,   124,    35,    34,
      32,   128,    19,    30,    37,    35,   114,     3,   123,     5,
       6,    19,    20,     9,    22,    11,    38,    13,    14,    30,
      30,    29,    30,    19,    20,    38,    22,    35,    37,    28,
      38,    23,    30,    29,    30,    37,    32,    33,    31,    34,
       4,    37,    38,    39,     3,    31,     5,     6,    19,    20,
       9,    22,    11,    38,    13,    14,    31,    36,    29,    30,
      19,    20,    35,    22,    31,    22,    31,    38,    37,    31,
      29,    30,     7,    32,    33,    89,    91,    -1,    37,    38,
      39,     3,    -1,     5,     6,    90,    -1,     9,    -1,    11,
      -1,    13,    14,    -1,    -1,    -1,    -1,    19,    20,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    -1,
      32,    -1,    -1,    -1,    -1,    37,    38,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    42,    43,     0,     9,    11,    13,    44,    45,    46,
      47,    53,    54,    45,    38,    55,    30,    34,    36,    37,
      31,    50,    54,    19,    38,    37,    49,    31,    36,    38,
      35,    34,    32,    51,    37,    48,    54,    19,    52,    51,
      38,    35,     3,     5,     6,    14,    19,    20,    22,    29,
      30,    33,    37,    38,    39,    51,    53,    54,    56,    57,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      30,    30,    62,    67,    66,    72,    72,    67,    30,    34,
      30,    38,    33,    57,    57,    24,    25,    27,    37,    28,
      22,    26,    23,    67,    65,    30,    37,    31,    68,    74,
      75,    35,    67,    38,     4,    68,    69,    71,    70,    72,
      31,    58,    67,    31,    36,    35,    31,    61,    65,    31,
      68,    37,    57,    59,    63,    67,    57,    31,    60,    57
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
#line 342 "47.y"
    {
		fprintf(asmout, ".MODEL SMALL\n");
		fprintf(asmout, "\n.STACK 1000H\n");
		fprintf(asmout, "\n.DATA\n\nFLAG DB 0\nNL DB 13,10,\"$\"\nNUMBER_STRING DB \"00000$\" \n");
		fprintf(tempasmout, "\n.CODE\n");
	;}
    break;

  case 3:
#line 347 "47.y"
    {
		printUtilFunctions();
		if(isMainDefined) fprintf(tempasmout, "END MAIN\n");
	;}
    break;

  case 4:
#line 354 "47.y"
    {
		(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (2)].treeNode)->getSymbolName()+"\n"+(yyvsp[(2) - (2)].treeNode)->getSymbolName(),"program");
	;}
    break;

  case 5:
#line 358 "47.y"
    {
		(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
	;}
    break;

  case 6:
#line 364 "47.y"
    {
		(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
	;}
    break;

  case 7:
#line 368 "47.y"
    {
		(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
		
	;}
    break;

  case 8:
#line 373 "47.y"
    {
		(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
	;}
    break;

  case 9:
#line 379 "47.y"
    {
			string returnType = (yyvsp[(1) - (6)].treeNode)->getSymbolName();
			string funcName = (yyvsp[(2) - (6)].treeNode)->getSymbolName();
			symbolInfo* temp = table.lookup(funcName);
			if (temp!=nullptr)
			{

			}
			else {
				splitParameterTypeList((yyvsp[(4) - (6)].treeNode)->getsymbolType(), ',');


				symbolInfo* f= new symbolInfo(funcName, returnType,"FUNCTION");
				for(string parameterType : parameterTypeList)
					f->addParameter(parameterType);
				table.insert(f);
				clearParameterTypeList();
			}
			table.enterScope();table.exitScope(); // dummy scope for declaration
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (6)].treeNode)->getSymbolName()+" "+(yyvsp[(2) - (6)].treeNode)->getSymbolName()+"("+(yyvsp[(4) - (6)].treeNode)->getSymbolName()+");","func_declaration");
			
		;}
    break;

  case 10:
#line 402 "47.y"
    {
			string returnType = (yyvsp[(1) - (5)].treeNode)->getSymbolName();
			string funcName = (yyvsp[(2) - (5)].treeNode)->getSymbolName();
			symbolInfo* temp = table.lookup(funcName);
			if (temp!=nullptr)
			{
			}
			else {
				symbolInfo* f= new symbolInfo(funcName, returnType,"FUNCTION");
				table.insert(f);
			}
			table.enterScope();table.exitScope(); // dummy scope for declaration
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (5)].treeNode)->getSymbolName()+" "+(yyvsp[(2) - (5)].treeNode)->getSymbolName()+"();","func_declaration");
			
		;}
    break;

  case 11:
#line 420 "47.y"
    {
			string returnType = (yyvsp[(1) - (5)].treeNode)->getSymbolName();
			returnTypeToMatch= returnType;
			string funcName = (yyvsp[(2) - (5)].treeNode)->getSymbolName();
			splitParameterTypeList((yyvsp[(4) - (5)].treeNode)->getsymbolType(), ',');
			extractParameterNameList((yyvsp[(4) - (5)].treeNode)->getSymbolName(),',');

			currentFunc=funcName;
			
			symbolInfo* temp = table.lookup(funcName);
			if (temp!=nullptr) // exists in symboltable, may or may not be func, decl or defn
			{
				if (temp->getFuncName()=="FUNCTION"){
					symbolInfo* ftemp=temp;
					if(ftemp->getDefined()){
					}
					else { // decl but not defn, working case
						// return type matching
						if (ftemp->getReturnType() != returnType) {
						}
						// total number of arguments mismatch
						if ((ftemp->getParameterTypeList().size() != parameterTypeList.size())) {
							
						}
						else {
							for(int i=0; i<ftemp->getParameterTypeList().size(); i++){
								if (ftemp->getParameterTypeList()[i] != parameterTypeList[i]){
								}
							}

						}
						ftemp->setDefined(true);
						
					}
				}
				else { // not a function 
				}
			}
			else { // not in symboltable
				symbolInfo* f= new symbolInfo(funcName, returnType,"FUNCTION");
				for(string parameterType : parameterTypeList)
					f->addParameter(parameterType);
				f->setDefined(true);
				table.insert(f);
			}
			;


			fprintf(tempasmout, "\n%s PROC\n", funcName.c_str());
			fprintf(tempasmout, "\tPUSH BP\n\tMOV BP, SP\n");
			cout<<parameterTypeList.size()<<endl;

			
		;}
    break;

  case 12:
#line 473 "47.y"
    {
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (7)].treeNode)->getSymbolName()+" "+(yyvsp[(2) - (7)].treeNode)->getSymbolName()+"("+(yyvsp[(4) - (7)].treeNode)->getSymbolName()+")"+(yyvsp[(7) - (7)].treeNode)->getSymbolName()+"\n","func_definition");

			resetCurrentOffset();
			fprintf(tempasmout, "%s_EXIT:\n", (yyvsp[(2) - (7)].treeNode)->getSymbolName().c_str());
			fprintf(tempasmout, "\tMOV SP, BP ; Restoring SP\n");
			fprintf(tempasmout, "\tPOP BP\n");
			fprintf(tempasmout, "\tRET %d\n", 2*parameterCount);
			fprintf(tempasmout, "%s ENDP\n", (yyvsp[(2) - (7)].treeNode)->getSymbolName().c_str());

		;}
    break;

  case 13:
#line 485 "47.y"
    {	// set isMainDefined as true when ID.name == "main"
			string returnType = (yyvsp[(1) - (4)].treeNode)->getSymbolName();
			returnTypeToMatch= returnType;
			string funcName = (yyvsp[(2) - (4)].treeNode)->getSymbolName();
			if(funcName == "main") isMainDefined=true;

			currentFunc=funcName;
			
			symbolInfo* temp = table.lookup(funcName);
			if (temp!=nullptr) // exists in symboltable, may or may not be func, decl or defn
			{
				if (temp->getFuncName()=="FUNCTION"){
					symbolInfo* ftemp=temp;
					if(ftemp->getDefined()){
					}
					else { // decl but not defn, working case
						// return type matching

						if (ftemp->getReturnType() != returnType) {
						}
						// total number of arguments mismatch
						if ((ftemp->getParameterTypeList().size() != 0)) {
						}
						
						ftemp->setDefined(true);
						
					}
				}
				else { // not a function 
				}
			}
			else { // not in symboltable
				symbolInfo* f= new symbolInfo(funcName, returnType,"FUNCTION");
				f->setDefined(true);
				table.insert(f);
			}
			
			fprintf(tempasmout, "\n%s PROC\n", funcName.c_str());
			if(funcName=="main") {
				fprintf(tempasmout, "\tMOV AX, @DATA\n\tMOV DS, AX\n");
			}
			fprintf(tempasmout, "PUSH BP\nMOV BP, SP\n");

			
		;}
    break;

  case 14:
#line 529 "47.y"
    {
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (6)].treeNode)->getSymbolName()+" "+(yyvsp[(2) - (6)].treeNode)->getSymbolName()+"()"+(yyvsp[(6) - (6)].treeNode)->getSymbolName()+"\n","func_definition");
			resetCurrentOffset();
			fprintf(tempasmout, "%s_EXIT:\n", (yyvsp[(2) - (6)].treeNode)->getSymbolName().c_str());
			fprintf(tempasmout, "\tMOV SP, BP ; Restoring SP\n");
			fprintf(tempasmout, "\tPOP BP\n");
			if((yyvsp[(2) - (6)].treeNode)->getSymbolName()=="main") {
				fprintf(tempasmout, "\tMOV AH, 4CH\n\tINT 21H\n");
			} else {
				fprintf(tempasmout, "\tRET\n");
			}

			fprintf(tempasmout, "%s ENDP\n", (yyvsp[(2) - (6)].treeNode)->getSymbolName().c_str());
		;}
    break;

  case 15:
#line 547 "47.y"
    {
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (4)].treeNode)->getSymbolName() + "," + (yyvsp[(3) - (4)].treeNode)->getSymbolName() + " " + (yyvsp[(4) - (4)].treeNode)->getSymbolName(), (yyvsp[(1) - (4)].treeNode)->getsymbolType() + "," + (yyvsp[(3) - (4)].treeNode)->getsymbolType());
		;}
    break;

  case 16:
#line 551 "47.y"
    {
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName() + "," + (yyvsp[(3) - (3)].treeNode)->getSymbolName(), (yyvsp[(1) - (3)].treeNode)->getsymbolType() + "," + (yyvsp[(3) - (3)].treeNode)->getsymbolType());
		;}
    break;

  case 17:
#line 555 "47.y"
    {
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (2)].treeNode)->getSymbolName() + " " + (yyvsp[(2) - (2)].treeNode)->getSymbolName(), (yyvsp[(1) - (2)].treeNode)->getsymbolType());
		;}
    break;

  case 18:
#line 559 "47.y"
    {
			(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
		;}
    break;

  case 19:
#line 567 "47.y"
    {
				

				(yyval.treeNode) = new symbolInfo("{\n"+(yyvsp[(3) - (4)].treeNode)->getSymbolName()+"\n}\n","compound_statement");

				p.clear();
				table.exitScope();
				
			;}
    break;

  case 20:
#line 577 "47.y"
    {
				(yyval.treeNode) = new symbolInfo("{\n}\n","compound_statement");

				table.exitScope();
			;}
    break;

  case 21:
#line 584 "47.y"
    {
				table.enterScope();
				if ((parameterNameList.size() != parameterTypeList.size())) {
				}
				else if(parameterTypeList.size()>0){
					parameterCount= parameterTypeList.size();
					for(int i=0; i<parameterTypeList.size(); i++){
						symbolInfo* tempSymbol= new symbolInfo(parameterNameList[i], parameterTypeList[i]);
						tempSymbol->setStackOffset((parameterTypeList.size()-i-1)*2+4); // 2 for BP, 2 for ret address
						tempSymbol->setGlobal(false);
						// fprintf(tempasmout, "PUSH AX\n");
						p.push_back(tempSymbol);
						bool ok=table.insert(tempSymbol);
						cout<<ok<<" "<<parameterNameList[i]<<" "<<tempSymbol->isGlobal()<<endl;
					}
				}
				clearParameterNameList();
				clearParameterTypeList();
			;}
    break;

  case 22:
#line 606 "47.y"
    {
			string varType = (yyvsp[(1) - (3)].treeNode)->getSymbolName();
			string varList = (yyvsp[(2) - (3)].treeNode)->getSymbolName();
			if ((yyvsp[(1) - (3)].treeNode)->getSymbolName()=="void"){
			}
			
			else {
				split(varList,',');
				for (string var : v){
					if ((var.find("[") != string::npos) || (var.find("]") != string::npos)) {
						string arrayName = getArrayName(var);
						int arraySize = getArraySize(var);
						bool newSymbol = table.insert(arrayName, varType+"[]");
						if(!newSymbol){
						}
						else {
							if(1==table.getCurrentScopeId()) { // global
								fprintf(asmout, "%s DW %d DUP(?) ; %s[%d] decl\n", arrayName.c_str(), arraySize, arrayName.c_str(), arraySize);
							}
							else{
								for(int j=0; j<arraySize; j++){
									fprintf(tempasmout, "PUSH AX ; %s[%d] decl\n", arrayName.c_str(), arraySize-1-j);
									currentOffset-=2;
								}
								symbolInfo* temp= table.lookup(arrayName);
								temp->setStackOffset(currentOffset); // arrayName[arraySize - 1] is at currentOffset[BP]
								temp->setGlobal(false);
							}
						}
					}

					else {
						bool newSymbol = table.insert(var, varType);
						if(!newSymbol){
						}
						else {
							if(1==table.getCurrentScopeId()) { // global
                                globalVar+=(var+" DW 1 DUP (0000H) ;"+var+" decl\n");
                                cout<<globalVar<<endl;
								fprintf(asmout, "%s DW ? ; %s decl\n", var.c_str(), var.c_str());
							}
							else{
								fprintf(tempasmout, "SUB SP,2 ; %s decl\n", var.c_str());
								currentOffset-=2;
								symbolInfo* temp= table.lookup(var);
								temp->setStackOffset(currentOffset);
								temp->setGlobal(false);
							}
						}
					}


				}
				clearVector();
			}



			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+" "+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+";", "var_declaration");

		;}
    break;

  case 23:
#line 670 "47.y"
    {
			(yyval.treeNode)= new symbolInfo("int","int");
		;}
    break;

  case 24:
#line 674 "47.y"
    {
			(yyval.treeNode)= new symbolInfo("float","float");
		;}
    break;

  case 25:
#line 678 "47.y"
    {
			(yyval.treeNode)= new symbolInfo("void","void");
		;}
    break;

  case 26:
#line 684 "47.y"
    {
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+","+(yyvsp[(3) - (3)].treeNode)->getSymbolName(), "declaration_list");
			
		  ;}
    break;

  case 27:
#line 689 "47.y"
    {
			if((yyvsp[(5) - (6)].treeNode)->getSymbolName()=="0"){
			}
			
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (6)].treeNode)->getSymbolName()+","+(yyvsp[(3) - (6)].treeNode)->getSymbolName()+"["+(yyvsp[(5) - (6)].treeNode)->getSymbolName()+"]", "declaration_list");
			
		  ;}
    break;

  case 28:
#line 697 "47.y"
    {
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (1)].treeNode)->getSymbolName(), "declaration_list");
			
		  ;}
    break;

  case 29:
#line 702 "47.y"
    {
			if((yyvsp[(3) - (4)].treeNode)->getSymbolName()=="0"){
			}
			
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (4)].treeNode)->getSymbolName()+"["+(yyvsp[(3) - (4)].treeNode)->getSymbolName()+"]", "declaration_list");
			
		  ;}
    break;

  case 30:
#line 713 "47.y"
    {
			(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
		;}
    break;

  case 31:
#line 717 "47.y"
    {
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (2)].treeNode)->getSymbolName()+"\n"+(yyvsp[(2) - (2)].treeNode)->getSymbolName(), "statements");
			
	    ;}
    break;

  case 32:
#line 724 "47.y"
    {
		(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
		
	  ;}
    break;

  case 33:
#line 729 "47.y"
    {	
		
		(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
	  ;}
    break;

  case 34:
#line 734 "47.y"
    {
		(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
	  ;}
    break;

  case 35:
#line 737 "47.y"
    {
		forCount++;
		forCountStack.push(forCount);
		fprintf(tempasmout, "%s: ; for loop starting label\n", ("label_for_start_"+to_string(forCountStack.top())).c_str());
	  ;}
    break;

  case 36:
#line 741 "47.y"
    {
		
	  	fprintf(tempasmout, "CMP AX, 0\n");
	  	fprintf(tempasmout, "JE %s ; loop ending condn\n", ("label_for_end_"+to_string(forCountStack.top())).c_str());
	  	fprintf(tempasmout, "JMP %s ; loop code label\n", ("label_for_stmt_"+to_string(forCountStack.top())).c_str());
	  	fprintf(tempasmout, "%s: ; loop iterator inc/dec\n", ("label_for_ite_"+to_string(forCountStack.top())).c_str());
	  	
	  ;}
    break;

  case 37:
#line 748 "47.y"
    {
		fprintf(tempasmout, "JMP %s ; restart loop\n", ("label_for_start_"+to_string(forCountStack.top())).c_str());
		fprintf(tempasmout, "%s: ; loop code\n", ("label_for_stmt_"+to_string(forCountStack.top())).c_str());
	  ;}
    break;

  case 38:
#line 752 "47.y"
    {
		(yyval.treeNode) = new symbolInfo("for("+(yyvsp[(3) - (10)].treeNode)->getSymbolName()+(yyvsp[(5) - (10)].treeNode)->getSymbolName()+(yyvsp[(7) - (10)].treeNode)->getSymbolName()+")"+(yyvsp[(10) - (10)].treeNode)->getSymbolName(), "statement");
		//Offline 4 code
		fprintf(tempasmout, "JMP %s ; update iterator after stmt\n", ("label_for_ite_"+to_string(forCountStack.top())).c_str());
	  	fprintf(tempasmout, "%s: ; end of for loop\n", ("label_for_end_"+to_string(forCountStack.top())).c_str());
	  	forCountStack.pop();
	  ;}
    break;

  case 39:
#line 760 "47.y"
    {
		(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (2)].treeNode)->getSymbolName()+(yyvsp[(2) - (2)].treeNode)->getSymbolName(), "statement");
		fprintf(tempasmout, "%s: ; end if label\n", ("label_else_"+to_string(ifCountStack.top())).c_str());
		ifCountStack.pop();
	  ;}
    break;

  case 40:
#line 765 "47.y"
    {
		// labelEndIf= "label_endif_"+to_string(ifCount);
		fprintf(tempasmout, "JMP %s\n", ("label_endif_"+to_string(ifCountStack.top())).c_str());
		fprintf(tempasmout, "%s: ; else label\n", ("label_else_"+to_string(ifCountStack.top())).c_str());
	  ;}
    break;

  case 41:
#line 769 "47.y"
    {
		(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (5)].treeNode)->getSymbolName()+(yyvsp[(2) - (5)].treeNode)->getSymbolName()+"else\n"+(yyvsp[(5) - (5)].treeNode)->getSymbolName(), "statement");
		fprintf(tempasmout, "%s: ; end if label\n", ("label_endif_"+to_string(ifCountStack.top())).c_str());
		ifCountStack.pop();
	  ;}
    break;

  case 42:
#line 775 "47.y"
    {
		whileCount++;
		whileCountStack.push(whileCount);
		// labelLoopStart= "label_while_start_"+to_string(whileCount);
		fprintf(tempasmout, "%s: ; while loop begin\n", ("label_while_start_"+to_string(whileCountStack.top())).c_str());
	  ;}
    break;

  case 43:
#line 781 "47.y"
    {
		// labelLoopEnd= "label_while_end_"+to_string(whileCount);
		fprintf(tempasmout, "POP CX\nCMP CX, 0\nJE %s\n", ("label_while_end_"+to_string(whileCountStack.top())).c_str());
	  ;}
    break;

  case 44:
#line 785 "47.y"
    {
		(yyval.treeNode) = new symbolInfo("while("+(yyvsp[(4) - (7)].treeNode)->getSymbolName()+")"+(yyvsp[(7) - (7)].treeNode)->getSymbolName(), "statement");
		//fprintf(logout, "Line %d: statement : WHILE LPAREN expression RPAREN statement\n\n%s\n\n", lineCount, $$->getSymbolName().c_str());
		//Offline 4 code
		fprintf(tempasmout, "JMP %s ; back to top of loop\n%s:\n", ("label_while_start_"+to_string(whileCountStack.top())).c_str(), ("label_while_end_"+to_string(whileCountStack.top())).c_str());
		whileCountStack.pop();
	  ;}
    break;

  case 45:
#line 793 "47.y"
    { // move to AX from stack 
		symbolInfo *temp = table.lookup((yyvsp[(3) - (5)].treeNode)->getSymbolName());
		// handle undeclared variable error
		if(temp==nullptr){
		}
		else (yyval.treeNode) = new symbolInfo("println("+(yyvsp[(3) - (5)].treeNode)->getSymbolName()+");", "statement");
		
		if(temp->isGlobal()) 
		fprintf(tempasmout, "MOV AX, %s\nCALL PRINT\n ; argument %s in AX\n", temp->getSymbolName().c_str(), temp->getSymbolName().c_str());
		else{
				fprintf(tempasmout, "MOV AX, %d[BP]\nCALL PRINT\n ; argument %s in AX\n", temp->getStackOffset(), temp->getSymbolName().c_str());
		}
	  ;}
    break;

  case 46:
#line 807 "47.y"
    { // jump to label of current function
	  	//! return value should be in AX
		// check return type in func_defn and decl
		if((yyvsp[(2) - (3)].treeNode)->getsymbolType()=="expression") {
		}

		else if(returnTypeToMatch=="void");

		else if((yyvsp[(2) - (3)].treeNode)->getsymbolType()!=returnTypeToMatch){
		}
		
		(yyval.treeNode) = new symbolInfo("return "+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+";", "statement");
		fprintf(tempasmout, "POP AX\n");
		fprintf(tempasmout, "\tJMP %s_EXIT\n", currentFunc.c_str());	
	  ;}
    break;

  case 47:
#line 825 "47.y"
    {
		ifCount++;
		ifCountStack.push(ifCount);
		// labelElse= "label_else_"+to_string(ifCount);
		fprintf(tempasmout, "POP AX ; expr in AX\nCMP AX, 0 ; checking expr\n");
		fprintf(tempasmout, "JE %s\n", ("label_else_"+to_string(ifCountStack.top())).c_str());
		(yyval.treeNode)= new symbolInfo("if("+(yyvsp[(3) - (4)].treeNode)->getSymbolName()+")", "statement");
	;}
    break;

  case 48:
#line 835 "47.y"
    {
				(yyval.treeNode) = new symbolInfo(";", "expression_statement");
			;}
    break;

  case 49:
#line 839 "47.y"
    {
				(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (2)].treeNode)->getSymbolName()+";", "expression_statement");
				fprintf(tempasmout, "POP AX\n");
			;}
    break;

  case 50:
#line 846 "47.y"
    {
		symbolInfo *temp = table.lookup((yyvsp[(1) - (1)].treeNode)->getSymbolName());
		if(temp->isGlobal()){
			for(auto s:p){
				if(s->getSymbolName()==(yyvsp[(1) - (1)].treeNode)->getSymbolName()){
					temp=s;
					break;
				}
			}
		}
		
		//handle undeclared variable error
		if(temp==nullptr){
		}
		else { 

			if(temp->isGlobal()) {
				fprintf(tempasmout, "MOV AX, %s\nPUSH AX ; %s called\n", temp->getSymbolName().c_str(), temp->getSymbolName().c_str());
			} else {
				fprintf(tempasmout, "MOV AX, %d[BP]\nPUSH AX ; %s called\n", temp->getStackOffset(), temp->getSymbolName().c_str());
			}
			(yyval.treeNode) = new symbolInfo(temp->getSymbolName(), temp->getsymbolType());
			(yyval.treeNode)->setStackOffset(temp->getStackOffset());
		}
		
	 ;}
    break;

  case 51:
#line 873 "47.y"
    {
		symbolInfo *temp = table.lookup((yyvsp[(1) - (4)].treeNode)->getSymbolName());
		if(temp==nullptr){
		}
		else {
			string varType = temp->getsymbolType();
			if ((varType.find("[") != string::npos) || (varType.find("]") != string::npos)) { // is an array
				// handle [float] error
				if ((yyvsp[(3) - (4)].treeNode)->getsymbolType()!="int"){
				}
				if(temp->isGlobal()) {
					fprintf(tempasmout, "POP BX ; popped index expr\nSHL BX, 1\nMOV SI, %s\nMOV AX, BX[SI]\n ; %s called\n", temp->getSymbolName().c_str(), temp->getSymbolName().c_str()); 
				} else {
					fprintf(tempasmout, "POP BX ; popped index expr %s\nSHL BX, 1\nADD BX, %d\n;ADD BX, BP\nPUSH BP\nADD BP, BX\nMOV AX, [BP]\nPOP BP\n;MOV AX, [BX]\nPUSH AX ; value of %s[%s]\nPUSH BX ; index %s\n",
						(yyvsp[(3) - (4)].treeNode)->getSymbolName().c_str(), temp->getStackOffset(), temp->getSymbolName().c_str(), (yyvsp[(3) - (4)].treeNode)->getSymbolName().c_str(), (yyvsp[(3) - (4)].treeNode)->getSymbolName().c_str());
				}
				(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (4)].treeNode)->getSymbolName()+"["+(yyvsp[(3) - (4)].treeNode)->getSymbolName()+"]", getArrayName(varType));
				(yyval.treeNode)->setStackOffset(temp->getStackOffset());
			} 
			else { 
			}
		}
	 ;}
    break;

  case 52:
#line 897 "47.y"
    {
		symbolInfo *temp = table.lookup((yyvsp[(1) - (3)].treeNode)->getSymbolName());
		if(temp==nullptr){
		}
		else {
			string varType = temp->getsymbolType();
			if ((varType.find("[") != string::npos) || (varType.find("]") != string::npos)) { // is an array
				// handle [] error
				errorCount++;
				(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+"[]", getArrayName(varType));
			} 
			else { 
			}
		}
		
	 ;}
    break;

  case 53:
#line 916 "47.y"
    {
			(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
		;}
    break;

  case 54:
#line 920 "47.y"
    {
			// bunch of type mismatch handling (but int in float is allowed)
			if ((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="void" || (yyvsp[(3) - (3)].treeNode)->getsymbolType()=="void"){
			}
			else if ((yyvsp[(1) - (3)].treeNode)->getsymbolType()!=(yyvsp[(3) - (3)].treeNode)->getsymbolType()){
				string varType= (yyvsp[(1) - (3)].treeNode)->getsymbolType();
				string exprType= (yyvsp[(3) - (3)].treeNode)->getsymbolType();
				if ((varType.find("[") != string::npos) || (exprType.find("[") != string::npos)) { // either an array
				}
				else if (varType=="float" && exprType=="int") ;
				else if (varType=="variable" || exprType=="factor") ;
				else {
				}
			}
			string varName= (yyvsp[(1) - (3)].treeNode)->getSymbolName();

			fprintf(tempasmout, "POP AX ; r-val of assignop %s\n", (yyvsp[(3) - (3)].treeNode)->getSymbolName().c_str());
			
			symbolInfo* temp = table.lookup(getArrayName(varName));
			if(temp->isGlobal()){
				fprintf(tempasmout, "MOV %s, AX\n", temp->getSymbolName().c_str());
			} else {
				if (varName.find("[") != string::npos){
					fprintf(tempasmout, "POP BX\n");
					fprintf(tempasmout, ";MOV [BX], AX\nPUSH BP\nADD BP, BX\nMOV [BP], AX\nPOP BP ; assigning to %s\n", (yyvsp[(1) - (3)].treeNode)->getSymbolName().c_str());
				}
				else {
					fprintf(tempasmout, "MOV %d[BP], AX ; assigning %s to %s\n", (yyvsp[(1) - (3)].treeNode)->getStackOffset(), (yyvsp[(3) - (3)].treeNode)->getSymbolName().c_str(), (yyvsp[(1) - (3)].treeNode)->getSymbolName().c_str());
				}
			}
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+"="+(yyvsp[(3) - (3)].treeNode)->getSymbolName(), "expression");
			
	   	;}
    break;

  case 55:
#line 956 "47.y"
    {
			(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
		;}
    break;

  case 56:
#line 960 "47.y"
    {
			if ((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="void" || (yyvsp[(3) - (3)].treeNode)->getsymbolType()=="void"){
			}
			(yyval.treeNode) = new symbolInfo("", "int");
			(yyval.treeNode)->setSymbolName((yyvsp[(1) - (3)].treeNode)->getSymbolName()+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+(yyvsp[(3) - (3)].treeNode)->getSymbolName());
			
			// Offline 4 code
			fprintf(tempasmout, "POP BX\nPOP AX ; left side value\n");
			string labelIfTrue=newLabel();
			string labelIfFalse=newLabel(); 

			if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="&&"){
				fprintf(tempasmout, "CMP AX, 0\nJE %s\nCMP BX, 0\nJE %s\nPUSH 1\nJMP %s\n", labelIfFalse.c_str(), labelIfFalse.c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; total false\n%s:\n", labelIfFalse.c_str(), labelIfTrue.c_str());
			
			} else if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="||"){
				fprintf(tempasmout, "CMP AX, 0\nJNE %s\nCMP BX, 0\nJNE %s\nPUSH 0\nJMP %s\n", labelIfFalse.c_str(), labelIfFalse.c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 1 ; total false\n%s:\n", labelIfFalse.c_str(), labelIfTrue.c_str());
			
			} 

		;}
    break;

  case 57:
#line 985 "47.y"
    {
			(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
		;}
    break;

  case 58:
#line 989 "47.y"
    {
			if ((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="void" || (yyvsp[(3) - (3)].treeNode)->getsymbolType()=="void"){
			}
			(yyval.treeNode) = new symbolInfo("", "int");
			(yyval.treeNode)->setSymbolName((yyvsp[(1) - (3)].treeNode)->getSymbolName()+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+(yyvsp[(3) - (3)].treeNode)->getSymbolName());
			// Offline 4 code
			fprintf(tempasmout, "POP AX\nPOP BX ; left side value\nCMP BX, AX ; evaluating %s\n", (yyval.treeNode)->getSymbolName().c_str());
			string labelIfTrue=newLabel();
			string labelIfFalse=newLabel(); 
			if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="<"){
				fprintf(tempasmout, "JNL %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
			
			} else if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="<="){
				fprintf(tempasmout, "JNLE %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
			
			} else if((yyvsp[(2) - (3)].treeNode)->getSymbolName()==">"){
				fprintf(tempasmout, "JNG %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
		
			} else if((yyvsp[(2) - (3)].treeNode)->getSymbolName()==">="){
				fprintf(tempasmout, "JNGE %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
			
			} else if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="=="){
				fprintf(tempasmout, "JNE %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
			
			} else if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="!="){
				fprintf(tempasmout, "JE %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), (yyval.treeNode)->getSymbolName().c_str(), labelIfTrue.c_str());
							
			}

		;}
    break;

  case 59:
#line 1028 "47.y"
    {
			(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
		;}
    break;

  case 60:
#line 1032 "47.y"
    {	// add and keep in AX
			// handle int addition and float addition
			string exprType;
			if(((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="int") && ((yyvsp[(3) - (3)].treeNode)->getsymbolType()=="int")) exprType= "int"; 
			else exprType= "float";
			if ((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="void" || (yyvsp[(3) - (3)].treeNode)->getsymbolType()=="void"){
				exprType= "void";
			}
			if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="+")
				fprintf(tempasmout, "POP AX\nPOP BX\nADD AX, BX\nPUSH AX ; %s+%s pushed\n", (yyvsp[(1) - (3)].treeNode)->getSymbolName().c_str(), (yyvsp[(3) - (3)].treeNode)->getSymbolName().c_str());
			else 
				fprintf(tempasmout, "POP AX\nPOP BX\nSUB BX, AX\nPUSH BX ; %s-%s pushed\n", (yyvsp[(1) - (3)].treeNode)->getSymbolName().c_str(), (yyvsp[(3) - (3)].treeNode)->getSymbolName().c_str()); //! check minus
			(yyval.treeNode) = new symbolInfo("", exprType);
			(yyval.treeNode)->setSymbolName((yyvsp[(1) - (3)].treeNode)->getSymbolName()+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+(yyvsp[(3) - (3)].treeNode)->getSymbolName());
			//fprintf(logout, "Line %d: simple_expression : simple_expression ADDOP term\n\n%s\n\n", lineCount, $$->getSymbolName().c_str());
		;}
    break;

  case 61:
#line 1051 "47.y"
    {
		(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
	 ;}
    break;

  case 62:
#line 1055 "47.y"
    {
		//handle errors
		if ((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="void" || (yyvsp[(3) - (3)].treeNode)->getsymbolType()=="void"){
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+(yyvsp[(3) - (3)].treeNode)->getSymbolName(),"void");
		}
		else if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="%"){ // modulus cases
			if(((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="int") && ((yyvsp[(3) - (3)].treeNode)->getsymbolType()=="int")){
				if((yyvsp[(3) - (3)].treeNode)->getSymbolName()=="0"){
				}
			}
			else { // non int operand
			}
			
			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+(yyvsp[(3) - (3)].treeNode)->getSymbolName(),"int");
			//Offline 4 code
			fprintf(tempasmout, "MOV DX, 0 ; DX:AX = 0000:AX\nPOP BX\nPOP AX\nIDIV BX\nPUSH DX ; remainder of %s is in DX\n", (yyval.treeNode)->getSymbolName().c_str());

		}
		else {
			if(((yyvsp[(1) - (3)].treeNode)->getsymbolType()=="int")&&((yyvsp[(3) - (3)].treeNode)->getsymbolType()=="int"))
				(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+(yyvsp[(3) - (3)].treeNode)->getSymbolName(),"int");
			else (yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+(yyvsp[(3) - (3)].treeNode)->getSymbolName(),"float");
			// Offline 4 code
			if((yyvsp[(2) - (3)].treeNode)->getSymbolName()=="*")
				fprintf(tempasmout, "POP BX\nPOP AX\nIMUL BX\nPUSH AX ; result of %s is in AX, pushed\n", (yyval.treeNode)->getSymbolName().c_str());
			else 
				fprintf(tempasmout, "POP BX\nPOP AX\nIDIV BX\nPUSH AX ; result of %s is in AX, pushed\n", (yyval.treeNode)->getSymbolName().c_str());; //! division
		}
		
	 ;}
    break;

  case 63:
#line 1088 "47.y"
    {
			if ((yyvsp[(2) - (2)].treeNode)->getsymbolType()=="void"){
				errorCount++;
			}

			//Offline 4
			if((yyvsp[(1) - (2)].treeNode)->getSymbolName()=="-"){
				fprintf(tempasmout, "POP AX\nNEG AX ; -%s\nPUSH AX\n", (yyvsp[(2) - (2)].treeNode)->getSymbolName().c_str());
			}

			(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (2)].treeNode)->getSymbolName()+(yyvsp[(2) - (2)].treeNode)->getSymbolName(), (yyvsp[(2) - (2)].treeNode)->getsymbolType());
		 ;}
    break;

  case 64:
#line 1101 "47.y"
    {
			if ((yyvsp[(2) - (2)].treeNode)->getsymbolType()=="void"){
			}
			(yyval.treeNode) = new symbolInfo("!"+(yyvsp[(2) - (2)].treeNode)->getSymbolName(), (yyvsp[(2) - (2)].treeNode)->getsymbolType());
			//fprintf(logout, "Line %d: unary_expression : NOT unary_expression\n\n%s\n\n", lineCount, $$->getSymbolName().c_str());
		 	string labelIfTrue=newLabel();
			string labelIfFalse=newLabel();
			fprintf(tempasmout, "POP AX\nCMP AX, 0 ; !%s\nJNE %s\nMOV AX, 1\nJMP %s\n\
				\n%s:\nXOR AX, AX\n%s:\nPUSH AX\n"
				, (yyvsp[(2) - (2)].treeNode)->getSymbolName().c_str(), labelIfTrue.c_str(), labelIfFalse.c_str(), labelIfTrue.c_str(), labelIfFalse.c_str());
		 ;}
    break;

  case 65:
#line 1113 "47.y"
    {
			(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
		 ;}
    break;

  case 66:
#line 1119 "47.y"
    {
		(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
		if ((yyval.treeNode)->getSymbolName().find("[") != string::npos)
			fprintf(tempasmout, "POP BX ; r-value, no need for index\n");
	;}
    break;

  case 67:
#line 1125 "47.y"
    {
		string returnType= "factor";
		string funcName = (yyvsp[(1) - (4)].treeNode)->getSymbolName();
		symbolInfo* temp = table.lookup(funcName);
		if (temp==nullptr)
		{
		}
		else {
			if(temp->getFuncName()=="FUNCTION"){
				symbolInfo* ftemp= temp;
				returnType= ftemp->getReturnType();
				splitParameterTypeList((yyvsp[(3) - (4)].treeNode)->getsymbolType(),',');
				// cout<<parameterTypeList[0]<<" "<<ftemp->getParameterTypeList().size()<<endl;
				if(parameterTypeList.size()!=ftemp->getParameterTypeList().size()){
					if(parameterTypeList[0]=="void");
					else {
					}
				}
				else {
					for(int i=0; i<ftemp->getParameterTypeList().size(); i++){
						if (parameterTypeList[i].find("[") != string::npos){ // array check
						}
						if (ftemp->getParameterTypeList()[i] != parameterTypeList[i]){
						}
					}

				}

				clearParameterTypeList();
			}
			else {
			}
		}
		(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (4)].treeNode)->getSymbolName()+"("+(yyvsp[(3) - (4)].treeNode)->getSymbolName()+")", returnType);
		fprintf(tempasmout, "CALL %s\n", (yyvsp[(1) - (4)].treeNode)->getSymbolName().c_str());
		if(returnType!="void"){
			fprintf(tempasmout, "PUSH AX ; return value of %s\n", (yyvsp[(1) - (4)].treeNode)->getSymbolName().c_str());
		}
	;}
    break;

  case 68:
#line 1165 "47.y"
    {
		(yyval.treeNode) = new symbolInfo("("+(yyvsp[(2) - (3)].treeNode)->getSymbolName()+")", (yyvsp[(2) - (3)].treeNode)->getsymbolType());

	;}
    break;

  case 69:
#line 1170 "47.y"
    {
		(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
		fprintf(tempasmout, "PUSH %s\n", (yyval.treeNode)->getSymbolName().c_str());
	;}
    break;

  case 70:
#line 1175 "47.y"
    {
		(yyval.treeNode) = (yyvsp[(1) - (1)].treeNode);
	;}
    break;

  case 71:
#line 1179 "47.y"
    {
		(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (2)].treeNode)->getSymbolName()+"++",(yyvsp[(1) - (2)].treeNode)->getsymbolType());
		if ((yyvsp[(1) - (2)].treeNode)->getSymbolName().find("[") != string::npos){
			fprintf(tempasmout, "POP BX\nPOP AX\nINC AX ; %s++\n", (yyvsp[(1) - (2)].treeNode)->getSymbolName().c_str());
			fprintf(tempasmout, "PUSH BP\nADD BP, BX\nMOV [BP], AX\nPOP BP\n");
		}
		else {
			fprintf(tempasmout, "INC AX\nMOV %d[BP], AX\n", (yyvsp[(1) - (2)].treeNode)->getStackOffset());
		}
		// fprintf(tempasmout, "INC AX\n");
	;}
    break;

  case 72:
#line 1191 "47.y"
    {
		(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (2)].treeNode)->getSymbolName()+"--",(yyvsp[(1) - (2)].treeNode)->getsymbolType());
		if ((yyvsp[(1) - (2)].treeNode)->getSymbolName().find("[") != string::npos){
			fprintf(tempasmout, "POP BX\nPOP AX\nDEC AX ; %s++\n", (yyvsp[(1) - (2)].treeNode)->getSymbolName().c_str());
			fprintf(tempasmout, "PUSH BP\nADD BP, BX\nMOV [BP], AX\nPOP BP\n");
		}
		else {
			fprintf(tempasmout, "DEC AX\nMOV %d[BP], AX\n", (yyvsp[(1) - (2)].treeNode)->getStackOffset());
		}
	;}
    break;

  case 73:
#line 1204 "47.y"
    {
				(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
			;}
    break;

  case 74:
#line 1208 "47.y"
    {
				(yyval.treeNode)=new symbolInfo("", "void");
				//fprintf(logout, "Line %d: argument_list : \n\n%s\n\n", lineCount, $$->getSymbolName().c_str());
			;}
    break;

  case 75:
#line 1215 "47.y"
    {
				(yyval.treeNode) = new symbolInfo((yyvsp[(1) - (3)].treeNode)->getSymbolName()+","+(yyvsp[(3) - (3)].treeNode)->getSymbolName(),(yyvsp[(1) - (3)].treeNode)->getsymbolType()+","+(yyvsp[(3) - (3)].treeNode)->getsymbolType());

			;}
    break;

  case 76:
#line 1220 "47.y"
    {
				(yyval.treeNode)=(yyvsp[(1) - (1)].treeNode);
			;}
    break;


/* Line 1267 of yacc.c.  */
#line 2917 "47.tab.c"
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


#line 1226 "47.y"


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
    fclose(tempasmout);
	fclose(asmout);

	ifstream firstasm;
	ifstream secondasm;
	ofstream finalasm;
	string line;
	firstasm.open("code.asm");
	secondasm.open("temp.asm");

	vector<string>finalCode;

	while(getline(firstasm,line)){
		finalCode.push_back(line);
	}

	while(getline(secondasm,line)){
		finalCode.push_back(line);
	}

	finalasm.open("code.asm");
	
	for(auto s:finalCode){
		finalasm<<s<<endl;
	}

	firstasm.close();
	secondasm.close();
	finalasm.close();

	optimizeCode();
	
	return 0;
}

