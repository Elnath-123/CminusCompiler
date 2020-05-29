#include "../header/visitor.h"
#include "../header/ast.h"
#include "../header/symbol.h"	
#define RET_FROM_BINOP 114514.1919810
#define ERROR -1
void RaiseError(Error);
/* SemanticCheckVisitor */
double SemanticCheckVisitor::visit ( Expression* n ){
	double v;
	if (n->type == "Plus")
		v = n->left->accept(this) + n->right->accept(this);
	else if (n->type == "Sub")
		v = n->left->accept(this) - n->right->accept(this);
	else if (n->type == "Mul")
		v = n->left->accept(this) * n->right->accept(this);
	else if (n->type == "Div")
		v = n->left->accept(this) / n->right->accept(this);
	return v;
}

double SemanticCheckVisitor::visit(Int10* n){
	return n->val;
}

bool redeclCheck(string name, SymbolTable* sym_table){
	if(sym_table->s_arr.count(name) > 0 ||
		   sym_table->s_func.count(name) > 0 ||
		   sym_table->s_id.count(name) > 0 ||
		   sym_table->s_keyword.count(name) > 0)
			return true;
	return false;	
}
/* Semantic check */
int SemanticCheckVisitor::visit(Variable* v){
	SymbolTable* sym_table = this->sym_table;
	string name = v->id->name;
	if(redeclCheck(name, sym_table)){
		RaiseError(ID_REDECL);
		return ERROR;
	}
}

int SemanticCheckVisitor::visit(Function* func){
	SymbolTable* sym_table = this->sym_table;
	string name = func->id->name;

	if(redeclCheck(name, sym_table)){
		RaiseError(FUNC_REDECL);
		return ERROR;
	}	
}

int SemanticCheckVisitor::visit(ArrayVariable* arr_var){
	SymbolTable* sym_table = this->sym_table;
	string name = arr_var->id->name;

	if(redeclCheck(name, sym_table)){
		RaiseError(ARR_REDECL);
		return ERROR;
	}
}

void RaiseError(Error error_type){
	switch(error_type){
		case FUNC_REDECL:
		printf("Error type %d: function re-declaration\n", error_type);
		break;

		case ID_REDECL:
		printf("Error type %d: identifier re-declaration\n", error_type);
		break;

		case ARR_REDECL:
		printf("Error type %d: identifier re-declaration\n", error_type);
		break;
	}
}


/* PostfixVisitor 
double PostfixVisitor::visit( Expression* n ){
	double vLeft  = n->left->accept(this);
	if(vLeft != RET_FROM_BINOP) std::cout << vLeft << ' ';
	double vRight = n->right->accept(this);	
	if(vRight != RET_FROM_BINOP) std::cout << vRight << ' ';
	if (n->type == "Plus")
		std::cout << '+' << ' ';		
	else if (n->type == "Sub")
		std::cout << '-' << ' ';
	else if (n->type == "Mul")
		std::cout << '*' << ' ';
	else if (n->type == "Div")
		std::cout << '/' << ' ';
	return RET_FROM_BINOP;
}

double PostfixVisitor::visit( Int10* n){
	return n->val;
}

*/