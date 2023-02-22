%option noyywrap
%x STRING_STATE
%x SINGLE_LINE_COMMENT_STATE
%x MULTI_LINE_COMMENT_STATE
%{
#include "bits/stdc++.h"
#include "symbolTable.h"


#include "47.tab.h"


using namespace std;

int errorCount=0;
int line_count=1;
int temp_line_count=0;


extern YYSTYPE yylval;
extern FILE *logout;
extern FILE *errorout;
extern void yyerror(char *s);

symbolTable symbolTableObj(10);

string tokenStr,logStr,strLexemeType,logComment,commentLexemeType;

// void symbolGenerator(string s){
// 	string symbolName(yytext);
// 	symbolInfo* symbol = new symbolInfo();
// 	symbol->setSymbolName(symbolName);
// 	symbol->setSymbolType(s);
//     symbol->startLine=line_count;
//     symbol->endLine=line_count;
// 	yylval = (YYSTYPE)symbol;
// }

%}

WHITESPACE [ \t\f\r\v]+ 
LETTER [a-zA-Z]
NEWLINE \n

INTEGER [0-9]+
FLOAT [0-9]+(\.[0-9]*)?([eE][+-]?[0-9]+)?|\.[0-9]+([eE][+-]?[0-9]+)?	
ESCAPE_CHAR_LITERAL "'\\"[ntafrbv0\\"\""]"'"
SINGLE_CHAR_LITERAL "'"."'"

IDENTIFIER [_a-zA-Z][_a-z0-9A-Z]*
STRING_START (\")
SINGLE_LINE_COMMENT_START (\/\/)
MULTI_LINE_COMMENT_START (\/\*)



ADDOP "+"|"-"
MULOP "*"|"/"|"%"
INCOP "++"
DECOP "--"
RELOP "<"|"<="|">"|">="|"=="|"!="
ASSIGNOP "="
LOGICOP "&&"|"||"
BITOP "&"|"|"|"^"|"<<"|">>"

REDUNDANT_DECIMAL [0-9]+(\.[0-9]*)*([eE][+-]?[0-9]+)?|(\.|[0-9])*([eE][+-]?[0-9]+)?
ILL_NUMBER [0-9]+(\.[0-9]*)*([eE][+-]?([0-9]|".")*)?|(\.|[0-9])*([eE][+-]?([0-9]|".")*)?
INVALID_PRE_SUFF [\._a-zA-Z0-9]*
MULTIPLE_CHAR "'"[^"'"\n]+"'"
EMPTY_CHAR "''"
UNFINISHED_CHAR "'"[^;]?
UNFINISHED_ESCAPE_CHAR (\'(\\)\')
UNRECOGNIZED_CHAR .

%%

{NEWLINE}	{
			line_count++;
		}

"if"	{
			//fprintf(tokenout,"<IF, if>\n");
            yylval.treeNode=new symbolInfo(yytext,"IF");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="IF :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <IF> Lexeme %s found\n",line_count,yytext);
            return IF;
        }
		
"for"	{
			//fprintf(tokenout,"<FOR, for>\n");
            
            yylval.treeNode=new symbolInfo(yytext,"FOR");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="FOR :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <FOR> Lexeme %s found\n",line_count,yytext);
            return FOR;
        }
"do"    {
			//fprintf(tokenout,"<DO, do>\n");
            yylval.treeNode=new symbolInfo(yytext,"DO");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="DO :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <DO> Lexeme %s found\n",line_count,yytext);
            return DO;
		}
"int"   {
			//fprintf(tokenout,"<INT, int>\n");
            yylval.treeNode=new symbolInfo(yytext,"INT");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="INT :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <INT> Lexeme %s found\n",line_count,yytext);
            return INT;
        }
"float" {
			//fprintf(tokenout,"<FLOAT, float>\n");
            yylval.treeNode=new symbolInfo(yytext,"FLOAT");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="FLOAT :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <FLOAT> Lexeme %s found\n",line_count,yytext);
            return FLOAT;
        }
"void"	{	
			//fprintf(tokenout,"<VOID, void>\n");
            yylval.treeNode=new symbolInfo(yytext,"VOID");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="VOID :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <VOID> Lexeme %s found\n",line_count,yytext);
            return VOID;
        }

