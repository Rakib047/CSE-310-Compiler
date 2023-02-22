%{

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

%}

//%define parse.error verbose

%union{
    symbolInfo* treeNode;
}

%token<treeNode> IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE
%token<treeNode> CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP INCOP DECOP RELOP ASSIGNOP LOGICOP NOT LPAREN 
%token<treeNode> RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON ID PRINTLN

%type<treeNode> start program unit var_declaration func_declaration func_definition
type_specifier parameter_list compound_statement scopeController statements declaration_list
statement expression_statement expression variable logic_expression simple_expression term
unary_expression factor argument_list arguments rel_expression if_expr

%nonassoc LOWER_THAN_ELSE 
%nonassoc ELSE

%%
start : {
		fprintf(asmout, ".MODEL SMALL\n");
		fprintf(asmout, "\n.STACK 1000H\n");
		fprintf(asmout, "\n.DATA\n\nFLAG DB 0\nNL DB 13,10,\"$\"\nNUMBER_STRING DB \"00000$\" \n");
		fprintf(tempasmout, "\n.CODE\n");
	} program {
		printUtilFunctions();
		if(isMainDefined) fprintf(tempasmout, "END MAIN\n");
	}
	;

program : program unit 
	{
		$$ = new symbolInfo($1->getSymbolName()+"\n"+$2->getSymbolName(),"program");
	}
	| unit
	{
		$$ = $1;
	}
	;
	
unit : var_declaration
	{
		$$ = $1;
	}
     | func_declaration
	{
		$$ = $1;
		
	}
     | func_definition
	{
		$$ = $1;
	}
     ;
     
func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON
		{
			string returnType = $1->getSymbolName();
			string funcName = $2->getSymbolName();
			symbolInfo* temp = table.lookup(funcName);
			if (temp!=nullptr)
			{

			}
			else {
				splitParameterTypeList($4->getsymbolType(), ',');


				symbolInfo* f= new symbolInfo(funcName, returnType,"FUNCTION");
				for(string parameterType : parameterTypeList)
					f->addParameter(parameterType);
				table.insert(f);
				clearParameterTypeList();
			}
			table.enterScope();table.exitScope(); // dummy scope for declaration
			$$ = new symbolInfo($1->getSymbolName()+" "+$2->getSymbolName()+"("+$4->getSymbolName()+");","func_declaration");
			
		}
		| type_specifier ID LPAREN RPAREN SEMICOLON
		{
			string returnType = $1->getSymbolName();
			string funcName = $2->getSymbolName();
			symbolInfo* temp = table.lookup(funcName);
			if (temp!=nullptr)
			{
			}
			else {
				symbolInfo* f= new symbolInfo(funcName, returnType,"FUNCTION");
				table.insert(f);
			}
			table.enterScope();table.exitScope(); // dummy scope for declaration
			$$ = new symbolInfo($1->getSymbolName()+" "+$2->getSymbolName()+"();","func_declaration");
			
		}
		;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN 
		{
			string returnType = $1->getSymbolName();
			returnTypeToMatch= returnType;
			string funcName = $2->getSymbolName();
			splitParameterTypeList($4->getsymbolType(), ',');
			extractParameterNameList($4->getSymbolName(),',');

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

			
		} compound_statement {
			$$ = new symbolInfo($1->getSymbolName()+" "+$2->getSymbolName()+"("+$4->getSymbolName()+")"+$7->getSymbolName()+"\n","func_definition");

			resetCurrentOffset();
			fprintf(tempasmout, "%s_EXIT:\n", $2->getSymbolName().c_str());
			fprintf(tempasmout, "\tMOV SP, BP ; Restoring SP\n");
			fprintf(tempasmout, "\tPOP BP\n");
			fprintf(tempasmout, "\tRET %d\n", 2*parameterCount);
			fprintf(tempasmout, "%s ENDP\n", $2->getSymbolName().c_str());

		}
		| type_specifier ID LPAREN RPAREN
		{	// set isMainDefined as true when ID.name == "main"
			string returnType = $1->getSymbolName();
			returnTypeToMatch= returnType;
			string funcName = $2->getSymbolName();
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

			
		} compound_statement {
			$$ = new symbolInfo($1->getSymbolName()+" "+$2->getSymbolName()+"()"+$6->getSymbolName()+"\n","func_definition");
			resetCurrentOffset();
			fprintf(tempasmout, "%s_EXIT:\n", $2->getSymbolName().c_str());
			fprintf(tempasmout, "\tMOV SP, BP ; Restoring SP\n");
			fprintf(tempasmout, "\tPOP BP\n");
			if($2->getSymbolName()=="main") {
				fprintf(tempasmout, "\tMOV AH, 4CH\n\tINT 21H\n");
			} else {
				fprintf(tempasmout, "\tRET\n");
			}

			fprintf(tempasmout, "%s ENDP\n", $2->getSymbolName().c_str());
		}
 		;				


