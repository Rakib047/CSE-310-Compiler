
#include "bits/stdc++.h"
using namespace std;


class symbolInfo{
    private:
        string symbolName;
        string symbolType;
        string idType;
        symbolInfo* nextSymbolInfo;
        
        

        string typeVar,funcSt; ///*typeVar = kon type er ID, funcSt = function er declaration/definition statement specity korar jonno*/
        vector<string> list1;
        /**
         * 
         * list1 used for:
         * 1. function er khetre parameter er type_specifier rakhar jonno
         * 2. var_declaration list er khetre var_name rakhar jonno
         * 3. argument list rakhar jonno
         *
         */
        vector<string> list2;
        /**
         * 
         * list2 used for:
         * 1. function er khetre parameter er id(name) rakhar jonno
         * 2. var_declaration list er khetre --
         *      a. array hole "[]" eta rakhbe
         *      b. otherwise "" eta(empty string) rakhbe
         */
         string stPointer;
         bool temp;

    public:
        vector<symbolInfo*>childList;
        int startLine,endLine;
        string parseRule;
        string rule;
        bool leaf;
        string funcType1,funcType2;
        string returnType;
        vector<string> parameterTypeList;
        bool defined;
        string funcName;
        int stackOffset;
        bool isGlobalBool=true;


        symbolInfo(){
            setSymbolName("");
            setSymbolType("");
            setnextSymbolInfo(nullptr);
            funcName="";
        }

        symbolInfo(string symbolName,string symbolType){
            this->symbolName=symbolName;
            this->symbolType=symbolType;
            nextSymbolInfo=NULL;
            funcName="";
        }

        symbolInfo(string symbolName,string returnType,string func){
            this->returnType=returnType;
            this->defined=false;
            this->funcName=func;
        }

        bool isGlobal(){
            return this->isGlobalBool;
        }
        void setGlobal(bool global){
            this->isGlobalBool= global;
        }

        int getStackOffset(){
            return this->stackOffset;
        }
        void setStackOffset(int offset){
            this->stackOffset= offset;
        }

        string getFuncName(){
            return funcName;
        }

        void addParameter(string parameterType){
            this->parameterTypeList.push_back(parameterType);
        }

        vector<string> getParameterTypeList(){
            return parameterTypeList;
        }
        string getReturnType(){
            return returnType;
        }
        bool getDefined(){
            return defined;
        }
        void setDefined(bool defined){
            this->defined=defined;
        }



        void setIdType(string name){
            this->idType="hello";
        }
        string getIdType(){
            return idType;
        }
        void setStPointer(string stPointer){
            this->stPointer = stPointer;
        }
        string getStPointer(){
            return stPointer;
        }

        void setTypeVar(string typeVar){
            this->typeVar=typeVar;
        }

        void setFuncSt(string funcSt){
            this->funcSt = funcSt;
        }

        string getTypeVar(){
            return typeVar;
        }

        string getFuncSt(){
            return funcSt;
        }

        void insertToList1(string data){
            list1.push_back(data);
        }

        void insertToList2(string data){
            list2.push_back(data);
        }  

        void insertToChildList(symbolInfo* child){
            childList.push_back(child);
        }

        const vector<symbolInfo*>& getChildList(){
                return childList;
        }

        const vector<string>& getList1(){
                return list1;
        }

        const vector<string>& getList2(){
                return list2;
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
		        hash = ((symbolName[i]) + (hash << 6) + (hash << 16) - hash);
	        }

	        return hash%numBucket;
        }

    symbolInfo* lookUp(string symbolName){
        int bucketNo=SDBMHash(symbolName)%numBucket;
        symbolInfo* symbolInfoPtr=hashTable[bucketNo];

        int i=1;
        while(symbolInfoPtr){
            if(symbolInfoPtr->getSymbolName()==symbolName){
                if(symbolName=="foo")
                cout<<"return address from lookup:"<<symbolInfoPtr<<endl;
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

    bool insert(symbolInfo* symbol){
        string symbolName=symbol->getSymbolName();

         if(symbolName=="foo")
         cout<<"insert address from insert function:"<<symbol<<endl;       
        
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
            hashTable[bucketNo]=new symbolInfo(symbol->getSymbolName(),symbol->getsymbolType());
            //cout<<"Inserted in ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", 1"<<endl;
        }
        else{
            int i=2;
            while(symbolInfoPtr->getnextSymbolInfo()){
                i++;
                symbolInfoPtr=symbolInfoPtr->getnextSymbolInfo();
            }
            symbolInfo* symbolInfoInserted=new symbolInfo(symbol->getSymbolName(),symbol->getsymbolType());
            symbolInfoPtr->setnextSymbolInfo(symbol);
            //symbolInfoInserted->setFuncSt(symbol->getFuncSt());
            //symbolInfoInserted->setTypeVar(symbol->getTypeVar());
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

    void print(FILE* logout){
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
        bool isEmpty;
        
    public:
        int scopeTableCount;
        
        symbolTable(int currentScopeTableSize){
            scopeTableCount=0;
            this->currentScopeTableSize=currentScopeTableSize;
            currentScopeTable=new scopeTable(currentScopeTableSize,nullptr,++scopeTableCount);    
        }

        void enterScope(){
            scopeTable* temp=new scopeTable(currentScopeTableSize,currentScopeTable,++scopeTableCount);
            currentScopeTable=temp;
        }

        void exitScope(){
            // if(currentScopeTable->getScopeTableId()==1 && command!="Q"){
            //     //cout<<"ScopeTable# 1 cannot be removed"<<endl;
            //     return;
            // }
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

        bool insert(symbolInfo* symbol){
            return currentScopeTable->insert(symbol);
        }

        bool insert(string name,string type){
            symbolInfo* temp=new symbolInfo(name,type);
            return currentScopeTable->insert(temp);
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

        void printCurrentScope(FILE* logout){
            currentScopeTable->print(logout);
        }

        void printAllScope(FILE* logout){
            scopeTable* scopeTablePtr=currentScopeTable;
            while(scopeTablePtr){
                scopeTablePtr->print(logout);
                scopeTablePtr=scopeTablePtr->getParentScopeTable();
            }
        }

        bool getIsEmpty(){
            return isEmpty;
        }

        int getCurrentScopeId(){
            return currentScopeTable->getScopeTableId();
        }
};
