#ifndef _VISITOR_H
#define _VISITOR_H
#include <string>
#include <vector>
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
/* Symbol table */
class Compose;
class SymbolTable;


/* AstNode (root) */
class AstNode;

/* SyntaxTree root */
class SyntaxRoot;

/* Expression */
class Expression;
class BinOp;
class Int10;
class Real10;
class Identifier;
class UnaryOp;
class FunctionInvocation;

/* Statement */
class Statement;
class Variable;
class ArrayVariable;
class Function;
class ReturnStmt;
class IfStmt;
class WhileStmt;
class BlockStmt;
class EmptyStmt;
class ExpStmt;

/* PrimitiveType */
class PrimitiveType;

/* AccessVar */
class AccessVar;


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
	virtual int    visit (SyntaxRoot*) = 0;
	Visitor(SymbolTable* sym_table):
		sym_table(sym_table) {}
	Visitor(){}
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
	virtual int    visit (SyntaxRoot*);
	SemanticCheckVisitor(SymbolTable* sym_table):
		Visitor(sym_table) {}
};

class SyntaxTreeVisitor : public Visitor{
	private:
		int depth;
		vector<string>* grammar_tree;
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
		virtual int    visit (SyntaxRoot*);
		vector<string>* getGrammarTree(){return this->grammar_tree;}
		void printTab();
		SyntaxTreeVisitor(): depth(0) {grammar_tree = new vector<string>();}
};




/*class PostfixVisitor : public Visitor{
public:
	virtual float visit ( Expression* n );
	virtual float visit ( Int10* n );
};	
*/
#endif