"switch" {
			//fprintf(tokenout,"<SWITCH, switch>\n");
            yylval.treeNode=new symbolInfo(yytext,"SWITCH");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="SWITCH :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <SWITCH> Lexeme %s found\n",line_count,yytext);
            return SWITCH;
        }
"default" {
			//fprintf(tokenout,"<DEFAULT, default>\n");
            yylval.treeNode=new symbolInfo(yytext,"DEFAULT");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="DEFAULT :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <DEFAULT> Lexeme %s found\n",line_count,yytext);
            return DEFAULT;
        }
"else"	{
			//fprintf(tokenout,"<ELSE, else>\n");
            yylval.treeNode=new symbolInfo(yytext,"ELSE");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="ELSE :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <ELSE> Lexeme %s found\n",line_count,yytext);
            return ELSE;
        }
"while"	{
			//fprintf(tokenout,"<WHILE, while>\n");
            yylval.treeNode=new symbolInfo(yytext,"WHILE");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="WHILE :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <WHILE> Lexeme %s found\n",line_count,yytext);
            return WHILE;
        }
"break"	{
			//fprintf(tokenout,"<BREAK, break>\n");
            yylval.treeNode=new symbolInfo(yytext,"BREAK");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="BREAK :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <BREAK> Lexeme %s found\n",line_count,yytext);
            return BREAK;
        }
"char"	{
			//fprintf(tokenout,"<CHAR, char>\n");
            yylval.treeNode=new symbolInfo(yytext,"CHAR");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="CHAR :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <CHAR> Lexeme %s found\n",line_count,yytext);
            return CHAR;
        }
"double" {
			//fprintf(tokenout,"<DOUBLE, double>\n");
            yylval.treeNode=new symbolInfo(yytext,"DOUBLE");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="DOUBLE :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <DOUBLE> Lexeme %s found\n",line_count,yytext);
            return DOUBLE;
        }
"return" {
			//fprintf(tokenout,"<RETURN, return>\n");
            yylval.treeNode=new symbolInfo(yytext,"RETURN");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="RETURN :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <RETURN> Lexeme %s found\n",line_count,yytext);
            return RETURN;
        }
"case"  {
			//fprintf(tokenout,"<CASE, case>\n");
             yylval.treeNode=new symbolInfo(yytext,"CASE");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="CASE :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <CASE> Lexeme %s found\n",line_count,yytext);
            return CASE;
        }
"continue" {
			//fprintf(tokenout,"<CONTINUE, continue>\n");
            yylval.treeNode=new symbolInfo(yytext,"CONTINUE");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="CONTINUE :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <CONTINUE> Lexeme %s found\n",line_count,yytext);
            return CONTINUE;
        }
"printf" {  yylval.treeNode=new symbolInfo(yytext,"PRINTLN");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="PRINTLN :"+(string)yytext;
            return PRINTLN; 
            
            }
{INTEGER} {		
			//fprintf(tokenout,"<CONST_INT, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <CONST_INT> Lexeme %s found\n",line_count,yytext);
            yylval.treeNode=new symbolInfo(yytext,"CONST_INT");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="CONST_INT :"+(string)yytext;
            return CONST_INT;
        }
{FLOAT} {
			//fprintf(tokenout,"<CONST_FLOAT, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
            yylval.treeNode=new symbolInfo(yytext,"CONST_FLOAT");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="CONST_FLOAT :"+(string)yytext;
            return CONST_FLOAT;
        }
{ADDOP} {
			//fprintf(tokenout,"<ADDOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <ADDOP> Lexeme %s found\n",line_count,yytext);		
            yylval.treeNode=new symbolInfo(yytext,"ADDOP");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="ADDOP :"+(string)yytext;
            return ADDOP;
        }
{MULOP} {
			//fprintf(tokenout,"<MULOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <MULOP> Lexeme %s found\n",line_count,yytext);		
            yylval.treeNode=new symbolInfo(yytext,"MULOP");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="MULOP :"+(string)yytext;
            return MULOP;
        }	
{INCOP} {
			//fprintf(tokenout,"<INCOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <INCOP> Lexeme %s found\n",line_count,yytext);		
            yylval.treeNode=new symbolInfo(yytext,"INCOP");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="INCOP :"+(string)yytext;
            return INCOP;
        }
{DECOP} {
			//fprintf(tokenout,"<INCOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <INCOP> Lexeme %s found\n",line_count,yytext);		
            yylval.treeNode=new symbolInfo(yytext,"DECOP");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="DECOP :"+(string)yytext;
            return DECOP;
        }							
{RELOP}	{
			//fprintf(tokenout,"<RELOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <RELOP> Lexeme %s found\n",line_count,yytext);
            yylval.treeNode=new symbolInfo(yytext,"RELOP");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="RELOP :"+(string)yytext;
            return RELOP;
        }
{ASSIGNOP} {
			//fprintf(tokenout,"<ASSIGNOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <ASSIGNOP> Lexeme %s found\n",line_count,yytext);		
		    yylval.treeNode=new symbolInfo(yytext,"ASSIGNOP");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="ASSIGNOP :"+(string)yytext;
            return ASSIGNOP;
        }	
{LOGICOP} {
			//fprintf(tokenout,"<LOGICOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <LOGICOP> Lexeme %s found\n",line_count,yytext);		
            yylval.treeNode=new symbolInfo(yytext,"LOGICOP");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="LOGICOP :"+(string)yytext;
            return LOGICOP;
        }	

