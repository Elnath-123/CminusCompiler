#include "symbol.h"
SymbolTable::SymbolTable(){
    
}

int SymbolTable::insertKeywordSymbol(string name, KeyWordSymbol* keyword){
    if(s_keyword.count(name)) return ERR_DUP_KEY;
    this->s_keyword[name] = keyword;
    return VALID_KEY;
}

int SymbolTable::insertIdSymbol(string name, IdSymbol* id){
    if(s_id.count(name)) return ERR_DUP_KEY;
    this->s_id[name] = id;
    return VALID_KEY;
}

int SymbolTable::insertFuncSymbol(string name, FuncSymbol* func){
    if(s_func.count(name)) return ERR_DUP_KEY;
    this->s_func[name] = func;
    return VALID_KEY;
}

int SymbolTable::insertArraySymbol(string name, ArraySymbol* array){
    if(s_arr.count(name)) return ERR_DUP_KEY;
    this->s_arr[name] = array;
    return VALID_KEY;
}