%{

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

%}


%union{
    symbolInfo* treeNode;
}

%token<treeNode> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE
%token<treeNode> CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP INCOP DECOP RELOP ASSIGNOP LOGICOP NOT LPAREN 
%token<treeNode> RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON ID PRINTLN

%type<treeNode> start program unit var_declaration func_declaration func_definition
type_specifier parameter_list compound_statement scopeController statements declaration_list
statement expression_statement expression variable logic_expression simple_expression term
unary_expression factor argument_list arguments rel_expression

%nonassoc LOWER_THAN_ELSE 
%nonassoc ELSE

%%
start : program {         
                $$=new symbolInfo("start","program");
                $$->insertToChildList($1);
                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;

                rulePrint("start", "program");

                printTree($$,"");
        }
        
program : program unit {
               
                $$ = new symbolInfo("program", "program unit");
                
                rulePrint("program", "program unit");

                $$->insertToChildList($1);
                $$->insertToChildList($2);

                $$->startLine=$1->startLine;
                $$->endLine=$2->endLine;

        }
	    | unit{
                $$ = new symbolInfo("program", "unit");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;

                rulePrint("program", "unit");
        }
	    ;
unit    : var_declaration {
                $$ = new symbolInfo("unit", "var_declaration");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;

                rulePrint("unit", "var_declaration");
     } 
        | func_declaration{
                $$ = new symbolInfo("unit", "func_declaration");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;

                rulePrint("unit", "func_declaration");

     }   

        | func_definition{
                $$ = new symbolInfo("unit", "func_definition");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;

                rulePrint("unit", "func_definition");
     }
     ; 
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON{
  
                                $$ = new symbolInfo("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);
                                $$->insertToChildList($5);
                                $$->insertToChildList($6);

                                $$->startLine=$1->startLine;
                                $$->endLine=$6->endLine;

                                

                                string _id = $2->getSymbolName();
                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup($2->getSymbolName()); //need to check all scopetables
                                //declaration of same name function
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                            
                                }
                                else{
                                    //symbolInfo *newFunc = new symbolInfo(_id, "ID");
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+$1->getSymbolName());
                            
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

                                    newFunc->setTypeVar($1->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                    
                                    //func.push_back(newFunc);
                                }



                                rulePrint("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");


                } 
                |type_specifier ID LPAREN parameter_list RPAREN error {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(string a)
                                */
                                $$ = new symbolInfo("func_declaration","RPAREN error");
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);
                                $$->insertToChildList($5);

                                $$->startLine=$1->startLine;
                                $$->endLine=$5->endLine;

                                yyerror("RPAREN of func_declaration");
                                errorCount++;
                                string _id = $2->getSymbolName();
                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup($2->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    //symbolInfo *newFunc = new symbolInfo(_id, "ID");
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+$1->getSymbolName());

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

                                    newFunc->setTypeVar($1->getSymbolName());
                        
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    //table.insert(newFunc);
                                }
                                

                }
                |type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(int a+b);
                                */
                                $$ = new symbolInfo("func_declaration","parameter_list error");
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);
                                $$->insertToChildList($6);
                                $$->insertToChildList($7);

                                $$->startLine=$1->startLine;
                                $$->endLine=$7->endLine;

                                yyerror("parameter_list of func_declaration");
                                errorCount++;
                                string _id = $2->getSymbolName();

                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup($2->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+$1->getSymbolName());


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

                                    newFunc->setTypeVar($1->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    //table.insert(newFunc);
                                }



                                rulePrint("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
                                

                }
                | type_specifier ID LPAREN parameter_list error RPAREN error {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(int a+b)*/
                               $$ = new symbolInfo("func_declaration","parameter_list error RPAREN error");    
                               $$->insertToChildList($1);
                               $$->insertToChildList($2);
                               $$->insertToChildList($3);
                               $$->insertToChildList($4);
                               $$->insertToChildList($6);

                                $$->startLine=$1->startLine;
                                $$->endLine=$6->endLine;

                               yyerror("parameter_list,RPAREN of func_declaration");
                               errorCount++;
                                string _id = $2->getSymbolName();

                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup($2->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+$1->getSymbolName());


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

                                    newFunc->setTypeVar($1->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    //table.insert(newFunc);
                                }



                               // rulePrint("func_declaration", "type_specifier ID LPAREN parameter_list RPAREN");
                                
                }
                | type_specifier ID LPAREN RPAREN SEMICOLON{
         
                                $$ = new symbolInfo("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);
                                $$->insertToChildList($5);

                                $$->startLine=$1->startLine;
                                $$->endLine=$5->endLine;

                                

                                //string stmt = $1->getSymbolName()+ " " + $2->getSymbolName() + "();";
                                string _id = $2->getSymbolName();
                                
                                //SymbolInfo *checker = new SymbolInfo();
                                symbolInfo *checker = table.lookup($2->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+$1->getSymbolName());                      
                                    //symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION");
                                    newFunc->setTypeVar($1->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                    if(newFunc->getSymbolName()=="foo")
                                    //cout<<"insert address from bison file:"<<newFunc<<endl;
                                    //cout<<newFunc->getSymbolName()<<endl;
                                    func.push_back(newFunc);
                                    
                                }



                                rulePrint("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");

                }
                | type_specifier ID LPAREN RPAREN error {
                                /*
                                    Error recovery of func_definition like:
                                    int foo()
                                */
                                $$ = new symbolInfo("func_declaration","RPAREN error");
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);

                                $$->startLine=$1->startLine;
                                $$->endLine=$4->endLine;

                                yyerror("RPAREN of func_declaration");
                                errorCount++;
                                string stmt = $1->getSymbolName()+ " " + $2->getSymbolName() + "()";
                                string _id = $2->getSymbolName();

                                //$$ = new symbolInfo(stmt,"func_declaration");
                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup($2->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+$1->getSymbolName());
                                    newFunc->setTypeVar($1->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                }

                                rulePrint("func_declaration", "type_specifier ID LPAREN RPAREN");
                }
                | type_specifier ID LPAREN error RPAREN SEMICOLON {
                                /*
                                    Error recovery of func_definition like:
                                    int foo(*);
                                */
                                $$ = new symbolInfo("func_declaration","LPAREN error");
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($5);
                                $$->insertToChildList($6);

                                $$->startLine=$1->startLine;
                                $$->endLine=$6->endLine;

                                yyerror("LPAREN of func_declaration");
                                errorCount++;
                                string _id = $2->getSymbolName();


                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup($2->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+$1->getSymbolName());
                                    newFunc->setTypeVar($1->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                }



                                //rulePrint("func_declaration", "type_specifier ID LPAREN RPAREN SEMICOLON");
                                
                }
                | type_specifier ID LPAREN error RPAREN error{
                                /*
                                    Error recovery of func_definition like:
                                    int foo(*)
                                */
                                $$ = new symbolInfo("func_declaration","LPAREN error RPAREN error");
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($5);

                                $$->startLine=$1->startLine;
                                $$->endLine=$5->endLine;

                                yyerror("LPAREN,RPAREN of func_declaration");
                                errorCount++;
                                string _id = $2->getSymbolName();

                               
                                symbolInfo *checker = new symbolInfo();
                                checker = table.lookup($2->getSymbolName()); //need to check all scopetables
                                if(checker!=nullptr){
                                    yyerror("Multiple Declaration of "+_id);
                                    errorCount++;
                                }
                                else{
                                    symbolInfo *newFunc = new symbolInfo(_id, "FUNCTION,"+$1->getSymbolName());
                                    newFunc->setTypeVar($1->getSymbolName());
                                    newFunc->setFuncSt("declaration"); //marked func statement type as "declaration"
                                    table.insert(newFunc);
                                }

                                //rulePrint("func_declaration", "type_specifier ID LPAREN RPAREN");
                              
                }
		        ;