"!" {
			//fprintf(tokenout,"<NOT, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"NOT");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="NOT :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <NOT> Lexeme %s found\n",line_count,yytext);		
            return NOT;
        }	
"(" {
			//fprintf(tokenout,"<LPAREN, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"LPAREN");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="LPAREN :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <LPAREN> Lexeme %s found\n",line_count,yytext);		
            return LPAREN;
        }	
")" {
			//fprintf(tokenout,"<RPAREN, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"RPAREN");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="RPAREN :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <RPAREN> Lexeme %s found\n",line_count,yytext);		
            return RPAREN;
        }
"{" {
            //symbolTableObj.enterScope();
			//fprintf(tokenout,"<LCURL, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"LCURL");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="LCURL :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <LCURL> Lexeme %s found\n",line_count,yytext);		
            return LCURL;
        }
"}" {
            //symbolTableObj.exitScope();
			//fprintf(tokenout,"<RCURL, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"RCURL");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="RCURL :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <RCURL> Lexeme %s found\n",line_count,yytext);		
            return RCURL;
        }
"[" {
			//fprintf(tokenout,"<LSQUARE, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"LTHIRD");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="LTHIRD :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <LSQUARE> Lexeme %s found\n",line_count,yytext);		
            return LTHIRD;
        }
"]" {
			//fprintf(tokenout,"<RSQUARE, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"RTHIRD");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="RTHIRD :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <RSQUARE> Lexeme %s found\n",line_count,yytext);		
            return RTHIRD;
        }
"," {
			//fprintf(tokenout,"<COMMA, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"COMMA");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="COMMA :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <COMMA> Lexeme %s found\n",line_count,yytext);		
            return COMMA;
        }
";" {
			//fprintf(tokenout,"<SEMICOLON, %s>\n",yytext);
            yylval.treeNode=new symbolInfo(yytext,"SEMICOLON");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="SEMICOLON :"+(string)yytext;
			fprintf(logout,"Line# %d: Token <SEMICOLON> Lexeme %s found\n",line_count,yytext);		
            return SEMICOLON;
        }

{UNFINISHED_ESCAPE_CHAR} {
            errorCount++;
            fprintf(logout,"Error at line# %d: UNFINISHED_CONST_CHAR %s\n", line_count ,yytext);
            fprintf(errorout,"Error at line# %d: UNFINISHED_CONST_CHAR %s\n", line_count ,yytext);

        }
{SINGLE_CHAR_LITERAL} {
            string character="";
            character+=yytext[1];
			//fprintf(tokenout,"<CONST_CHAR, %s>\n",character.c_str());
			fprintf(logout,"Line# %d: Token <CONST_CHAR> Lexeme %s found\n",line_count,character.c_str());
            yylval.treeNode=new symbolInfo(yytext,"CONST_CHAR");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="CONST_CHAR :"+(string)yytext;
            return CONST_CHAR;
        }
{ESCAPE_CHAR_LITERAL} {
            string character="";

            if( yytext[2] =='n') character = '\n';
			else if( yytext[2] =='t') character = '\t';
			else if( yytext[2] =='a') character = '\a';
			else if( yytext[2] =='f') character = '\f';
			else if( yytext[2] =='r') character = '\r';
			else if( yytext[2] =='b') character = '\b';
			else if( yytext[2] =='v') character = '\v';
			else if( yytext[2] =='0') character = '\0';
			else if( yytext[2] =='\\') character = '\\';
			else character = '\"';
			//fprintf(tokenout,"<CONST_CHAR, %s>\n",character.c_str());
			fprintf(logout,"Line# %d: Token <CONST_CHAR> Lexeme %s found\n",line_count,character.c_str());
            yylval.treeNode=new symbolInfo(yytext,"CONST_CHAR");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="CONST_CHAR :"+(string)yytext;
            return CONST_CHAR;
        }

