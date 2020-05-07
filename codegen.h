#ifndef CODEGEN_H
#define CODEGEN_H
#include "ast.h"
#include <iostream>
#include <fstream>
using namespace std;

class Gen{
    
private:
    static string filename;
    static int label;
    static string newtemp();
    static void write2File(string content);
public:
    static void genBinary(Expression*& E, Expression* E1, Expression* E2, string op);

    static void genRelop(Expression*& E, Expression* E1, Expression* E2, string op);

    static void genParenthesis(Expression*& E, Expression*& E1);

    static void genId(Identifier*& var, Identifier* Id);

    static void genInt10(Expression*& E, Int10* num);

    /* Assign node is root (need to write S->code to file) */
    static void genAssign(Assign*& S, Identifier* id, Expression* E);

};

#endif