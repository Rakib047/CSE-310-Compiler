%option noyywrap
%x STRING_STATE
%x SINGLE_LINE_COMMENT_STATE
%x MULTI_LINE_COMMENT_STATE
%{
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<iterator>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

int errorCount=0;
int line_count=1;
int temp_line_count=0;

FILE *logout;
FILE *tokenout;

using namespace std;

class symbolInfo{
    private:
        string symbolName;
        string symbolType;
        symbolInfo* nextSymbolInfo;
        
    public:
  
        symbolInfo(string symbolName,string symbolType){
            this->symbolName=symbolName;
            this->symbolType=symbolType;
            nextSymbolInfo=NULL;
        }    

        void setSymbolName(string symbolName){
            this->symbolName=symbolName;
        }
        

        string getSymbolName(){
            return symbolName;
        }

        void setSymbolType(string symbolType){
            this->symbolType=symbolType;
        }

        string getsymbolType(){
            return symbolType;
        }

        void setnextSymbolInfo(symbolInfo* nextElement){
            nextSymbolInfo=nextElement;
        }

        symbolInfo* getnextSymbolInfo(){
            return nextSymbolInfo;
        }
};

class scopeTable{
    private:
        symbolInfo** hashTable;
        scopeTable* parentScopeTable;
        int scopeTableId;
        int numBucket;
    public:
        scopeTable(int n,scopeTable* parentScopeTable,int scopeTableId){
            hashTable=new symbolInfo*[n];
            this->parentScopeTable=parentScopeTable;
            numBucket=n;
            this->scopeTableId=scopeTableId;

            for(int i=0;i<n;i++){
                hashTable[i]=nullptr;
            }
            //cout<<"ScopeTable# "<<scopeTableId<<" created"<<endl;
        } 

        ~scopeTable(){
            for(int i=0;i<numBucket;i++){
                delete hashTable[i];
            }
            delete[] hashTable;
        }

        int getScopeTableId(){
            return scopeTableId;
        }

        int getNumBucket(){
            return numBucket;
        }

        scopeTable* getParentScopeTable(){
            return parentScopeTable;
        }

     unsigned int SDBMHash(string symbolName) {
	        unsigned int hash = 0;
	        unsigned int i = 0;
	        unsigned int len = symbolName.length();

	        for (i = 0; i < len; i++){
		        hash = ((symbolName[i]) + (hash << 6) + (hash << 16) - hash)%numBucket;
	        }

	        return hash;
        }

    symbolInfo* lookUp(string symbolName){
        int bucketNo=SDBMHash(symbolName)%numBucket;
        symbolInfo* symbolInfoPtr=hashTable[bucketNo];

        int i=1;
        while(symbolInfoPtr){
            if(symbolInfoPtr->getSymbolName()==symbolName){
                //cout<<"'"<<symbolName<<"'"<<" found in ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", "<<i<<endl;
                return symbolInfoPtr;
            }
            symbolInfoPtr=symbolInfoPtr->getnextSymbolInfo();
            i++;
        }
        return nullptr;
    }

    bool insert(symbolInfo symbol){
        string symbolName=symbol.getSymbolName();
        
        
        int bucketNo=SDBMHash(symbolName)%numBucket;
        symbolInfo* symbolInfoPtr=hashTable[bucketNo];
        
        //check if already exist
        int i=0;
        bool flag=false;
        while(symbolInfoPtr){
            if(symbolInfoPtr->getSymbolName()==symbolName){
                flag=true;
                break;
            }
            
            symbolInfoPtr=symbolInfoPtr->getnextSymbolInfo();
            i++;
        }

        if(flag){
            //cout<<"'"<<symbolName<<"'"<<" already exists in the current ScopeTable"<<endl;
            return false;
        }

        symbolInfoPtr=hashTable[bucketNo];


        if(symbolInfoPtr==nullptr){
            hashTable[bucketNo]=new symbolInfo(symbol.getSymbolName(),symbol.getsymbolType());
            //cout<<"Inserted in ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", 1"<<endl;
        }
        else{
            int i=2;
            while(symbolInfoPtr->getnextSymbolInfo()){
                i++;
                symbolInfoPtr=symbolInfoPtr->getnextSymbolInfo();
            }
            symbolInfo* symbolInfoInserted=new symbolInfo(symbol.getSymbolName(),symbol.getsymbolType());
            symbolInfoPtr->setnextSymbolInfo(symbolInfoInserted);
            //cout<<"Inserted in ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", "<<i<<endl;

        }
        return true;
    }

    bool Delete(string symbolName){
        int bucketNo=SDBMHash(symbolName)%numBucket;

        symbolInfo* symbolInfoPtr=hashTable[bucketNo];
        symbolInfo* prevSymbolInfo=nullptr;

        int i=1;
        while(symbolInfoPtr){

            if(symbolInfoPtr->getSymbolName()==symbolName){
                //cout<<"Deleted "<<"'"<<symbolName<<"'"<<" from ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", "<<i<<endl;

                if(!prevSymbolInfo){
                    hashTable[bucketNo]=symbolInfoPtr->getnextSymbolInfo();
                }
                else{
                    prevSymbolInfo->setnextSymbolInfo(symbolInfoPtr->getnextSymbolInfo());
                }
                delete symbolInfoPtr;
                return true;
            }

            i++;
            prevSymbolInfo=symbolInfoPtr;
            symbolInfoPtr=symbolInfoPtr->getnextSymbolInfo();
        }
        //cout<<"Not found in the current ScopeTable"<<endl;
        return false;
    }

    void print(){
        fprintf(logout,"\t");
        //cout<<"\t";
        fprintf(logout,"ScopeTable# %d",scopeTableId);
         fprintf(logout,"\n");
        //cout<<"ScopeTable# "<<scopeTableId<<endl;

        for(int i=1;i<=numBucket;i++){  
            symbolInfo* symbolInfoPtr=hashTable[i-1];
            if(!symbolInfoPtr) continue; 
            fprintf(logout,"\t");
            //cout<<"\t";
            //cout<<i<<"--> ";
            fprintf(logout,"%d--> ",i);
            while(symbolInfoPtr){
                fprintf(logout,"<%s,%s> ",symbolInfoPtr->getSymbolName().c_str(),symbolInfoPtr->getsymbolType().c_str());
                //cout<<"<"<<symbolInfoPtr->getSymbolName()<<","<<symbolInfoPtr->getsymbolType()<<"> ";
                symbolInfoPtr=symbolInfoPtr->getnextSymbolInfo();
            }
            fprintf(logout,"\n");
            //cout<<endl;
        }
    }
};

    

class symbolTable{
    private:
        scopeTable* currentScopeTable;
        int currentScopeTableSize;
        static int scopeTableCount;
        static bool isEmpty;
    
    public:
        symbolTable(int currentScopeTableSize){
            this->currentScopeTableSize=currentScopeTableSize;
            currentScopeTable=new scopeTable(currentScopeTableSize,nullptr,++scopeTableCount);    
        }

        void enterScope(){
            scopeTable* temp=new scopeTable(currentScopeTableSize,currentScopeTable,++scopeTableCount);
            currentScopeTable=temp;
        }

        void exitScope(string command){
            if(currentScopeTable->getScopeTableId()==1 && command!="Q"){
                //cout<<"ScopeTable# 1 cannot be removed"<<endl;
                return;
            }
            if(currentScopeTable->getScopeTableId()==1){
                isEmpty=true;
            }
            scopeTable* temp=currentScopeTable;
            currentScopeTable=currentScopeTable->getParentScopeTable();
            //cout<<"ScopeTable# "<<temp->getScopeTableId()<<" removed"<<endl;
            delete temp;
        }

        bool insert(symbolInfo symbol){
            bool retValue=currentScopeTable->insert(symbol);
            return retValue;
        }

        bool remove(string symbolName){
            bool retValue=currentScopeTable->Delete(symbolName);
            return retValue;
        }

        symbolInfo* lookup(string symbolName){
            scopeTable* scopeTablePtr=currentScopeTable;

            while(scopeTablePtr){
                symbolInfo* foundScopeTable=scopeTablePtr->lookUp(symbolName);
                if(foundScopeTable){
                    return foundScopeTable;
                }
                else{
                    scopeTablePtr=scopeTablePtr->getParentScopeTable();
                }
            }
            //cout<<"'"<<symbolName<<"'"<<" not found in any of the ScopeTables"<<endl;
            return nullptr;
        }

        void printCurrentScope(){
            currentScopeTable->print();
        }

        void printAllScope(){
            scopeTable* scopeTablePtr=currentScopeTable;
            while(scopeTablePtr){
                scopeTablePtr->print();
                scopeTablePtr=scopeTablePtr->getParentScopeTable();
            }
        }

        static int getScopeTableCount(){
            return scopeTableCount;
        }

        static bool getIsEmpty(){
            return isEmpty;
        }
};

int symbolTable::scopeTableCount=0;
bool symbolTable::isEmpty=false;

symbolTable symbolTableObj(10);

string tokenStr,logStr,strLexemeType,logComment,commentLexemeType;
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
INCOP "++"|"--"
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
			fprintf(tokenout,"<IF, if>\n");
			fprintf(logout,"Line# %d: Token <IF> Lexeme %s found\n",line_count,yytext);
		}
		