{IDENTIFIER} {
            
			// fprintf(tokenout,"<ID, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <ID> Lexeme %s found\n",line_count,yytext);

            // bool checkExistance=symbolTableObj.insert(symbolInfo(yytext,"ID"));
            // if(!checkExistance){
            //     fprintf(logout,"\t%s already exisits in the current ScopeTable\n",yytext);
            // }
            // else{
            // symbolTableObj.printAllScope();
            // }
            yylval.treeNode=new symbolInfo(yytext,"ID");
            yylval.treeNode->leaf=true;
            yylval.treeNode->startLine=line_count;
            yylval.treeNode->endLine=line_count;
            yylval.treeNode->rule="ID :"+(string)yytext;
            return ID;
		}
{STRING_START} {
           tokenStr="";
           logStr="\"";
           temp_line_count=0;
           BEGIN STRING_STATE;
        }
<STRING_STATE>\\n {
           logStr+="\\n";
           tokenStr+="\n";
        }
<STRING_STATE>\\t {
            logStr+="\\t";
            tokenStr+="\t";
        }
<STRING_STATE>\\\\ {
            logStr+="\\\\";
            tokenStr+="\\";
        }
<STRING_STATE>\\\' {
            logStr+="\\\'";
            tokenStr+="\'";
        }
<STRING_STATE>\\\" {
            logStr+="\\\"";
            tokenStr+="\"";
        }
<STRING_STATE>\\a {
            logStr+="\\a";
            tokenStr+="\a";
        }
<STRING_STATE>\\f {
            logStr+="\\f";
            tokenStr+="\f";
        }
<STRING_STATE>\\r {
            logStr+="\\r";
            tokenStr+="\r";
        }
<STRING_STATE>\\b {
            logStr+="\\b";
            tokenStr+="\b";
        }
<STRING_STATE>\\v {
            logStr+="\\v";
            tokenStr+="\v";
        }
<STRING_STATE>\\0 {
            logStr+="\\0";
            tokenStr+="\0";
        }
<STRING_STATE>\\[\r]?[\n] {
            //multiline string
            temp_line_count++;
            string temp(yytext);
            logStr+=temp;
        }
<STRING_STATE>[\r]?[\n] {
            temp_line_count++;
            errorCount++;
            //fprintf(logout,"Error at line# %d: UNFINISHED_STRING %s\n", line_count ,logStr.c_str());
            line_count+=temp_line_count;
            temp_line_count=0;
            logStr="";
            tokenStr="";
            BEGIN INITIAL;
        }
<STRING_STATE>\" {
            if(logStr.find("\n")!=string::npos){
                strLexemeType="MULTI LINE STRING";
            }
            else{
                strLexemeType="SINGLE LINE STRING";
            }
            logStr+="\"";
            //fprintf(tokenout,"<%s, %s>\n",strLexemeType.c_str(),tokenStr.c_str());
            fprintf(logout,"Line# %d: Token <%s> Lexeme %s found\n",line_count,strLexemeType.c_str(),logStr.c_str());
            line_count+=temp_line_count;
            temp_line_count=0;
            logStr="";
            tokenStr="";
            BEGIN INITIAL;
        }
<STRING_STATE>. {
            logStr+=yytext;
            tokenStr+=yytext;
        }

{SINGLE_LINE_COMMENT_START} {
            logComment="//";
            temp_line_count=0;
            BEGIN SINGLE_LINE_COMMENT_STATE;
        }
<SINGLE_LINE_COMMENT_STATE>\\[\r]?[\n] {
            //multiple single line comment with a slash and a enter
            temp_line_count++;
            string temp(yytext);
            logComment+=temp;
        }