parameter_list  : parameter_list COMMA type_specifier ID
		{
			$$ = new symbolInfo($1->getSymbolName() + "," + $3->getSymbolName() + " " + $4->getSymbolName(), $1->getsymbolType() + "," + $3->getsymbolType());
		}
		| parameter_list COMMA type_specifier
		{
			$$ = new symbolInfo($1->getSymbolName() + "," + $3->getSymbolName(), $1->getsymbolType() + "," + $3->getsymbolType());
		}
		| type_specifier ID
		{
			$$ = new symbolInfo($1->getSymbolName() + " " + $2->getSymbolName(), $1->getsymbolType());
		}
		| type_specifier
		{
			$$ = $1;
		}
		
		;

 		
compound_statement : LCURL scopeController statements RCURL
			{
				

				$$ = new symbolInfo("{\n"+$3->getSymbolName()+"\n}\n","compound_statement");

				p.clear();
				table.exitScope();
				
			}
 		    | LCURL scopeController RCURL
			{
				$$ = new symbolInfo("{\n}\n","compound_statement");

				table.exitScope();
			};

scopeController :
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
			}
 		    ;
 		    
var_declaration : type_specifier declaration_list SEMICOLON
		{
			string varType = $1->getSymbolName();
			string varList = $2->getSymbolName();
			if ($1->getSymbolName()=="void"){
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



			$$ = new symbolInfo($1->getSymbolName()+" "+$2->getSymbolName()+";", "var_declaration");

		}
 		 ;
 		 
type_specifier	: INT
		{
			$$= new symbolInfo("int","int");
		}
 		| FLOAT
		{
			$$= new symbolInfo("float","float");
		}
 		| VOID
		{
			$$= new symbolInfo("void","void");
		}
 		;
 		
declaration_list : declaration_list COMMA ID
		  {
			$$ = new symbolInfo($1->getSymbolName()+","+$3->getSymbolName(), "declaration_list");
			
		  }
 		  | declaration_list COMMA ID LTHIRD CONST_INT RTHIRD 
		  {
			if($5->getSymbolName()=="0"){
			}
			
			$$ = new symbolInfo($1->getSymbolName()+","+$3->getSymbolName()+"["+$5->getSymbolName()+"]", "declaration_list");
			
		  }
 		  | ID
		  {
			$$ = new symbolInfo($1->getSymbolName(), "declaration_list");
			
		  }
 		  | ID LTHIRD CONST_INT RTHIRD
		  {
			if($3->getSymbolName()=="0"){
			}
			
			$$ = new symbolInfo($1->getSymbolName()+"["+$3->getSymbolName()+"]", "declaration_list");
			
		  }
	
 		  ;
 		  
statements : statement
		{
			$$=$1;
		}
	   | statements statement
	    {
			$$ = new symbolInfo($1->getSymbolName()+"\n"+$2->getSymbolName(), "statements");
			
	    }
	   ;
	   
statement : var_declaration
	  {
		$$=$1;
		
	  }
	  | expression_statement
	  {	
		
		$$=$1;
	  }
	  | compound_statement
	  {
		$$=$1;
	  }
	  | FOR LPAREN expression_statement {
		forCount++;
		forCountStack.push(forCount);
		fprintf(tempasmout, "%s: ; for loop starting label\n", ("label_for_start_"+to_string(forCountStack.top())).c_str());
	  } expression_statement {
		
	  	fprintf(tempasmout, "CMP AX, 0\n");
	  	fprintf(tempasmout, "JE %s ; loop ending condn\n", ("label_for_end_"+to_string(forCountStack.top())).c_str());
	  	fprintf(tempasmout, "JMP %s ; loop code label\n", ("label_for_stmt_"+to_string(forCountStack.top())).c_str());
	  	fprintf(tempasmout, "%s: ; loop iterator inc/dec\n", ("label_for_ite_"+to_string(forCountStack.top())).c_str());
	  	
	  } expression RPAREN {
		fprintf(tempasmout, "JMP %s ; restart loop\n", ("label_for_start_"+to_string(forCountStack.top())).c_str());
		fprintf(tempasmout, "%s: ; loop code\n", ("label_for_stmt_"+to_string(forCountStack.top())).c_str());
	  } statement
	  {
		$$ = new symbolInfo("for("+$3->getSymbolName()+$5->getSymbolName()+$7->getSymbolName()+")"+$10->getSymbolName(), "statement");
		//Offline 4 code
		fprintf(tempasmout, "JMP %s ; update iterator after stmt\n", ("label_for_ite_"+to_string(forCountStack.top())).c_str());
	  	fprintf(tempasmout, "%s: ; end of for loop\n", ("label_for_end_"+to_string(forCountStack.top())).c_str());
	  	forCountStack.pop();
	  }
	  | if_expr statement %prec LOWER_THAN_ELSE
	  {
		$$ = new symbolInfo($1->getSymbolName()+$2->getSymbolName(), "statement");
		fprintf(tempasmout, "%s: ; end if label\n", ("label_else_"+to_string(ifCountStack.top())).c_str());
		ifCountStack.pop();
	  }
	  | if_expr statement ELSE {
		// labelEndIf= "label_endif_"+to_string(ifCount);
		fprintf(tempasmout, "JMP %s\n", ("label_endif_"+to_string(ifCountStack.top())).c_str());
		fprintf(tempasmout, "%s: ; else label\n", ("label_else_"+to_string(ifCountStack.top())).c_str());
	  } statement{
		$$ = new symbolInfo($1->getSymbolName()+$2->getSymbolName()+"else\n"+$5->getSymbolName(), "statement");
		fprintf(tempasmout, "%s: ; end if label\n", ("label_endif_"+to_string(ifCountStack.top())).c_str());
		ifCountStack.pop();
	  }
	  | WHILE 
	  {
		whileCount++;
		whileCountStack.push(whileCount);
		// labelLoopStart= "label_while_start_"+to_string(whileCount);
		fprintf(tempasmout, "%s: ; while loop begin\n", ("label_while_start_"+to_string(whileCountStack.top())).c_str());
	  } LPAREN expression RPAREN 
	  {
		// labelLoopEnd= "label_while_end_"+to_string(whileCount);
		fprintf(tempasmout, "POP CX\nCMP CX, 0\nJE %s\n", ("label_while_end_"+to_string(whileCountStack.top())).c_str());
	  } statement
	  {
		$$ = new symbolInfo("while("+$4->getSymbolName()+")"+$7->getSymbolName(), "statement");
		//fprintf(logout, "Line %d: statement : WHILE LPAREN expression RPAREN statement\n\n%s\n\n", lineCount, $$->getSymbolName().c_str());
		//Offline 4 code
		fprintf(tempasmout, "JMP %s ; back to top of loop\n%s:\n", ("label_while_start_"+to_string(whileCountStack.top())).c_str(), ("label_while_end_"+to_string(whileCountStack.top())).c_str());
		whileCountStack.pop();
	  }
	  | PRINTLN LPAREN ID RPAREN SEMICOLON
	  { // move to AX from stack 
		symbolInfo *temp = table.lookup($3->getSymbolName());
		// handle undeclared variable error
		if(temp==nullptr){
		}
		else $$ = new symbolInfo("println("+$3->getSymbolName()+");", "statement");
		
		if(temp->isGlobal()) 
		fprintf(tempasmout, "MOV AX, %s\nCALL PRINT\n ; argument %s in AX\n", temp->getSymbolName().c_str(), temp->getSymbolName().c_str());
		else{
				fprintf(tempasmout, "MOV AX, %d[BP]\nCALL PRINT\n ; argument %s in AX\n", temp->getStackOffset(), temp->getSymbolName().c_str());
		}
	  }
	  | RETURN expression SEMICOLON
	  { // jump to label of current function
	  	//! return value should be in AX
		// check return type in func_defn and decl
		if($2->getsymbolType()=="expression") {
		}

		else if(returnTypeToMatch=="void");

		else if($2->getsymbolType()!=returnTypeToMatch){
		}
		
		$$ = new symbolInfo("return "+$2->getSymbolName()+";", "statement");
		fprintf(tempasmout, "POP AX\n");
		fprintf(tempasmout, "\tJMP %s_EXIT\n", currentFunc.c_str());	
	  }
	  ;

if_expr :	IF LPAREN expression RPAREN 
	{
		ifCount++;
		ifCountStack.push(ifCount);
		// labelElse= "label_else_"+to_string(ifCount);
		fprintf(tempasmout, "POP AX ; expr in AX\nCMP AX, 0 ; checking expr\n");
		fprintf(tempasmout, "JE %s\n", ("label_else_"+to_string(ifCountStack.top())).c_str());
		$$= new symbolInfo("if("+$3->getSymbolName()+")", "statement");
	} 	

expression_statement 	: SEMICOLON
			{
				$$ = new symbolInfo(";", "expression_statement");
			}			
			| expression SEMICOLON 
			{
				$$ = new symbolInfo($1->getSymbolName()+";", "expression_statement");
				fprintf(tempasmout, "POP AX\n");
			}
			;
	  
variable : ID 		
	 {
		symbolInfo *temp = table.lookup($1->getSymbolName());
		if(temp->isGlobal()){
			for(auto s:p){
				if(s->getSymbolName()==$1->getSymbolName()){
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
			$$ = new symbolInfo(temp->getSymbolName(), temp->getsymbolType());
			$$->setStackOffset(temp->getStackOffset());
		}
		
	 }
	 | ID LTHIRD expression RTHIRD 
	 {
		symbolInfo *temp = table.lookup($1->getSymbolName());
		if(temp==nullptr){
		}
		else {
			string varType = temp->getsymbolType();
			if ((varType.find("[") != string::npos) || (varType.find("]") != string::npos)) { // is an array
				// handle [float] error
				if ($3->getsymbolType()!="int"){
				}
				if(temp->isGlobal()) {
					fprintf(tempasmout, "POP BX ; popped index expr\nSHL BX, 1\nMOV SI, %s\nMOV AX, BX[SI]\n ; %s called\n", temp->getSymbolName().c_str(), temp->getSymbolName().c_str()); 
				} else {
					fprintf(tempasmout, "POP BX ; popped index expr %s\nSHL BX, 1\nADD BX, %d\n;ADD BX, BP\nPUSH BP\nADD BP, BX\nMOV AX, [BP]\nPOP BP\n;MOV AX, [BX]\nPUSH AX ; value of %s[%s]\nPUSH BX ; index %s\n",
						$3->getSymbolName().c_str(), temp->getStackOffset(), temp->getSymbolName().c_str(), $3->getSymbolName().c_str(), $3->getSymbolName().c_str());
				}
				$$ = new symbolInfo($1->getSymbolName()+"["+$3->getSymbolName()+"]", getArrayName(varType));
				$$->setStackOffset(temp->getStackOffset());
			} 
			else { 
			}
		}
	 }
	 | ID LTHIRD RTHIRD 
	 {
		symbolInfo *temp = table.lookup($1->getSymbolName());
		if(temp==nullptr){
		}
		else {
			string varType = temp->getsymbolType();
			if ((varType.find("[") != string::npos) || (varType.find("]") != string::npos)) { // is an array
				// handle [] error
				errorCount++;
				$$ = new symbolInfo($1->getSymbolName()+"[]", getArrayName(varType));
			} 
			else { 
			}
		}
		
	 }
	 ;
	 
expression : logic_expression
		{
			$$=$1;
		}
	   | variable ASSIGNOP logic_expression
	   	{
			// bunch of type mismatch handling (but int in float is allowed)
			if ($1->getsymbolType()=="void" || $3->getsymbolType()=="void"){
			}
			else if ($1->getsymbolType()!=$3->getsymbolType()){
				string varType= $1->getsymbolType();
				string exprType= $3->getsymbolType();
				if ((varType.find("[") != string::npos) || (exprType.find("[") != string::npos)) { // either an array
				}
				else if (varType=="float" && exprType=="int") ;
				else if (varType=="variable" || exprType=="factor") ;
				else {
				}
			}
			string varName= $1->getSymbolName();

			fprintf(tempasmout, "POP AX ; r-val of assignop %s\n", $3->getSymbolName().c_str());
			
			symbolInfo* temp = table.lookup(getArrayName(varName));
			if(temp->isGlobal()){
				fprintf(tempasmout, "MOV %s, AX\n", temp->getSymbolName().c_str());
			} else {
				if (varName.find("[") != string::npos){
					fprintf(tempasmout, "POP BX\n");
					fprintf(tempasmout, ";MOV [BX], AX\nPUSH BP\nADD BP, BX\nMOV [BP], AX\nPOP BP ; assigning to %s\n", $1->getSymbolName().c_str());
				}
				else {
					fprintf(tempasmout, "MOV %d[BP], AX ; assigning %s to %s\n", $1->getStackOffset(), $3->getSymbolName().c_str(), $1->getSymbolName().c_str());
				}
			}
			$$ = new symbolInfo($1->getSymbolName()+"="+$3->getSymbolName(), "expression");
			
	   	}
	   ;
			
logic_expression : rel_expression
		{
			$$=$1;
		}
		 | rel_expression LOGICOP rel_expression
		{
			if ($1->getsymbolType()=="void" || $3->getsymbolType()=="void"){
			}
			$$ = new symbolInfo("", "int");
			$$->setSymbolName($1->getSymbolName()+$2->getSymbolName()+$3->getSymbolName());
			
			// Offline 4 code
			fprintf(tempasmout, "POP BX\nPOP AX ; left side value\n");
			string labelIfTrue=newLabel();
			string labelIfFalse=newLabel(); 

			if($2->getSymbolName()=="&&"){
				fprintf(tempasmout, "CMP AX, 0\nJE %s\nCMP BX, 0\nJE %s\nPUSH 1\nJMP %s\n", labelIfFalse.c_str(), labelIfFalse.c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; total false\n%s:\n", labelIfFalse.c_str(), labelIfTrue.c_str());
			
			} else if($2->getSymbolName()=="||"){
				fprintf(tempasmout, "CMP AX, 0\nJNE %s\nCMP BX, 0\nJNE %s\nPUSH 0\nJMP %s\n", labelIfFalse.c_str(), labelIfFalse.c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 1 ; total false\n%s:\n", labelIfFalse.c_str(), labelIfTrue.c_str());
			
			} 

		}
		 ;
			
rel_expression	: simple_expression
		{
			$$=$1;
		}
		| simple_expression RELOP simple_expression
		{
			if ($1->getsymbolType()=="void" || $3->getsymbolType()=="void"){
			}
			$$ = new symbolInfo("", "int");
			$$->setSymbolName($1->getSymbolName()+$2->getSymbolName()+$3->getSymbolName());
			// Offline 4 code
			fprintf(tempasmout, "POP AX\nPOP BX ; left side value\nCMP BX, AX ; evaluating %s\n", $$->getSymbolName().c_str());
			string labelIfTrue=newLabel();
			string labelIfFalse=newLabel(); 
			if($2->getSymbolName()=="<"){
				fprintf(tempasmout, "JNL %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
			
			} else if($2->getSymbolName()=="<="){
				fprintf(tempasmout, "JNLE %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
			
			} else if($2->getSymbolName()==">"){
				fprintf(tempasmout, "JNG %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
		
			} else if($2->getSymbolName()==">="){
				fprintf(tempasmout, "JNGE %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
			
			} else if($2->getSymbolName()=="=="){
				fprintf(tempasmout, "JNE %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
			
			} else if($2->getSymbolName()=="!="){
				fprintf(tempasmout, "JE %s\nPUSH 1 ; if %s is true\nJMP %s\n", labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
				fprintf(tempasmout, "%s:\nPUSH 0 ; if %s is false\n%s:\n",labelIfFalse.c_str(), $$->getSymbolName().c_str(), labelIfTrue.c_str());
							
			}

		}
		;
				
simple_expression : term 
		{
			$$=$1;
		}
		  | simple_expression ADDOP term 
		{	// add and keep in AX
			// handle int addition and float addition
			string exprType;
			if(($1->getsymbolType()=="int") && ($3->getsymbolType()=="int")) exprType= "int"; 
			else exprType= "float";
			if ($1->getsymbolType()=="void" || $3->getsymbolType()=="void"){
				exprType= "void";
			}
			if($2->getSymbolName()=="+")
				fprintf(tempasmout, "POP AX\nPOP BX\nADD AX, BX\nPUSH AX ; %s+%s pushed\n", $1->getSymbolName().c_str(), $3->getSymbolName().c_str());
			else 
				fprintf(tempasmout, "POP AX\nPOP BX\nSUB BX, AX\nPUSH BX ; %s-%s pushed\n", $1->getSymbolName().c_str(), $3->getSymbolName().c_str()); //! check minus
			$$ = new symbolInfo("", exprType);
			$$->setSymbolName($1->getSymbolName()+$2->getSymbolName()+$3->getSymbolName());
			//fprintf(logout, "Line %d: simple_expression : simple_expression ADDOP term\n\n%s\n\n", lineCount, $$->getSymbolName().c_str());
		} 
		  ;
					
term :	unary_expression
	 {
		$$=$1;
	 }
     |  term MULOP unary_expression
	 {
		//handle errors
		if ($1->getsymbolType()=="void" || $3->getsymbolType()=="void"){
			$$ = new symbolInfo($1->getSymbolName()+$2->getSymbolName()+$3->getSymbolName(),"void");
		}
		else if($2->getSymbolName()=="%"){ // modulus cases
			if(($1->getsymbolType()=="int") && ($3->getsymbolType()=="int")){
				if($3->getSymbolName()=="0"){
				}
			}
			else { // non int operand
			}
			
			$$ = new symbolInfo($1->getSymbolName()+$2->getSymbolName()+$3->getSymbolName(),"int");
			//Offline 4 code
			fprintf(tempasmout, "MOV DX, 0 ; DX:AX = 0000:AX\nPOP BX\nPOP AX\nIDIV BX\nPUSH DX ; remainder of %s is in DX\n", $$->getSymbolName().c_str());

		}
		else {
			if(($1->getsymbolType()=="int")&&($3->getsymbolType()=="int"))
				$$ = new symbolInfo($1->getSymbolName()+$2->getSymbolName()+$3->getSymbolName(),"int");
			else $$ = new symbolInfo($1->getSymbolName()+$2->getSymbolName()+$3->getSymbolName(),"float");
			// Offline 4 code
			if($2->getSymbolName()=="*")
				fprintf(tempasmout, "POP BX\nPOP AX\nIMUL BX\nPUSH AX ; result of %s is in AX, pushed\n", $$->getSymbolName().c_str());
			else 
				fprintf(tempasmout, "POP BX\nPOP AX\nIDIV BX\nPUSH AX ; result of %s is in AX, pushed\n", $$->getSymbolName().c_str());; //! division
		}
		
	 }
     ;

unary_expression : ADDOP unary_expression  
		 {
			if ($2->getsymbolType()=="void"){
				errorCount++;
			}

			//Offline 4
			if($1->getSymbolName()=="-"){
				fprintf(tempasmout, "POP AX\nNEG AX ; -%s\nPUSH AX\n", $2->getSymbolName().c_str());
			}

			$$ = new symbolInfo($1->getSymbolName()+$2->getSymbolName(), $2->getsymbolType());
		 }
		 | NOT unary_expression 
		 {
			if ($2->getsymbolType()=="void"){
			}
			$$ = new symbolInfo("!"+$2->getSymbolName(), $2->getsymbolType());
			//fprintf(logout, "Line %d: unary_expression : NOT unary_expression\n\n%s\n\n", lineCount, $$->getSymbolName().c_str());
		 	string labelIfTrue=newLabel();
			string labelIfFalse=newLabel();
			fprintf(tempasmout, "POP AX\nCMP AX, 0 ; !%s\nJNE %s\nMOV AX, 1\nJMP %s\n\
				\n%s:\nXOR AX, AX\n%s:\nPUSH AX\n"
				, $2->getSymbolName().c_str(), labelIfTrue.c_str(), labelIfFalse.c_str(), labelIfTrue.c_str(), labelIfFalse.c_str());
		 }
		 | factor 
		 {
			$$=$1;
		 }
		 ;
	
factor	: variable 
	{
		$$=$1;
		if ($$->getSymbolName().find("[") != string::npos)
			fprintf(tempasmout, "POP BX ; r-value, no need for index\n");
	}
	| ID LPAREN argument_list RPAREN
	{
		string returnType= "factor";
		string funcName = $1->getSymbolName();
		symbolInfo* temp = table.lookup(funcName);
		if (temp==nullptr)
		{
		}
		else {
			if(temp->getFuncName()=="FUNCTION"){
				symbolInfo* ftemp= temp;
				returnType= ftemp->getReturnType();
				splitParameterTypeList($3->getsymbolType(),',');
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
		$$ = new symbolInfo($1->getSymbolName()+"("+$3->getSymbolName()+")", returnType);
		fprintf(tempasmout, "CALL %s\n", $1->getSymbolName().c_str());
		if(returnType!="void"){
			fprintf(tempasmout, "PUSH AX ; return value of %s\n", $1->getSymbolName().c_str());
		}
	}
	| LPAREN expression RPAREN
	{
		$$ = new symbolInfo("("+$2->getSymbolName()+")", $2->getsymbolType());

	}
	| CONST_INT 
	{
		$$ = $1;
		fprintf(tempasmout, "PUSH %s\n", $$->getSymbolName().c_str());
	}
	| CONST_FLOAT
	{
		$$ = $1;
	}
	| variable INCOP
	{
		$$ = new symbolInfo($1->getSymbolName()+"++",$1->getsymbolType());
		if ($1->getSymbolName().find("[") != string::npos){
			fprintf(tempasmout, "POP BX\nPOP AX\nINC AX ; %s++\n", $1->getSymbolName().c_str());
			fprintf(tempasmout, "PUSH BP\nADD BP, BX\nMOV [BP], AX\nPOP BP\n");
		}
		else {
			fprintf(tempasmout, "INC AX\nMOV %d[BP], AX\n", $1->getStackOffset());
		}
		// fprintf(tempasmout, "INC AX\n");
	}
	| variable DECOP
	{
		$$ = new symbolInfo($1->getSymbolName()+"--",$1->getsymbolType());
		if ($1->getSymbolName().find("[") != string::npos){
			fprintf(tempasmout, "POP BX\nPOP AX\nDEC AX ; %s++\n", $1->getSymbolName().c_str());
			fprintf(tempasmout, "PUSH BP\nADD BP, BX\nMOV [BP], AX\nPOP BP\n");
		}
		else {
			fprintf(tempasmout, "DEC AX\nMOV %d[BP], AX\n", $1->getStackOffset());
		}
	}
	;
	
argument_list : arguments
			{
				$$=$1;
			}
			  |
			{
				$$=new symbolInfo("", "void");
				//fprintf(logout, "Line %d: argument_list : \n\n%s\n\n", lineCount, $$->getSymbolName().c_str());
			}
			  ;
	
arguments : arguments COMMA logic_expression
			{
				$$ = new symbolInfo($1->getSymbolName()+","+$3->getSymbolName(),$1->getsymbolType()+","+$3->getsymbolType());

			}
	      | logic_expression
			{
				$$=$1;
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