func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement {
                        string _def = $1->getSymbolName() + " " + $2->getSymbolName() + "(" + $4->getSymbolName() + ")";

                                symbolInfo *returnedSym = table.lookup($2->getSymbolName());
                                if(returnedSym!=nullptr){
                                    string retSymFuncST = returnedSym->getFuncSt();
                                    string retSymType = returnedSym->getTypeVar();
                                    if(retSymFuncST!="declaration"){
                                        yyerror("Multiple Declaration of " + $2->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType!=$1->getSymbolName()){
                                        yyerror("Return type mismatch with function declaration in function "+$2->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType==$1->getSymbolName()){
                                        vector<string> decParamsTypeList = returnedSym->getList1(); //type list of paramsList in declaration
                                        if(decParamsTypeList.size() == paramsList.size()){
                                            bool checker = true;
                                            for(int i=0; i<paramsList.size(); i++){
                                                string _paramType = paramsList[i].first;
                                                if(decParamsTypeList[i]!=_paramType){
                                                    int x = i+1;
                                                    yyerror(x + "th argument mismatch in function "+$2->getSymbolName());
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
                                            yyerror("Total number of arguments mismatch with declaration in function "+$2->getSymbolName());
                                            errorCount++;
                                        }
                                        decParamsTypeList.clear();
                                    }
                                }
                                else{
                                    symbolInfo *symbol = new symbolInfo($2->getSymbolName(), "FUNCTION,"+$1->getSymbolName());
                                    
                                    //symbolInfo *symbol = new symbolInfo($2->getSymbolName(), "FUNCTION");
                                    
                                    int params_no = paramsList.size();
  
                                    for(int i=0; i<params_no; i++){
                                        string paramsType = paramsList[i].first;
                                        string paramsName = paramsList[i].second;
                                        symbol->insertToList1(paramsType);
                                        symbol->insertToList2(paramsName);
                                    }
                                    symbol->setTypeVar($1->getSymbolName());
                
                                    symbol->setFuncSt("definition");
                                    table.insert(symbol);
                                    //func.push_back(symbol);
                                    //cout<<symbol->getTypeVar()<<" "<<symbol->getName()<<endl;
                                    
                                }
                                $$ = new symbolInfo("func_definition", "type_specifier ID LPAREN parameter_list RPAREN compound_statement");                               
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);
                                $$->insertToChildList($5);
                                $$->insertToChildList($6);

                                $$->startLine=$1->startLine;
                                $$->endLine=$6->endLine;
                }

                | type_specifier ID LPAREN parameter_list error RPAREN compound_statement {
                                 yyerror("parameter_list of func_definition");
                                 errorCount++;
                                string _def = $1->getSymbolName() + " " + $2->getSymbolName() + "(" + $4->getSymbolName() + ")";

                                symbolInfo *returnedSym = table.lookup($2->getSymbolName());
                                if(returnedSym!=nullptr){
                                    string retSymFuncST = returnedSym->getFuncSt();
                                    string retSymType = returnedSym->getTypeVar();
                                    if(retSymFuncST!="declaration"){
                                        yyerror("Multiple Declaration of " + $2->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType!=$1->getSymbolName()){
                                        yyerror("Return type mismatch with function declaration in function "+$2->getSymbolName());
                                        errorCount++;

                                    }
                                    else if(retSymFuncST=="declaration" && retSymType==$1->getSymbolName()){
                                        vector<string> decParamsTypeList = returnedSym->getList1(); //type list of paramsList in declaration
                                        if(decParamsTypeList.size() == paramsList.size()){
                                            bool checker = true;
                                            for(int i=0; i<paramsList.size(); i++){
                                                string _paramType = paramsList[i].first;
                                                if(decParamsTypeList[i]!=_paramType){
                                                    int x = i+1;
                                                    yyerror(x + "th argument mismatch in function "+$2->getSymbolName());
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
                                            yyerror("Total number of arguments mismatch with declaration in function "+$2->getSymbolName());
                                            errorCount++;
                                        }
                                        decParamsTypeList.clear();
                                    }
                                }
                                else{
                                    symbolInfo *symbol = new symbolInfo($2->getSymbolName(), "FUNCTION,"+$1->getSymbolName());
                                    int params_no = paramsList.size();
                                    for(int i=0; i<params_no; i++){
                                        string paramsType = paramsList[i].first;
                                        string paramsName = paramsList[i].second;
                                        symbol->insertToList1(paramsType);
                                        symbol->insertToList2(paramsName);
                                    }
                                    symbol->setTypeVar($1->getSymbolName());
                                    symbol->setFuncSt("definition");
                                    //table.insert(symbol);
                                    
                                }

                                $$ = new symbolInfo("func_definition", "parameter_list error");
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);
                                $$->insertToChildList($6);
                                $$->insertToChildList($7);

                                $$->startLine=$1->startLine;
                                $$->endLine=$7->endLine;
                }

                | error LPAREN parameter_list RPAREN compound_statement {
                        yyerror("type specifier of func_definition");
                        errorCount++;
                                ErrFunc = false;
                                $$ = new symbolInfo("func_definition", "error LPAREN");
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);
                                $$->insertToChildList($5);

                                $$->startLine=$2->startLine;
                                $$->endLine=$5->endLine;
                }

                | type_specifier ID LPAREN RPAREN compound_statement {
                                string _def = $1->getSymbolName() + " " + $2->getSymbolName() + "()";
                                
                                symbolInfo *returnedSym = table.lookup($2->getSymbolName());
                                for(auto x:func){
                                    if($2->getSymbolName()==x->getSymbolName()){
                                        returnedSym=x;
                                    }
                                }
                                
                                if(returnedSym!=nullptr){
                                    string retSymFuncST = returnedSym->getFuncSt();
                                    string retSymType = returnedSym->getTypeVar();
                                    if(retSymFuncST!="declaration"){
                                        errorCount++;
                                        yyerror("Multiple Declaration of " + $2->getSymbolName());
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType!=$1->getSymbolName()){
                                        yyerror("Return type mismatch with function declaration in function "+$2->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType==$1->getSymbolName()){
                                        vector<string> decParamsTypeList = returnedSym->getList1(); //type list of paramsList in declaration
                                        if(decParamsTypeList.size() == 0){
                                            returnedSym->setFuncSt("definition");     
                                        }
                                        else{
                                            errorCount++;
                                            yyerror("Total number of arguments mismatch with declaration in function "+$2->getSymbolName());
                                        }
                                        decParamsTypeList.clear();
                                    }
                                }
                                else{
                                    symbolInfo *symbol = new symbolInfo($2->getSymbolName(), "FUNCTION,"+$1->getSymbolName());
                                    int params_no = paramsList.size();

                                    symbol->setTypeVar($1->getSymbolName());
                                    symbol->setFuncSt("definition");
                                    table.insert(symbol);
                                }

                                $$ = new symbolInfo("func_definition", "type_specifier ID LPAREN RPAREN compound_statement");
                                
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($4);
                                $$->insertToChildList($5);

                                $$->startLine=$1->startLine;
                                $$->endLine=$5->endLine;                              
                }

| type_specifier ID LPAREN error RPAREN compound_statement {
                                yyerror("LPAREN of func_definition");
                                errorCount++;
                                string _def = $1->getSymbolName() + " " + $2->getSymbolName() + "()";

                                symbolInfo *returnedSym = table.lookup($2->getSymbolName());
                                if(returnedSym!=nullptr){
                                    string retSymFuncST = returnedSym->getFuncSt();
                                    string retSymType = returnedSym->getTypeVar();
                                    if(retSymFuncST!="declaration"){
                                        yyerror("Multiple Declaration of " + $2->getSymbolName());
                                        errorCount++;
                                    }
                                    else if(retSymFuncST=="declaration" && retSymType!=$1->getSymbolName()){
                                        yyerror("Return type mismatch with function declaration in function "+$2->getSymbolName());
                                        errorCount++;

                                    }
                                    else if(retSymFuncST=="declaration" && retSymType==$1->getSymbolName()){
                                        vector<string> decParamsTypeList = returnedSym->getList1(); //type list of paramsList in declaration
                                        if(decParamsTypeList.size() == 0){
                                            returnedSym->setFuncSt("definition");
                                            
                                        }
                                        else{
                                            yyerror("Total number of arguments mismatch with declaration in function "+$2->getSymbolName());
                                            errorCount++;
                                        }
                                        decParamsTypeList.clear();
                                    }
                                }
                                else{
                                    symbolInfo *symbol = new symbolInfo($2->getSymbolName(), "FUNCTION,"+$1->getSymbolName());
                                    int params_no = paramsList.size();

                                    symbol->setTypeVar($1->getSymbolName());
                                    symbol->setFuncSt("definition");
                                    table.insert(symbol);
                                    
                                }
                                $$ = new symbolInfo("func_definition", "LPAREN error");
                                
                                $$->insertToChildList($1);
                                $$->insertToChildList($2);
                                $$->insertToChildList($3);
                                $$->insertToChildList($5);
                                $$->insertToChildList($6);

                                $$->startLine=$1->startLine;
                                $$->endLine=$6->endLine; 
                }

                | error compound_statement {        

                                yyerror("error of func_definition");
                                errorCount++;
                                if(ErrFunc==false){
                                    ErrFunc = true;
                                    paramsList.clear();
                                } 
                                ErrFunc = false;
                                $$ = new symbolInfo("func_definition", "error compound_statement"); 
                                $$->insertToChildList($2);  

                                $$->startLine=$2->startLine;
                                $$->endLine=$2->endLine; 
                }
 		        ;  
parameter_list  : parameter_list COMMA type_specifier ID{
                        

                      
                        $$ = new symbolInfo("parameter_list", "parameter_list COMMA type_specifier ID");
                        $$->insertToChildList($1);
                        $$->insertToChildList($2);
                        $$->insertToChildList($3);
                        $$->insertToChildList($4);

                        $$->startLine=$1->startLine;
                        $$->endLine=$4->endLine; 

                        pair<string, string> newParam;
                        newParam.first = $3->getSymbolName(); //type
                        newParam.second = $4->getSymbolName(); //var_name
                        paramsList.push_back(newParam);
                        //cout<<paramsList.size()<<endl;
                        rulePrint("parameter_list", "parameter_list COMMA type_specifier ID");


                }

                | parameter_list error COMMA type_specifier ID{
                        /*
                            Error recovery of parameter_list like:
                            int foo(int a+b, float c)
                        */
                       
                        $$ = new symbolInfo("parameter_list", "parameter_list error");
                        $$->insertToChildList($1);
                        $$->insertToChildList($3);
                        $$->insertToChildList($4);
                        $$->insertToChildList($5);

                        $$->startLine=$1->startLine;
                        $$->endLine=$5->endLine; 
                        
                        yyerror("parameter_list of parameter_list");
                        errorCount++;
                        pair<string, string> newParam;
                        newParam.first = $4->getSymbolName(); //type
                        newParam.second = $5->getSymbolName(); //var_name
                        paramsList.push_back(newParam);

                }
                
		        | parameter_list COMMA type_specifier{
 
                        $$ = new symbolInfo("parameter_list", "parameter_list COMMA type_specifier");   
                        $$->insertToChildList($1);
                        $$->insertToChildList($2);
                        $$->insertToChildList($3);

                        $$->startLine=$1->startLine;
                        $$->endLine=$3->endLine; 
                        
                        pair<string, string> newParam;
                        newParam.first = $3->getSymbolName(); //type
                        newParam.second = ""; //var_name=empty
                        paramsList.push_back(newParam);
                        rulePrint("parameter_list", "parameter_list COMMA type_specifier");

                }

                | parameter_list error COMMA type_specifier{
                        /*
                            Error recovery of parameter_list like:
                            int foo(int a+b, float)
                        */
                        $$ = new symbolInfo("parameter_list", "parameter_list error");
                        $$->insertToChildList($1);
                        $$->insertToChildList($3);
                        $$->insertToChildList($4);

                        $$->startLine=$1->startLine;
                        $$->endLine=$4->endLine; 

                        yyerror("parameter_list of parameter_list");
                        errorCount++;
                        pair<string, string> newParam;
                        newParam.first = $4->getSymbolName(); //type
                        newParam.second = ""; //var_name=empty
                        paramsList.push_back(newParam);
                        

                } 

 		        | type_specifier ID{   
                        $$ = new symbolInfo("parameter_list", "type_specifier ID");
                        $$->insertToChildList($1);
                        $$->insertToChildList($2);

                        $$->startLine=$1->startLine;
                        $$->endLine=$2->endLine; 

                        pair<string, string> newParam;
                        newParam.first = $1->getSymbolName(); //type
                        newParam.second = $2->getSymbolName(); //var_name=empty
                        paramsList.push_back(newParam);
                        rulePrint("parameter_list", "type_specifier ID");
                        
                }
		        | type_specifier{
                        $$ = new symbolInfo("parameter_list", "type_specifier");
                        $$->insertToChildList($1);

                        $$->startLine=$1->startLine;
                        $$->endLine=$1->endLine; 

                        pair<string, string> newParam;
                        newParam.first = $1->getSymbolName(); //type
                        newParam.second = ""; //var_name=empty
                        paramsList.push_back(newParam);
                        rulePrint("parameter_list", "type_specifier");
                }
 		        ;
compound_statement : LCURL scopeController statements RCURL{
                           
                        $$ = new symbolInfo("compound_statement", "LCURL statements RCURL");
                        $$->insertToChildList($1);
                        $$->insertToChildList($3);
                        $$->insertToChildList($4);

                        $$->startLine=$1->startLine;
                        $$->endLine=$4->endLine; 


                        rulePrint("compound_statement", "LCURL statements RCURL");
                        table.printAllScope(logout);
                        table.exitScope();
            
                    }
                    | LCURL scopeController RCURL{
                        $$ = new symbolInfo("compound_statement", "LCURL RCURL");
                        $$->insertToChildList($1);
                        $$->insertToChildList($3);

                        $$->startLine=$1->startLine;
                        $$->endLine=$3->endLine; 
                        

                        rulePrint("compound_statement", "LCURL RCURL");
                        table.printAllScope(logout);
                        table.exitScope();
                        
                    }
                    | LCURL scopeController statements error RCURL{
                        $$ = new symbolInfo("compound_statement", "statements error");
                        $$->insertToChildList($1);
                        $$->insertToChildList($3);
                        $$->insertToChildList($5);

                        $$->startLine=$1->startLine;
                        $$->endLine=$5->endLine; 

                        yyerror("statements of compound_statement");
                        errorCount++;
                        table.printAllScope(logout);
                        table.exitScope();
                        
                    }
                    | LCURL scopeController error statements RCURL {
  
                        $$ = new symbolInfo("compound_statement", "scopeController error");  
                        $$->insertToChildList($1);
                        $$->insertToChildList($4);
                        $$->insertToChildList($5);

                        $$->startLine=$1->startLine;
                        $$->endLine=$5->endLine; 

                        //rulePrint("compound_statement", "LCURL statements RCURL");
                        table.printAllScope(logout);
                        table.exitScope();
                    
                    }
                    
                    ;                       
scopeController: {

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

            }
            ;
var_declaration : type_specifier declaration_list SEMICOLON{
  
                    $$ = new symbolInfo("var_declaration", "type_specifier declaration_list SEMICOLON");
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);
                    $$->insertToChildList($3);

                    $$->startLine=$1->startLine;
                    $$->endLine=$3->endLine; 
                    
                    string varType = $1->getSymbolName();
                    string varName = $2->getSymbolName();

                    // Error check: varType = void
                    if(varType=="void"){
                        string errormsg = "Variable type can't be void";
                        yyerror(errormsg);
                        errorCount++;
                    }
                    else{
                        vector<string> list1 = $2->getList1();
                        vector<string> list2 = $2->getList2();

                        for(int i=0; i<list1.size(); i++){
                            
                            string idType=$1->getSymbolName();
                            if(list2[i]=="[]") idType="ARRAY,"+$1->getSymbolName();
                            symbolInfo *symbol = new symbolInfo(list1[i],idType);
                            symbol->setTypeVar(varType+list2[i]);
                            
                            if(table.insert(symbol)==false){
                                yyerror("Multiple declaration of "+list1[i]);
                                errorCount++;
                            }

                        }

                        
                    }

            
                    rulePrint("var_declaration", "type_specifier declaration_list SEMICOLON");
                }
 		        ;
type_specifier	: INT{
                    
                    $$ = new symbolInfo("type_specifier", "INT");     
                    $$->insertToChildList($1);

                    $$->startLine=$1->startLine;
                    $$->endLine=$1->endLine; 
                    
                     rulePrint("type_specifier", "INT");
                }
 		        | FLOAT{
                   
                    $$ = new symbolInfo("type_specifier", "FLOAT");
                    $$->insertToChildList($1);

                    $$->startLine=$1->startLine;
                    $$->endLine=$1->endLine; 
                    
                    rulePrint("type_specifier", "FLOAT");
                }
 		        | VOID{
                    
                    $$ = new symbolInfo("type_specifier", "VOID");
                    $$->insertToChildList($1);

                    $$->startLine=$1->startLine;
                    $$->endLine=$1->endLine; 
                    
                    rulePrint("type_specifier", "VOID");
                }
 		        ;
declaration_list : declaration_list COMMA ID{

                    $$=new symbolInfo("declaration_list","declaration_list COMMA ID");
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);
                    $$->insertToChildList($3);

                    $$->startLine=$1->startLine;
                    $$->endLine=$3->endLine;

                    string new_list = $1->getSymbolName()+ "," + $3->getSymbolName();
                    $1->insertToList1($3->getSymbolName()); //append new id to parent list
                    $1->insertToList2("");
                    $1->setSymbolName(new_list);
                    rulePrint("declaration_list", "declaration_list COMMA ID");
                    table.insert($3);
                }
                | declaration_list error COMMA ID{
   
                    $$=new symbolInfo("declaration_list","declaration_list error");
                    $$->insertToChildList($1);
                    $$->insertToChildList($3);
                    $$->insertToChildList($4);

                    $$->startLine=$1->startLine;
                    $$->endLine=$4->endLine;

                    yyerror("declaration_list of variable declaration");
                    errorCount++;
                    string new_list = $1->getSymbolName()+ "," + $4->getSymbolName();
                    $1->insertToList1($4->getSymbolName()); //append new id to parent list
                    $1->insertToList2("");
                    $1->setSymbolName(new_list);
                    

                }
                | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD{
                    $$=new symbolInfo("declaration_list","declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);
                    $$->insertToChildList($3);
                    $$->insertToChildList($4);
                    $$->insertToChildList($5);
                    $$->insertToChildList($6);

                    $$->startLine=$1->startLine;
                    $$->endLine=$6->endLine;

                    string new_list = $1->getSymbolName() + "," + $3->getSymbolName() + "[" + $5->getSymbolName() + "]";
                    $1->insertToList1($3->getSymbolName()); //append new id to parent list
                    $1->insertToList2("[]"); //mark as array
                    $1->setSymbolName(new_list);
                    rulePrint("declaration_list", "declaration_list COMMA ID LSQUARE CONST_INT RSQUARE");
                    table.insert($3);
                    
                }
                | declaration_list error COMMA ID LTHIRD CONST_INT RTHIRD{
                    /*
                        Error recovery of declaration_list like:
                        int a+b, c[10];
                    // */
                    $$=new symbolInfo("declaration_list","declaration_list error");
                    $$->insertToChildList($1);
                    $$->insertToChildList($3);
                    $$->insertToChildList($4);
                    $$->insertToChildList($5);
                    $$->insertToChildList($6);
                    $$->insertToChildList($7);

                    $$->startLine=$1->startLine;
                    $$->endLine=$7->endLine;

                    yyerror("declaration_list of declaration_list");
                    errorCount++;
                    string new_list = $1->getSymbolName() + "," + $4->getSymbolName() + "[" + $6->getSymbolName() + "]";
                    $1->insertToList1($4->getSymbolName()); //append new id to parent list
                    $1->insertToList2("[]"); //mark as array
                    $1->setSymbolName(new_list);
                                  
                }
 		        | ID{
                    
                    symbolInfo *newSymbol = new symbolInfo("declaration_list", "ID");
                    $$ = newSymbol;
                    $$->insertToChildList($1);

                    $$->startLine=$1->startLine;
                    $$->endLine=$1->endLine;

                    string new_id = $1->getSymbolName();
                    //$$->insertToList1(new_id); //started a new declaration_list
                    //$$->insertToList2("");
                    rulePrint("declaration_list", "ID");
                    if(!table.lookup($1->getSymbolName())){
                        table.insert($1);
                    }
                }
 		        | ID LTHIRD CONST_INT RTHIRD{
                   
                    symbolInfo *newSymbol = new symbolInfo("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
                    $$ = newSymbol;
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);
                    $$->insertToChildList($3);
                    $$->insertToChildList($4);

                    $$->startLine=$1->startLine;
                    $$->endLine=$4->endLine;

                    $$->insertToList1($1->getSymbolName()); //started a new declaration_list
                    $$->insertToList2("[]");
                    rulePrint("declaration_list", "ID LSQUARE CONST_INT RSQUARE");
                    
                }
                | declaration_list COMMA ID LTHIRD CONST_FLOAT RTHIRD{
        
                    $$ = new symbolInfo("declaration_list","declaration_list COMMA ID LTHIRD CONST_FLOAT RTHIRD");
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);
                    $$->insertToChildList($3);
                    $$->insertToChildList($4);
                    $$->insertToChildList($5);
                    $$->insertToChildList($6);

                    $$->startLine=$1->startLine;
                    $$->endLine=$6->endLine;
                    
                    string new_list = $1->getSymbolName() + "," + $3->getSymbolName() + "[" + $5->getSymbolName() + "]";
                    $1->insertToList1($3->getSymbolName()); //append new id to parent list
                    $1->insertToList2("[]"); //mark as array
                    $1->setSymbolName(new_list);
                    yyerror("Non-Integer Array Size");
                    errorCount++;      
                }
                | ID LTHIRD CONST_FLOAT RTHIRD{
                    
                    symbolInfo *newSymbol = new symbolInfo("declaration_list", "ID LTHIRD CONST_FLOAT RTHIRD");
                    $$ = newSymbol;
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);
                    $$->insertToChildList($3);
                    $$->insertToChildList($4);

                    $$->startLine=$1->startLine;
                    $$->endLine=$4->endLine;

                    $$->insertToList1($1->getSymbolName()); //started a new declaration_list
                    $$->insertToList2("[]");
                    yyerror("Non-Integer Array Size");
                    errorCount++;
 

                }
                | ID LTHIRD RTHIRD{
                    
                    symbolInfo *newSymbol = new symbolInfo("declaration_list", "ID LSQUARE RSQUARE");
                    $$ = newSymbol;
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);
                    $$->insertToChildList($3);

                    $$->startLine=$1->startLine;
                    $$->endLine=$3->endLine;


                    $$->insertToList1($1->getSymbolName()); //started a new declaration_list
                    $$->insertToList2("[]");
                    rulePrint("declaration_list", "ID LSQUARE RSQUARE");
                    yyerror("Undefined Array Size");
                    errorCount++;
                    
                }
 		        ;
statements : statement {
                   
                    $$ = new symbolInfo("statements", "statement");
                    $$->insertToChildList($1);

                    $$->startLine=$1->startLine;
                    $$->endLine=$1->endLine;

                    rulePrint("statements","statement");
                
           }
    	   | statements statement {
                    
                    $$ = new symbolInfo("statements", "statements statement");
                  
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);

                    $$->startLine=$1->startLine;
                    $$->endLine=$2->endLine;

                    rulePrint("statements","statements statement");
                    

           }
           | statements error statement  {

                    $$ = new symbolInfo("statements", "statements error");
                    $$->insertToChildList($1);
                    $$->insertToChildList($3);

                    $$->startLine=$1->startLine;
                    $$->endLine=$3->endLine;
                    
           }
	       ;
	   
