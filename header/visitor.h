#ifndef _VISITOR_H
#define _VISITOR_H
#include <string>
using namespace std;
enum Error{
	FUNC_REDECL,
	ID_REDECL,
	ARR_REDECL
};

class AstNode;
class BinOp;
class Expression;
class Int10;

class Compose;
class SymbolTable;
class Variable;
class ArrayVariable;
class Function;

class Visitor{
public:
	SymbolTable* sym_table;
	virtual double visit (Expression* n) = 0;
	virtual double visit (Int10* n) = 0;
	virtual int    visit (Variable*) = 0;
	virtual int    visit (ArrayVariable*) = 0;
	virtual int    visit (Function*) = 0;
	Visitor(SymbolTable* sym_table):
		sym_table(sym_table) {}
};

class SemanticCheckVisitor : public Visitor{	
public:
	virtual double visit (Expression* n);
	virtual double visit (Int10* n);
	virtual int    visit (Variable*);
	virtual int    visit (ArrayVariable*);
	virtual int    visit (Function*);
	SemanticCheckVisitor(SymbolTable* sym_table):
		Visitor(sym_table) {}
};

/*class PostfixVisitor : public Visitor{
public:
	virtual double visit ( Expression* n );
	virtual double visit ( Int10* n );
};	
*/
#endif