"for"	{
			fprintf(tokenout,"<FOR, for>\n");
			fprintf(logout,"Line# %d: Token <FOR> Lexeme %s found\n",line_count,yytext);
		}
"do"    {
			fprintf(tokenout,"<DO, do>\n");
			fprintf(logout,"Line# %d: Token <DO> Lexeme %s found\n",line_count,yytext);

		}
"int"   {
			fprintf(tokenout,"<INT, int>\n");
			fprintf(logout,"Line# %d: Token <INT> Lexeme %s found\n",line_count,yytext);
		}
"float" {
			fprintf(tokenout,"<FLOAT, float>\n");
			fprintf(logout,"Line# %d: Token <FLOAT> Lexeme %s found\n",line_count,yytext);
		}
"void"	{	
			fprintf(tokenout,"<VOID, void>\n");
			fprintf(logout,"Line# %d: Token <VOID> Lexeme %s found\n",line_count,yytext);
		}

"switch" {
			fprintf(tokenout,"<SWITCH, switch>\n");
			fprintf(logout,"Line# %d: Token <SWITCH> Lexeme %s found\n",line_count,yytext);
		}
"default" {
			fprintf(tokenout,"<DEFAULT, default>\n");
			fprintf(logout,"Line# %d: Token <DEFAULT> Lexeme %s found\n",line_count,yytext);
		}
