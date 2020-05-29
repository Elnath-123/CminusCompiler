#ifndef _VISITOR_H
#define _VISITOR_H
class AstNode;
class BinOp;
class Expression;
class Int10;

class Visitor{
public:
	virtual double visit ( Expression* n ) = 0;
	virtual double visit ( Int10* n) = 0;
};

class EvalVisitor : public Visitor{	
public:
	virtual double visit ( Expression* n );
	virtual double visit ( Int10* n );
};

class PostfixVisitor : public Visitor{
public:
	virtual double visit ( Expression* n );
	virtual double visit ( Int10* n );
};	

#endif
