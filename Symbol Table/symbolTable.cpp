#include "bits/stdc++.h"
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
            cout<<"ScopeTable# "<<scopeTableId<<" created"<<endl;
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
                cout<<"'"<<symbolName<<"'"<<" found in ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", "<<i<<endl;
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
            cout<<"'"<<symbolName<<"'"<<" already exists in the current ScopeTable"<<endl;
            return false;
        }

        symbolInfoPtr=hashTable[bucketNo];


        if(symbolInfoPtr==nullptr){
            hashTable[bucketNo]=new symbolInfo(symbol.getSymbolName(),symbol.getsymbolType());
            cout<<"Inserted in ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", 1"<<endl;
        }
        else{
            int i=2;
            while(symbolInfoPtr->getnextSymbolInfo()){
                i++;
                symbolInfoPtr=symbolInfoPtr->getnextSymbolInfo();
            }
            symbolInfo* symbolInfoInserted=new symbolInfo(symbol.getSymbolName(),symbol.getsymbolType());
            symbolInfoPtr->setnextSymbolInfo(symbolInfoInserted);
            cout<<"Inserted in ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", "<<i<<endl;

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
                cout<<"Deleted "<<"'"<<symbolName<<"'"<<" from ScopeTable# "<<scopeTableId<<" at position "<<bucketNo+1<<", "<<i<<endl;

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
        cout<<"Not found in the current ScopeTable"<<endl;
        return false;
    }

    void print(){
        cout<<"\t";
        cout<<"ScopeTable# "<<scopeTableId<<endl;

        for(int i=1;i<=numBucket;i++){
            cout<<"\t";
            cout<<i<<"--> ";
            symbolInfo* symbolInfoPtr=hashTable[i-1];
            while(symbolInfoPtr){
                cout<<"<"<<symbolInfoPtr->getSymbolName()<<","<<symbolInfoPtr->getsymbolType()<<"> ";
                symbolInfoPtr=symbolInfoPtr->getnextSymbolInfo();
            }
            cout<<endl;
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
                cout<<"ScopeTable# 1 cannot be removed"<<endl;
                return;
            }
            if(currentScopeTable->getScopeTableId()==1){
                isEmpty=true;
            }
            scopeTable* temp=currentScopeTable;
            currentScopeTable=currentScopeTable->getParentScopeTable();
            cout<<"ScopeTable# "<<temp->getScopeTableId()<<" removed"<<endl;
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
            cout<<"'"<<symbolName<<"'"<<" not found in any of the ScopeTables"<<endl;
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

int main(){
    freopen("sample_input.txt","r",stdin);
    freopen("output.txt","w",stdout);

    int bucketNo;
    cin>>bucketNo;

    string operation;
    cout<<"\t";
    symbolTable symbolTableObj(bucketNo);
    

   
    int commandCount=0;
    while(1){
    
        string lineInput;
        getline(cin,lineInput);
        istringstream token(lineInput);

        string operation[3]={"","",""};
        int i=0;
        while(token>>operation[i]){
            i++;
        }

        if(operation[0]=="I"){
            commandCount++;
            cout<<"Cmd "<<commandCount<<": ";

            string symbolName,symbolType;

            symbolName=operation[1];
            symbolType=operation[2];
            
            if(symbolName==""||symbolType==""){
                cout<<operation[0];
                if(operation[1]!=""){
                    cout<<" "<<operation[1];
                }
                if(operation[2]!=""){
                    cout<<" "<<operation[2];
                }
                cout<<endl;
                cout<<"\t";
                cout<<"Number of parameters mismatch for the command I"<<endl;
                continue;
            }
            
            cout<<"I "<<symbolName<<" "<<symbolType<<endl;
            cout<<"\t";
            symbolTableObj.insert(symbolInfo(symbolName,symbolType));
        }
        else if(operation[0]=="L"){
            commandCount++;
            cout<<"Cmd "<<commandCount<<": ";

            string symbolName;
            string symbolType;

            symbolName=operation[1];
            symbolType=operation[2];
           
            if(symbolName==""||symbolType!=""){
                cout<<operation[0]<<" "<<operation[1]<<" "<<operation[2]<<endl;
                cout<<"\t";
                cout<<"Number of parameters mismatch for the command L"<<endl;
                continue;
            }
        
            cout<<"L "<<symbolName<<endl;
            cout<<"\t";
            symbolTableObj.lookup(symbolName);
        }
        else if(operation[0]=="D"){
            commandCount++;
            cout<<"Cmd "<<commandCount<<": ";

            string symbolName;
            string symbolType;

            symbolName=operation[1];
            symbolType=operation[2];
           
            if(symbolName==""||symbolType!=""){
                cout<<operation[0];
                if(operation[1]!=""){
                    cout<<" "<<operation[1];
                }
                if(operation[2]!=""){
                    cout<<" "<<operation[2];
                }
                cout<<endl;
                cout<<"\t";
                cout<<"Number of parameters mismatch for the  command D"<<endl;
                continue;
            }
            cout<<"D "<<symbolName<<endl;
            cout<<"\t";
            symbolTableObj.remove(symbolName);
        }
        else if(operation[0]=="P"){
            commandCount++;
            cout<<"Cmd "<<commandCount<<": ";

            string command1;
            string command2;
            
            command1=operation[1];
            command2=operation[2];

            if(command2!=""){
                cout<<operation[0]<<" "<<operation[1]<<" "<<operation[2]<<endl;
                cout<<"\t";
                cout<<"Number of parameters mismatch for the command P"<<endl;
                continue;
            }

            cout<<"P "<<command1<<endl;

            if(command1=="A"){
                symbolTableObj.printAllScope();
            }
            else{
                symbolTableObj.printCurrentScope();
            }
        }
        else if(operation[0]=="S"){
            commandCount++;
            cout<<"Cmd "<<commandCount<<": ";

            if(operation[1]!=""||operation[2]!=""){
                cout<<operation[0]<<" "<<operation[1]<<" "<<operation[2]<<endl;
                cout<<"\t";
                cout<<"Number of parameters mismatch for the command S"<<endl;
                continue;
            }
            cout<<"S"<<endl;
            cout<<"\t";
            symbolTableObj.enterScope();
        }
        else if(operation[0]=="E"){
            commandCount++;
            cout<<"Cmd "<<commandCount<<": ";

            if(operation[1]!=""||operation[2]!=""){
                cout<<operation[0]<<" "<<operation[1]<<" "<<operation[2]<<endl;
                cout<<"\t";
                cout<<"Number of parameters mismatch for the command E"<<endl;
                continue;
            }
            cout<<"E"<<endl;
            cout<<"\t";
            symbolTableObj.exitScope("E");
        }
        else if(operation[0]=="Q"){
            commandCount++;
            cout<<"Cmd "<<commandCount<<": ";
            cout<<"Q"<<endl;

            if(operation[1]!=""||operation[2]!=""){
                cout<<operation[0]<<" "<<operation[1]<<" "<<operation[2]<<endl;
                cout<<"\t";
                cout<<"Number of parameters mismatch for the command Q"<<endl;
                continue;
            }
            while(!symbolTableObj.getIsEmpty()){
                cout<<"\t";
                symbolTableObj.exitScope("Q");
            }
    
            exit(-1);
        }
    }
}