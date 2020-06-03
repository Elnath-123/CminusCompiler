#ifndef _VISITOR_H
#define _VISITOR_H
#include <string>
using namespace std;
enum Error{
	DIVIDE_BY_ZERO,
	FUNC_REDECL,
	ID_REDECL,
	ARR_REDECL,
	FUNC_NOT_DEFINE,
	ID_NOT_DEFINE,
	ARR_NOT_DEFINE,
	ARR_INDEX_OUT_OF_BOUND,
	ARR_INDEX_ACCESS_TYPE_INCOMPATIBLE,
	RET_TYPE_INCOMPATIBLE,
	RET_IN_VOID_FUNC_INCOMPATIBLE,
	RET_IN_NONVOID_FUNC_INCOMPATIBLE,
	FUNC_PARAMETER_INCOMPATIBLE,
	FUNC_PARAMETER_TYPE_INCOMPATIBLE
};

enum Warning{
	RET_TYPE_CONVERTION
};

class AstNode;
class BinOp;
class Expression;
class Int10;
class Real10;
class Identifier;

class Compose;
class SymbolTable;
class Variable;
class ArrayVariable;
class Function;
class AccessVar;
class FunctionInvocation;
class ReturnStmt;

class Visitor{
public:
	SymbolTable* sym_table;
	virtual float  visit (Expression* n) = 0;
	virtual float  visit (Int10* n) = 0;
	virtual float  visit (Real10* n) = 0;
	virtual float  visit (Identifier* ) = 0;
	virtual int    visit (Variable*) = 0;
	virtual int    visit (ArrayVariable*) = 0;
	virtual int    visit (Function*) = 0;
	virtual int    visit (AccessVar*) = 0;
	virtual int    visit (FunctionInvocation*) = 0;
	virtual int    visit (IfStmt*) = 0;
	virtual int    visit (WhileStmt*) = 0;
	virtual int    visit (BlockStmt*) = 0;
	virtual int    visit (EmptyStmt*) = 0;
	virtual int    visit (ReturnStmt*) = 0;
	virtual int    visit (ExpStmt*) = 0;
	virtual int    visit (PrimitiveType*) = 0;
	virtual int    visit (BinOp*) = 0;
	virtual int    visit (UnaryOp*) = 0;
	Visitor(SymbolTable* sym_table):
		sym_table(sym_table) {}
};

class SemanticCheckVisitor : public Visitor{	
public:
	virtual float  visit (Expression* n);
	virtual float  visit (Int10* n);
	virtual float  visit (Real10* n);
	virtual float  visit (Identifier* );
	virtual int    visit (Variable*);
	virtual int    visit (ArrayVariable*);
	virtual int    visit (Function*);
	virtual int    visit (AccessVar*);
	virtual int    visit (FunctionInvocation*);
	virtual int    visit (IfStmt*);
	virtual int    visit (WhileStmt*);
	virtual int    visit (BlockStmt*);
	virtual int    visit (EmptyStmt*);
	virtual int    visit (ReturnStmt*);
	virtual int    visit (ExpStmt*);
	virtual int    visit (PrimitiveType*);
	virtual int    visit (BinOp*);
	virtual int    visit (UnaryOp*);
	SemanticCheckVisitor(SymbolTable* sym_table):
		Visitor(sym_table) {}
};

class SyntaxTreeVisitor : public Visitor{
	public:
		virtual float  visit (Expression* n);
		virtual float  visit (Int10* n);
		virtual float  visit (Real10* n);
		virtual float  visit (Identifier* );
		virtual int    visit (Variable*);
		virtual int    visit (ArrayVariable*);
		virtual int    visit (Function*);
		virtual int    visit (AccessVar*);
		virtual int    visit (FunctionInvocation*);
		virtual int    visit (IfStmt*);
		virtual int    visit (WhileStmt*);
		virtual int    visit (BlockStmt*);
		virtual int    visit (EmptyStmt*);
		virtual int    visit (ReturnStmt*);
		virtual int    visit (ExpStmt*);
		virtual int    visit (PrimitiveType*);
		virtual int    visit (BinOp*);
		virtual int    visit (UnaryOp*);
}




/*class PostfixVisitor : public Visitor{
public:
	virtual float visit ( Expression* n );
	virtual float visit ( Int10* n );
};	
*/
#endif