statement : var_declaration{
               
                $$ = new symbolInfo("statement", "var_declaration");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;
                
                rulePrint("statement", "var_declaration");

        }
        | expression_statement{
               
                $$ = new symbolInfo("statement", "expression_statement");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;
                
                rulePrint("statement", "expression_statement");
        }
        | compound_statement{
              
                $$ = new symbolInfo("statement", "compound_statement");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;
                
                rulePrint("statement", "compound_statement");

        }
        | FOR LPAREN expression_statement expression_statement expression RPAREN statement{
               
                $$ = new symbolInfo("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);
                $$->insertToChildList($4);
                $$->insertToChildList($5);
                $$->insertToChildList($6);
                $$->insertToChildList($7);

                $$->startLine=$1->startLine;
                $$->endLine=$7->endLine;

                rulePrint("statement", "FOR LPAREN expression_statement expression_statement expression RPAREN statement");
                

        }
        | IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE{
              
                $$ = new symbolInfo("statement", "IF LPAREN expression RPAREN statement");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);
                $$->insertToChildList($4);
                $$->insertToChildList($5);

                $$->startLine=$1->startLine;
                $$->endLine=$5->endLine;

                rulePrint("statement", "IF LPAREN expression RPAREN statement");
                
        }
        | IF LPAREN expression RPAREN statement ELSE statement{
  
                $$ = new symbolInfo("statement", "IF LPAREN expression RPAREN statement ELSE statement");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);
                $$->insertToChildList($4);
                $$->insertToChildList($5);
                $$->insertToChildList($6);
                $$->insertToChildList($7);

                $$->startLine=$1->startLine;
                $$->endLine=$7->endLine;

                rulePrint("statement", "IF LPAREN expression RPAREN statement ELSE statement");
                
        }
        | WHILE LPAREN expression RPAREN statement{
                //string _stmt = "while(" + $3->getSymbolName() + ") " + $5->getSymbolName();
                $$ = new symbolInfo("statement", "WHILE LPAREN expression RPAREN statement");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);
                $$->insertToChildList($4);
                $$->insertToChildList($5);

                $$->startLine=$1->startLine;
                $$->endLine=$5->endLine;

                rulePrint("statement", "WHILE LPAREN expression RPAREN statement");
                

        }
        | PRINTLN LPAREN ID RPAREN SEMICOLON{

               $$ = new symbolInfo("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);
                $$->insertToChildList($4);
                $$->insertToChildList($5);

                $$->startLine=$1->startLine;
                $$->endLine=$5->endLine;

                symbolInfo *retSymbol = table.lookup($3->getSymbolName());
                if(retSymbol==nullptr){
                    yyerror("Undeclared Variable: " + $3->getSymbolName());
                    errorCount++;
                }
                rulePrint("statement", "PRINTLN LPAREN ID RPAREN SEMICOLON");
            
        }
        | RETURN expression SEMICOLON{
                
                $$ = new symbolInfo("statement", "RETURN expression SEMICOLON");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);

                $$->startLine=$1->startLine;
                $$->endLine=$3->endLine;
                
                rulePrint("statement", "RETURN expression SEMICOLON");
  
        }
        ;
