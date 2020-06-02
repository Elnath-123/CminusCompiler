#include "../header/visitor.h"
#include "../header/ast.h"
#include "../header/symbol.h"	
#define RET_FROM_BINOP 114514.1919810
#define ERROR -1
#define SUCCESS 1
void RaiseError(Error, string);
/* SemanticCheckVisitor */
float SemanticCheckVisitor::visit ( Expression* n ){
	float v;
	if (n->type == "+")
		v = n->left->accept(this) + n->right->accept(this);
	else if (n->type == "-")
		v = n->left->accept(this) - n->right->accept(this);
	else if (n->type == "*")
		v = n->left->accept(this) * n->right->accept(this);
	else if (n->type == "/")
		v = n->left->accept(this) / n->right->accept(this);
	return v;
}

float SemanticCheckVisitor::visit(Int10* n){
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
		RaiseError(ID_REDECL, name);
		return ERROR;
	}
	return SUCCESS;
}

int SemanticCheckVisitor::visit(Function* func){
	SymbolTable* sym_table = this->sym_table;
	string name = func->id->name;

	if(redeclCheck(name, sym_table)){
		RaiseError(FUNC_REDECL, name);
		return ERROR;
	}	
	return SUCCESS;
}

int SemanticCheckVisitor::visit(ArrayVariable* arr_var){
	SymbolTable* sym_table = this->sym_table;
	string name = arr_var->id->name;
	if(redeclCheck(name, sym_table)){
		RaiseError(ARR_REDECL, name);
		return ERROR;
	}
	return SUCCESS;
}

int SemanticCheckVisitor::visit(AccessVar* acv){
	SymbolTable* sym_table = this->sym_table;
	string name = acv->id->name;
	ArraySymbol* v = sym_table->s_arr[name];
	if(acv->index < 0 || acv->index->number >= v->size){
		RaiseError(ARR_INDEX_OUT_OF_BOUND, name);
		return ERROR;
	}
	return SUCCESS;
}

void RaiseError(Error error_type, string name){
	switch(error_type){
		case FUNC_REDECL:
		printf("Error type %d: Function named '%s' re-declaration\n",  error_type, name.c_str());
		break;

		case ID_REDECL:
		printf("Error type %d: Identifier named '%s' re-declaration\n", error_type, name.c_str());
		break;

		case ARR_REDECL:
		printf("Error type %d: Array identifier named '%s' re-declaration\n", error_type, name.c_str());
		break;

		case ARR_INDEX_OUT_OF_BOUND:
		printf("Error type %d: Array identifier named '%s',  index out of bound\n", error_type, name.c_str());
		break;

		case ARR_INDEX_ACCESS_TYPE_IMCOMPATIBLE:
		printf("Error type %d: Array identifier named '%s', array index type only support 'int' type", error_type, name.c_str());
	}
}


/* PostfixVisitor 
float PostfixVisitor::visit( Expression* n ){
	float vLeft  = n->left->accept(this);
	if(vLeft != RET_FROM_BINOP) std::cout << vLeft << ' ';
	float vRight = n->right->accept(this);	
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

float PostfixVisitor::visit( Int10* n){
	return n->val;
}

*/