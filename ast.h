/*
* @name ast.h
* @description Hierachy of AST
* @date 03/31/2020
* @author Lrq 
*                        |---------|
*                        | AstNode |
*                        |---------|
*                             |
*                             |
*                      |--------------|
*                      |  Expression  |
*                      |--------------|
*                          |      |
*                         |        |
*                        |          |
*                    |-------|    |-------|
*                    | BinOp |    |  Num  |
*                    |-------|    |-------|
*/
#ifndef _AST_H
#define _AST_H
#include <iostream>
#include <vector>
#include "visitor.h"
using namespace std;
class AstNode{
public:
	AstNode(){ }
	virtual double accept( Visitor* v ) = 0;
};

class Statement : public AstNode{
public:
	string type;
	string next;
	string code;
	Statement(string type):
		type(type) {}
	Statement(string type, string code):
		type(type), code(code) {}
};

class IfStmt : public Statement{
public:
	Statement* s1;
	Statement* s2;
	Expression* e;
	IfStmt(string type, Expression* e, Statement* s1, Statement* s2 = nullptr):
		Statement(type), s1(s1), s2(s2), e(e) {}

	double accept( Visitor* v) {}
};

class WhileStmt : public Statement{
public:
	Statement* s;
	Expression* e;
	WhileStmt(string type, Expression* e, Statement* s):
		Statement(type), s(s), e(e) {}
	
	double accept( Visitor* v) {}
};

class ReturnStmt : public Statement{
	
};

class ExpStmt : public Statement{
public:
	Expression* e;
	ExpStmt(string type, Expression* e):
		Statement(type), e(e) {
			/* Pass code */
			
		}
	double accept( Visitor* v) {}
};

class BlockStmt : public Statement{
public:
	vector<Statement*>* stmt_list;
	vector<Statement*>* local_decl_list;
	BlockStmt(string type, vector<Statement*>* local_decl_list, vector<Statement*>* stmt_list):
		Statement(type), stmt_list(stmt_list), local_decl_list(local_decl_list) {
			/* Merge(pass) code */
			for(Statement* local_decl : *local_decl_list)
				code += local_decl->code;
			
			for(Statement* stmt : *stmt_list)
				code += stmt->code;
		}
	double accept( Visitor* v) {}
};

class EmptyStmt : public Statement{
public:
	EmptyStmt(string type):
		Statement(type){ }
	double accept( Visitor* v) {}
};

class VariableDecl: public Statement{
public:
	string v_type;
	string v_name;
	VariableDecl(string type, string v_type, string v_name):
		Statement(type), v_type(v_type), v_name(v_name) { }
	double accept( Visitor* v) {}
};

class Expression : public AstNode{
public:
	string type;
	string code;
	string place;
	string True;
	string False;

	Expression* left;
	Expression* right;
	Expression(){ }
	Expression(string type): type(type) { }
	Expression(string type, Expression* left, Expression* right) : 
					type(type), left(left), right(right) { }
};

class BinOp : public Expression{
public:
	double accept( Visitor* v) {return v->visit(this);}
	
	BinOp( string type, Expression* left, Expression* right ) : 
				Expression(type, left, right){ }
	BinOp( string type) : 
				Expression(type){ }
};

class Int10 : public Expression{
public:		
	int val;
	double accept( Visitor* v){ return v->visit(this); }
	Int10( double val ): Expression("Int10"), val(val){}	
};

class Assign : public Expression{
public:
	double accept(Visitor * v){return v->visit(this);}
	Assign( string type, Expression* left, Expression* right ) : 
			Expression(type, left, right){ }
	Assign(string type):
		Expression(type){

		}
};

class Identifier : public Expression{
public:
	string name;
	bool hasRetVal;
	double accept( Visitor* v){ return v->visit(this); }
	Identifier(string type, string name, bool hasRetVal=false) :
			Expression(type), name(name), hasRetVal(hasRetVal) { }
};

class PrimitiveType : AstNode{
public:
	string type;
	PrimitiveType(string type) : type(type){}
	double accept( Visitor* v) {}
};

class Variable : public Statement{
public:
	PrimitiveType* v_type;
	Identifier* id;
	Variable(PrimitiveType* v_type, Identifier* id, string type):
				Statement(type), v_type(v_type), id(id){}
	double accept( Visitor* v) {}
};

class FunctionInvocation : public Expression{
public:
	Identifier* id;
	vector<Expression*>* arg_list;
	FunctionInvocation(Identifier* id, vector<Expression*>* arg_list, string type):
			Expression(type), id(id), arg_list(arg_list){}
	double accept( Visitor* v){ return v->visit(this); }
};

class Function : public Statement{
public:
	PrimitiveType* f_type;
	Identifier* id;
	vector<Variable*>* param_list;
	Statement* block;
	Function(PrimitiveType* f_type, Identifier* id, vector<Variable*>* param_list, Statement* block, string type):
			Statement(type), f_type(f_type), id(id), param_list(param_list), block(block){}
	double accept( Visitor* v) {}
};


class Real10 : public Expression{
public:
	double val;
	double accept(Visitor* v){return v->visit(this);}
	Real10(double val): Expression("Real10"), val(val){}
};

#endif