expression_statement : SEMICOLON{
                            $$ = new symbolInfo("expression_statement", "SEMICOLON"); 
                            $$->insertToChildList($1);

                            $$->startLine=$1->startLine;
                            $$->endLine=$1->endLine;
                            
                            rulePrint("expression_statement", "SEMICOLON");

                    }
			        | expression SEMICOLON {
                            
                            $$ = new symbolInfo("expression_statement", "expression SEMICOLON");
                            $$->insertToChildList($1);
                            $$->insertToChildList($2);

                            $$->startLine=$1->startLine;
                            $$->endLine=$2->endLine;

                            rulePrint("expression_statement", "expression SEMICOLON");
                            
                    }
                    
			        ;
variable : ID {
                $$=new symbolInfo("variable","ID");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;
                
                string _name = $1->getSymbolName();
                
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

        }		
	    | ID LTHIRD expression RTHIRD {
                $$=new symbolInfo("variable","ID LTHIRD expression RTHIRD");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);
                $$->insertToChildList($4);

                $$->startLine=$1->startLine;
                $$->endLine=$4->endLine;

                //fix here    

        }
        | ID LTHIRD RTHIRD {
                $$=new symbolInfo("variable"," ID LTHIRD RTHIRD");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);

                $$->startLine=$1->startLine;
                $$->endLine=$3->endLine;

                string _name = $1->getSymbolName() + "[]";
                symbolInfo *existingVar = table.lookup($1->getSymbolName()); //find if variable is declared
                string existingVarType = existingVar->getTypeVar();
                //string indexType = $3->getTypeVar();
                
                
                if(existingVar!=nullptr){
                    if(existingVarType=="int[]"){
                        $$->setTypeVar("int");
                    }
                    else if(existingVarType=="float[]"){
                        $$->setTypeVar("float");
                    }
                    else if(existingVarType=="char[]"){
                        $$->setTypeVar("char");
                    }
                    else{
                        string eMsg = "Type mismatch. Variable '" + $1->getSymbolName() + "' is not an array";
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
                
        }
	    ;  
expression : logic_expression {
                    $$ = new symbolInfo("expression","logic_expression");
                    $$->insertToChildList($1);

                    $$->startLine=$1->startLine;
                    $$->endLine=$1->endLine;
                    
                    rulePrint("expression","logic_expression");

            }
	        | variable ASSIGNOP logic_expression {
                            
                    $$ = new symbolInfo("expression","variable ASSIGNOP logic_expression" );
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);
                    $$->insertToChildList($3);

                    $$->startLine=$1->startLine;
                    $$->endLine=$3->endLine;
                   
                    string _exp = $1->getSymbolName() + "=" +$3->getSymbolName();
                    if($1->getsymbolType()=="func_declaration"||$1->getsymbolType()=="func_definition"||$3->getsymbolType()=="func_declaration"||$3->getsymbolType()=="func_definition"){
                        yyerror("= operator can not have function declaration/definition as operands");
                        $$->setTypeVar("none");
                        errorCount++;
                    }
                    
                    else if(checkAssignOp($1->getTypeVar(), $3->getTypeVar())==false){
                        //cout<<$1->getTypeVar()<<endl;
                        yyerror("Type mismatch");
                        errorCount++;
                        $$->setTypeVar($1->getTypeVar());
                    }
                    else{
                        symbolInfo *syym = table.lookup($1->getSymbolName());
                        if(syym!=nullptr)
                            $$->setTypeVar(syym->getTypeVar());
                    }
                    rulePrint("expression", "variable ASSIGNOP logic_expression");
            
            }
	        ;
			