<SINGLE_LINE_COMMENT_STATE>[\r]?[\n] {
            //single line comment without a slash at end(end of a single line comment)
            temp_line_count++;
            fprintf(logout,"Line# %d: Token <SINGLE LINE COMMENT> Lexeme %s found\n",line_count,logComment.c_str());
            line_count+=temp_line_count;
            logComment="";
            temp_line_count=0;
            BEGIN INITIAL;
        }
<SINGLE_LINE_COMMENT_STATE>. {
            logComment+=yytext;
        }
{MULTI_LINE_COMMENT_START} {
            logComment="/*";
            temp_line_count=0;
            BEGIN MULTI_LINE_COMMENT_STATE;
        }
<MULTI_LINE_COMMENT_STATE>[^*\n] {
            string temp(yytext);
            logComment+=temp;
        }
<MULTI_LINE_COMMENT_STATE>"*" {
            string temp(yytext);
            logComment+=temp;
        }
<MULTI_LINE_COMMENT_STATE>[\r]?[\n] {
            //new line of the multiline comment
            string temp(yytext);
            logComment+=temp;
            temp_line_count++;
        }
<MULTI_LINE_COMMENT_STATE>\*\/ {
            //end of multiline comment
            string temp(yytext);
            logComment+=temp;
            fprintf(logout,"Line# %d: Token <MULTI LINE COMMENT> Lexeme %s found\n",line_count,logComment.c_str());
            line_count+=temp_line_count;
            logComment="";
            temp_line_count=0;
            BEGIN INITIAL;
        }
<MULTI_LINE_COMMENT_STATE><<EOF>> {
            //unfinished comment
            errorCount++;
            temp_line_count++;
            line_count+=temp_line_count;
            //fprintf(logout,"Error at line# %d: UNFINISHED_COMMENT %s\n", line_count ,logComment.c_str());
            logComment="";
            temp_line_count=0;
            BEGIN INITIAL;
        }
{REDUNDANT_DECIMAL} {
            errorCount++;
            fprintf(logout,"Error at line# %d: TOO_MANY_DECIMAL_POINTS %s\n", line_count ,yytext);
            //fprintf(errorout,"Error at line# %d: TOO_MANY_DECIMAL_POINTS %s\n", line_count ,yytext);

        }
{ILL_NUMBER} {
            errorCount++;
            fprintf(logout,"Error at line# %d: ILLFORMED_NUMBER %s\n", line_count ,yytext);
            //fprintf(errorout,"Error at line# %d: ILLFORMED_NUMBER %s\n", line_count ,yytext);

        }
{INVALID_PRE_SUFF} {
            errorCount++;
            fprintf(logout,"Error at line# %d: INVALID_ID_SUFFIX_NUM_PREFIX %s\n", line_count ,yytext);
            //fprintf(errorout,"Error at line# %d: INVALID_ID_SUFFIX_NUM_PREFIX %s\n", line_count ,yytext);

        }
{MULTIPLE_CHAR} {
            errorCount++;
            fprintf(logout,"Error at line# %d: MULTICHAR_CONST_CHAR %s\n", line_count ,yytext);
            //fprintf(errorout,"Error at line# %d: MULTICHAR_CONST_CHAR %s\n", line_count ,yytext);

        }
{EMPTY_CHAR} {
            errorCount++;
            fprintf(logout,"Error at line# %d: EMPTY_CONST_CHAR %s\n", line_count ,yytext);
            //fprintf(errorout,"Error at line# %d: EMPTY_CONST_CHAR %s\n", line_count ,yytext);

        }
{UNFINISHED_CHAR}  {
            errorCount++;
            fprintf(logout,"Error at line# %d: UNFINISHED_CONST_CHAR %s\n", line_count ,yytext);
            //fprintf(errorout,"Error at line# %d: UNFINISHED_CONST_CHAR %s\n", line_count ,yytext);

}

{WHITESPACE} {}  

{UNRECOGNIZED_CHAR} {
    errorCount++;
    fprintf(logout,"Error at line# %d: UNRECOGNIZED_CHAR %s\n", line_count ,yytext);
    //fprintf(errorout,"Error at line# %d: UNRECOGNIZED_CHAR %s\n", line_count ,yytext);
}

%%