"else"	{
			fprintf(tokenout,"<ELSE, else>\n");
			fprintf(logout,"Line# %d: Token <ELSE> Lexeme %s found\n",line_count,yytext);
		}
"while"	{
			fprintf(tokenout,"<WHILE, while>\n");
			fprintf(logout,"Line# %d: Token <WHILE> Lexeme %s found\n",line_count,yytext);
		}
"break"	{
			fprintf(tokenout,"<BREAK, break>\n");
			fprintf(logout,"Line# %d: Token <BREAK> Lexeme %s found\n",line_count,yytext);
		}
"char"	{
			fprintf(tokenout,"<CHAR, char>\n");
			fprintf(logout,"Line# %d: Token <CHAR> Lexeme %s found\n",line_count,yytext);
		}
"double" {
			fprintf(tokenout,"<DOUBLE, double>\n");
			fprintf(logout,"Line# %d: Token <DOUBLE> Lexeme %s found\n",line_count,yytext);
		}
"return" {
			fprintf(tokenout,"<RETURN, return>\n");
			fprintf(logout,"Line# %d: Token <RETURN> Lexeme %s found\n",line_count,yytext);
		}
"case"  {
			fprintf(tokenout,"<CASE, case>\n");
			fprintf(logout,"Line# %d: Token <CASE> Lexeme %s found\n",line_count,yytext);
		}
"continue" {
			fprintf(tokenout,"<CONTINUE, continue>\n");
			fprintf(logout,"Line# %d: Token <CONTINUE> Lexeme %s found\n",line_count,yytext);
		}
{INTEGER} {		
			fprintf(tokenout,"<CONST_INT, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <CONST_INT> Lexeme %s found\n",line_count,yytext);
		}
{FLOAT} {
			fprintf(tokenout,"<CONST_FLOAT, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <CONST_FLOAT> Lexeme %s found\n",line_count,yytext);
		}
{ADDOP} {
			fprintf(tokenout,"<ADDOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <ADDOP> Lexeme %s found\n",line_count,yytext);		
		}
{MULOP} {
			fprintf(tokenout,"<MULOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <MULOP> Lexeme %s found\n",line_count,yytext);		
		}	
{INCOP} {
			fprintf(tokenout,"<INCOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <INCOP> Lexeme %s found\n",line_count,yytext);		
		}						
{RELOP}	{
			fprintf(tokenout,"<RELOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <RELOP> Lexeme %s found\n",line_count,yytext);
		}
{ASSIGNOP} {
			fprintf(tokenout,"<ASSIGNOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <ASSIGNOP> Lexeme %s found\n",line_count,yytext);		
		}	
{LOGICOP} {
			fprintf(tokenout,"<LOGICOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <LOGICOP> Lexeme %s found\n",line_count,yytext);		
		}	
{BITOP} {
			fprintf(tokenout,"<BITOP, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <BITOP> Lexeme %s found\n",line_count,yytext);		
		}	
"!" {
			fprintf(tokenout,"<NOT, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <NOT> Lexeme %s found\n",line_count,yytext);		
		}	
"(" {
			fprintf(tokenout,"<LPAREN, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <LPAREN> Lexeme %s found\n",line_count,yytext);		
		}	
")" {
			fprintf(tokenout,"<RPAREN, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <RPAREN> Lexeme %s found\n",line_count,yytext);		
		}
