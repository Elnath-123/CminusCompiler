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

class Visitor{
public:
	virtual double visit (Expression* n) = 0;
	virtual double visit (Int10* n) = 0;
	virtual int    visit (Compose*, string) = 0;
};

class SemanticCheckVisitor : public Visitor{	
public:
	virtual double visit (Expression* n);
	virtual double visit (Int10* n);
	virtual int    visit (Compose*, string);
};

/*class PostfixVisitor : public Visitor{
public:
	virtual double visit ( Expression* n );
	virtual double visit ( Int10* n );
};	
*/
#endif