logic_expression : rel_expression {
                        $$ = new symbolInfo("logic_expression","rel_expression");
                        $$->insertToChildList($1);

                        $$->startLine=$1->startLine;
                        $$->endLine=$1->endLine;
                        
                        rulePrint("logic_expression","rel_expression");

                }
		        | rel_expression LOGICOP rel_expression {
                        $$ = new symbolInfo("logic_expression", "rel_expression LOGICOP rel_expression");
                        $$->insertToChildList($1);
                        $$->insertToChildList($2);
                        $$->insertToChildList($3);

                        $$->startLine=$1->startLine;
                        $$->endLine=$3->endLine;

                        string expType = $1->getTypeVar();
                        string expTypeRight = $3->getTypeVar(); 
                        string _exp = $1->getSymbolName() + $2->getSymbolName() + $3->getSymbolName();
                        //cout<<expType<<endl;
                        //cout<<termType<<endl;
     

                        if(expType=="void" || expTypeRight=="void"){
                            yyerror("Void type operand detected!");
                            errorCount++;
                            $$->setTypeVar("void");
                        }
                        else{
                            $$->setTypeVar("int");
                        }

                        
                        rulePrint("logic_expression", "rel_expression LOGICOP rel_expression");
                       

                }
		        ;
rel_expression	: simple_expression {
                        $$ = new symbolInfo("rel_expression", "simple_expression");
                        $$->insertToChildList($1);

                        $$->startLine=$1->startLine;
                        $$->endLine=$1->endLine;
                        
                        rulePrint("rel_expression", "simple_expression");

                }
                | simple_expression RELOP simple_expression	{
                        $$ = new symbolInfo("rel_expression", "simple_expression RELOP simple_expression");
                        $$->insertToChildList($1);
                        $$->insertToChildList($2);
                        $$->insertToChildList($3);

                        $$->startLine=$1->startLine;
                        $$->endLine=$3->endLine;
                       
                        string expType = $1->getTypeVar();
                        string expTypeRight = $3->getTypeVar(); 
                        string _exp = $1->getSymbolName() + $2->getSymbolName() + $3->getSymbolName();
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
                            $$->setTypeVar("int");
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
                            $$->setTypeVar("int");
                        }
   
                        rulePrint("rel_expression", "simple_expression RELOP simple_expression");

                    
                }
                ;
