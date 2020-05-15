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
	
	Statement(string type):
		type(type) {}
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
		Statement(type), e(e) {}
	double accept( Visitor* v) {}
};

class BlockStmt : public Statement{
public:
	vector<Statement*>* stmt_list;
	vector<Statement*>* decl;
	BlockStmt(string type, vector<Statement*>* decl, vector<Statement*>* stmt_list):
		Statement(type), stmt_list(stmt_list), decl(decl) {}
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

	Expression* left;
	Expression* right;
	Expression(){ }
	Expression(string type): type(type) { }
	Expression(string type, Expression* left, Expression* right) : type(type), left(left), right(right) { }
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
	double accept( Visitor* v){ return v->visit(this); }
	Identifier(string type, string name) :
			Expression(type), name(name) {
				//std::cout << this->name << std::endl;
			}
};


class Real10 : public Expression{
public:
	double val;
	double accept(Visitor* v){return v->visit(this);}
	Real10(double val): Expression("Real10"), val(val){}
};

#endif
