#ifndef CODEGEN_H
#define CODEGEN_H
#include "ast.h"
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Gen{
    
private:
    static string filename;
    static int label_num;
    static int temp_num;
    static string newtemp();
    static string newlabel();
    static void write2File(string content);
public:
    static void genBinary(Expression*& E, Expression* E1, Expression* E2, string op);

    static void genRelop(Expression*& E, Expression* E1, Expression* E2, string op);

    static void genParenthesis(Expression*& E, Expression*& E1);

    static void genId(Identifier*& var, Identifier* Id);

    static void genArr(Identifier*& var, Identifier* Id, Expression* E);

    static void genInt10(Expression*& E, Int10* num);
    
    static void genReal10(Expression*& E, Real10* num);

    static void genIfStmt(Statement*& S, Expression* E, Statement* S1, Statement* S2 = NULL);

    static void genRetStmt(Statement*& S, Expression* E);

    static void genWhileStmt(Statement*& S, Expression* E, Statement* S1);

    static string genCode(vector<Statement*>* gloabal_decl_list);


    /*  function: genFunction
        parameters:
            f_type: return value; 
            id: function name;
            param_list: parameter list;
            block: function body;
    */
    static void genFunction(Statement*& F, Identifier* id, Statement* block);

    static void genFunctionInvoke(Expression*& E, Identifier* id, vector<Expression*>* arg_list);

    /* Assign node is root (need to write S->code to file) */
    static void genAssign(Assign*& S, Identifier* id, Expression* E);

};

#endif