simple_expression : term {
                            $$ = new symbolInfo("simple_expression", "term");
                            $$->insertToChildList($1);

                            $$->startLine=$1->startLine;
                            $$->endLine=$1->endLine;
                            
                            rulePrint("simple_expression", "term");
                            
                    }
		            | simple_expression ADDOP term {
                            
                            $$=new symbolInfo("simple_expression","simple_expression ADDOP term");
                            $$->insertToChildList($1);
                            $$->insertToChildList($2);
                            $$->insertToChildList($3);

                            $$->startLine=$1->startLine;
                            $$->endLine=$3->endLine;

                            string expType = $1->getTypeVar();
                            string termType = $3->getTypeVar();
                            string _exp = $1->getSymbolName() + $2->getSymbolName() + $3->getSymbolName();
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
                                $$->setTypeVar(expType);
                            }
                            else if(expType=="int" && arrayTerm){
                                $$->setTypeVar(termType);
                            }
                            else if(arrayExp || arrayTerm){
                                yyerror("Incompatible Operands");
                                errorCount++;
                            }
                            else if(expType=="float" || termType=="float"){
                                $$->setTypeVar("float");
                            }
                            else{
                                $$->setTypeVar("int");
                            }
                            

                            
                            rulePrint("simple_expression", "simple_expression ADDOP term");
                           
                    }
		            ;
