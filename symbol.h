#ifndef SYMBOL_H
#define SYMBOL_H
#include <string>
#include <map>
#include <vector>
#include "ast.h"
#define ERR_DUP_KEY -1
#define VALID_KEY 1
using namespace std;

class Symbol{
public:
    string type;
    string name;
    Symbol(){}
    Symbol(string type, string name):
        type(type), name(name){ }
};

class KeyWordSymbol : Symbol{
public:
    string keyword_type;
    KeyWordSymbol(string keyword_type):
         keyword_type(keyword_type){ }
};

class IdSymbol : Symbol{
public:
    string type_specifier; 
    Int10* num;
    IdSymbol(string type, string name, string type_specifier, Int10* num=NULL):
        Symbol(type, name), type_specifier(type_specifier), num(num){ }
};

class FuncSymbol : Symbol{
public:
    string ret_type;
    vector<Variable*>* param_list;
    FuncSymbol(string type, string name, string ret_type, vector<Variable*>* param_list):
        Symbol(type, name), ret_type(ret_type), param_list(param_list){ }
};

class ArraySymbol : IdSymbol{
public:
    unsigned size;
    ArraySymbol(string type, string name, string type_specifier, unsigned size):
        IdSymbol(type, name, type_specifier), size(size){ }
};

class SymbolTable{
public:
    SymbolTable();
    map<string, KeyWordSymbol*> s_keyword;
    map<string, IdSymbol*> s_id;
    map<string, FuncSymbol*> s_func;
    map<string, ArraySymbol*> s_arr;
    int insertKeywordSymbol(string name, KeyWordSymbol*);
    int insertIdSymbol(string name, IdSymbol*);
    int insertFuncSymbol(string name, FuncSymbol*);
    int insertArraySymbol(string name, ArraySymbol*);
};
#endif