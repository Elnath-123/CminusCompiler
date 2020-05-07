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
#include "visitor.h"

class AstNode{
public:
	AstNode(){ }
	virtual double accept( Visitor* v ) = 0;
};

class Statement : public AstNode{
public:
	std::string type;
	
	Statement(std::string type):
		type(type) {}
};

class IfStmt : public Statement{
public:
	Statement* s1;
	Statement* s2;
	Expression* e;
	IfStmt(std::string type, Expression* e, Statement* s1, Statement* s2 = nullptr):
		Statement(type), s1(s1), s2(s2), e(e) {}

	double accept( Visitor* v) {}
};

class WhileStmt : public Statement{
public:
	Statement* s;
	Expression* e;
	WhileStmt(std::string type, Expression* e, Statement* s):
		Statement(type), s(s), e(e) {}
	
	double accept( Visitor* v) {}
};

class ReturnStmt : public Statement{
	
};

class ExpStmt : public Statement{
public:
	ExpStmt(std::string type):
		Statement(type) {}
	double accept( Visitor* v) {}
};

class BlockStmt : public Statement{
public:
	Statement* s;
	BlockStmt(std::string type, Statement* s):
		Statement(type), s(s) {}
	double accept( Visitor* v) {}
};

class EmptyStmt : public Statement{
public:
	double accept( Visitor* v) {}
};

class Expression : public AstNode{
public:
	std::string type;
	std::string code;
	std::string place;

	Expression* left;
	Expression* right;
	Expression(){ }
	Expression(std::string type): type(type) { }
	Expression(std::string type, Expression* left, Expression* right) : type(type), left(left), right(right) { }
};

class BinOp : public Expression{
public:
	double accept( Visitor* v) {return v->visit(this);}
	
	BinOp( std::string type, Expression* left, Expression* right ) : 
				Expression(type, left, right){ }
	BinOp( std::string type) : 
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
	Assign( std::string type, Expression* left, Expression* right ) : 
			Expression(type, left, right){ }
	Assign(std::string type):
		Expression(type){

		}
};

class Identifier : public Expression{
public:
	std::string name;
	double accept( Visitor* v){ return v->visit(this); }
	Identifier(std::string type, std::string name) :
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