term :	unary_expression{
                $$ = new symbolInfo("term", "unary_expression");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;

                $$->setTypeVar($1->getTypeVar());
                
                rulePrint("term", "unary_expression");
     }
     |  term MULOP unary_expression{
                
                $$ = new symbolInfo("term", "term MULOP unary_expression");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);

                $$->startLine=$1->startLine;
                $$->endLine=$3->endLine;

                
                string expType = $3->getTypeVar(); //unary_expression type
                string termType = $1->getTypeVar();
                string _term = $1->getSymbolName() + $2->getSymbolName() + $3->getSymbolName();
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
                else if((termType!="int" || expType!="int") && $2->getSymbolName()=="%"){
                    yyerror("Modulus operator cannot have non-integer operands");
                    $$->setTypeVar("int");
                    errorCount++;
                }
                else if(($2->getSymbolName()=="%") && $3->getSymbolName()=="0"){
                    yyerror("Modulus by Zero");
                    errorCount++;
                    $$->setTypeVar("int");
                }
                else if(termType=="float" || expType=="float"){
                    $$->setTypeVar("float");
                }
                else{
                    $$->setTypeVar("int");
                }

                rulePrint("term", "term MULOP unary_expression");

     }
     ;
unary_expression : ADDOP unary_expression  {


                    $$ = new symbolInfo("unary_expression", "ADDOP unary_expression");  
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);

                    $$->startLine=$1->startLine;
                    $$->endLine=$2->endLine;

                    string _exp = $1->getSymbolName() + $2->getSymbolName();
                    string _expType = $2->getTypeVar();
                    if(_expType=="void"){
                        yyerror("Void type operand detected!");
                        errorCount++;
                    }

                    $$->setTypeVar(_expType);
                    rulePrint("unary_expression", "ADDOP unary_expression");
                    

                }
		        | NOT unary_expression {
   
                    $$ = new symbolInfo("unary_expression", "NOT unary_expression");
                    $$->insertToChildList($1);
                    $$->insertToChildList($2);

                    $$->startLine=$1->startLine;
                    $$->endLine=$2->endLine;

                    string _exp = "!" + $2->getSymbolName();
                    string _expType = $2->getTypeVar();
                    if(_expType=="void"){
                        yyerror("Void type operand detected!");
                        errorCount++;
                    }
                    $$->setTypeVar(_expType);

                    rulePrint("unary_expression", "NOT unary_expression");
                    
                }
		        | factor {
                        $$ = new symbolInfo("unary_expression", "factor");
                        $$->insertToChildList($1);

                        $$->startLine=$1->startLine;
                        $$->endLine=$1->endLine;
                        
                        $$->setTypeVar($1->getTypeVar());
                        rulePrint("unary_expression", "factor");
                        
                }
        		;