"{" {
            symbolTableObj.enterScope();
			fprintf(tokenout,"<LCURL, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <LCURL> Lexeme %s found\n",line_count,yytext);		
		}
"}" {
            symbolTableObj.exitScope("E");
			fprintf(tokenout,"<RCURL, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <RCURL> Lexeme %s found\n",line_count,yytext);		
		}
"[" {
			fprintf(tokenout,"<LSQUARE, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <LSQUARE> Lexeme %s found\n",line_count,yytext);		
		}
"]" {
			fprintf(tokenout,"<RSQUARE, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <RSQUARE> Lexeme %s found\n",line_count,yytext);		
		}
"," {
			fprintf(tokenout,"<COMMA, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <COMMA> Lexeme %s found\n",line_count,yytext);		
		}
";" {
			fprintf(tokenout,"<SEMICOLON, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <SEMICOLON> Lexeme %s found\n",line_count,yytext);		
		}
{UNFINISHED_ESCAPE_CHAR} {
            errorCount++;
            fprintf(logout,"Error at line# %d: UNFINISHED_CONST_CHAR %s\n", line_count ,yytext);
        }
{SINGLE_CHAR_LITERAL} {
            string character="";
            character+=yytext[1];
			fprintf(tokenout,"<CONST_CHAR, %s>\n",character.c_str());
			fprintf(logout,"Line# %d: Token <CONST_CHAR> Lexeme %s found\n",line_count,character.c_str());
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
			fprintf(tokenout,"<CONST_CHAR, %s>\n",character.c_str());
			fprintf(logout,"Line# %d: Token <CONST_CHAR> Lexeme %s found\n",line_count,character.c_str());
		}

{IDENTIFIER} {
            
			fprintf(tokenout,"<ID, %s>\n",yytext);
			fprintf(logout,"Line# %d: Token <ID> Lexeme %s found\n",line_count,yytext);

            bool checkExistance=symbolTableObj.insert(symbolInfo(yytext,"ID"));
            if(!checkExistance){
                fprintf(logout,"\t%s already exisits in the current ScopeTable\n",yytext);
            }
            else{
            symbolTableObj.printAllScope();
            }
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
            fprintf(logout,"Error at line# %d: UNFINISHED_STRING %s\n", line_count ,logStr.c_str());
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
            fprintf(tokenout,"<%s, %s>\n",strLexemeType.c_str(),tokenStr.c_str());
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
<MULTI_LINE_COMMENT_STATE>[^\n] {
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
            fprintf(logout,"Error at line# %d: UNFINISHED_COMMENT %s\n", line_count ,logComment.c_str());
            logComment="";
            temp_line_count=0;
            BEGIN INITIAL;
        }
{REDUNDANT_DECIMAL} {
            errorCount++;
            fprintf(logout,"Error at line# %d: TOO_MANY_DECIMAL_POINTS %s\n", line_count ,yytext);
        }
{ILL_NUMBER} {
            errorCount++;
            fprintf(logout,"Error at line# %d: ILLFORMED_NUMBER %s\n", line_count ,yytext);
        }
{INVALID_PRE_SUFF} {
            errorCount++;
            fprintf(logout,"Error at line# %d: INVALID_ID_SUFFIX_NUM_PREFIX %s\n", line_count ,yytext);
        }
{MULTIPLE_CHAR} {
            errorCount++;
            fprintf(logout,"Error at line# %d: MULTICHAR_CONST_CHAR %s\n", line_count ,yytext);
        }
{EMPTY_CHAR} {
            errorCount++;
            fprintf(logout,"Error at line# %d: EMPTY_CONST_CHAR %s\n", line_count ,yytext);
        }
{UNFINISHED_CHAR}  {
            errorCount++;
            fprintf(logout,"Error at line# %d: UNFINISHED_CONST_CHAR %s\n", line_count ,yytext);
}

{WHITESPACE} {}  

{UNRECOGNIZED_CHAR} {
    errorCount++;
    fprintf(logout,"Error at line# %d: UNRECOGNIZED_CHAR %s\n", line_count ,yytext);
}

%%

int main(int argc, char** argv) {
	if(argc!=2){
		printf("Please provide input file name and try again\n");
		return 0;
	}
	
	FILE *fin=fopen(argv[1],"r");
	if(fin==NULL){
		printf("Cannot open specified file\n");
		return 0;
	}
	
	logout= fopen("log.txt","w");
	tokenout= fopen("token.txt","w");

	yyin= fin;
	yylex();
	fclose(yyin);
    symbolTableObj.printAllScope();
    fprintf(logout,"Total lines: %d\n",line_count);
    fprintf(logout,"Total errors: %d",errorCount);
	fclose(tokenout);
	fclose(logout);
	return 0;
}