factor	: variable {
                $$ = new symbolInfo("factor", "variable");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;
                
                rulePrint("factor", "variable");   

        }
        | ID LPAREN argument_list RPAREN{

                $$ = new symbolInfo("factor", "ID LPAREN argument_list RPAREN");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);
                $$->insertToChildList($4);

                $$->startLine=$1->startLine;
                $$->endLine=$4->endLine;

                string _id = $1->getSymbolName();
                
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
                    $$->setTypeVar(declaredFunc->getTypeVar());
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
                    vector<string> argTypes = $3->getList1();
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
               

        }
        | LPAREN expression RPAREN{
 
                $$ = new symbolInfo("factor", "LPAREN expression RPAREN");
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$3->endLine;

                string expType = $2->getTypeVar();
                $$->setTypeVar(expType);
                rulePrint("factor", "LPAREN expression RPAREN");
                

        }
        | CONST_INT {
              
                $$ = new symbolInfo("CONST_INT",$1->getSymbolName());
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;

                $$->setTypeVar("int");
                rulePrint("factor", "CONST_INT");
               

        }
        | CONST_FLOAT {
               
                $$ = new symbolInfo("CONST_FLOAT",$1->getSymbolName());
                $$->insertToChildList($1);

                $$->startLine=$1->startLine;
                $$->endLine=$1->endLine;

                $$->setTypeVar("float");
                rulePrint("factor", "CONST_FLOAT");
            

        }
        | variable INCOP {

                $$ = new symbolInfo("factor", "variable INCOP");
                $$->insertToChildList($1);
                $$->insertToChildList($2);

                $$->startLine=$1->startLine;
                $$->endLine=$2->endLine;

                string _factr = $1->getSymbolName() + "++";
                string varType = $1->getTypeVar();
                if(varType == "void"){
                    yyerror("Invalid Operand Type for ++ operator");
                    errorCount++;
                }
                $$->setTypeVar(varType);
                rulePrint("factor", "variable INCOP");
               

        }
        | variable DECOP {
  
                $$ = new symbolInfo("factor", "variable DECOP");
                $$->insertToChildList($1);
                $$->insertToChildList($2);

                $$->startLine=$1->startLine;
                $$->endLine=$2->endLine;

                string _factr = $1->getSymbolName() + "--";
                string varType = $1->getTypeVar();
                if(varType == "void"){
                    yyerror("Invalid Operand Type for -- operator");
                    errorCount++;
                }
                $$->setTypeVar(varType);
                rulePrint("factor", "variable DECOP");
                
        }
        ;
argument_list : arguments {
                   
                    $$ = new symbolInfo("argument_list", "arguments");
                    $$->insertToChildList($1);

                    $$->startLine=$1->startLine;
                    $$->endLine=$1->endLine;

                    string _argmnts = $1->getSymbolName();
                    vector<string> argTypeList = $1->getList1();
                    for(int i=0; i<argTypeList.size(); i++){
                        $$->insertToList1(argTypeList[i]);
                    }
                    //$$->insertToList1($3->getTypeVar());
                    rulePrint("argument_list", "arguments");
                   
              }
			  | {
                    $$ = new symbolInfo("argument_list", "");
                    rulePrint("argument_list", "");

              }
			  ;
arguments : arguments COMMA logic_expression {
                $$ = new symbolInfo("arguments", "arguments COMMA logic_expression");
                $$->insertToChildList($1);
                $$->insertToChildList($2);
                $$->insertToChildList($3);

                string _argmnts = $1->getSymbolName() + "," + $3->getSymbolName();
                vector<string> argTypeList = $1->getList1();
                for(int i=0; i<argTypeList.size(); i++){
                    $$->insertToList1(argTypeList[i]);
                }
                $$->insertToList1($3->getTypeVar());
                rulePrint("arguments", "arguments COMMA logic_expression");
                
          }
	      | logic_expression {
                   
                $$ = new symbolInfo("arguments", "logic_expression");
                $$->insertToChildList($1);

                string _argmnts = $1->getSymbolName();
                rulePrint("arguments", "logic_expression");
                
          }
	      ;

%%

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
