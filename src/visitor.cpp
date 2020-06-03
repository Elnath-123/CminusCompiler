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

float SemanticCheckVisitor::visit(Real10* n){
	return n->val;
}

float SemanticCheckVisitor::visit(Identifier* id){
	SymbolTable* sym_table = this->sym_table;
	string type = sym_table->s_id[id->name]->type_specifier;
	if(type == "int"){
		return sym_table->s_id[id->name]->num->val;
	}
	return sym_table->s_id[id->name]->f_num->val;
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
	vector<ReturnStmt*>* ret_decl_list = func->block->ret_decl_list;
	
	/* No return statement but function is 'void' */
	if(func->f_type->type != "void" && !ret_decl_list->size()){
		RaiseError(RET_IN_NONVOID_FUNC_INCOMPATIBLE, name);
		return ERROR;
	}
	for(ReturnStmt* ret_decl : *ret_decl_list){
		/* Has return statement and expression but function is 'void' */
		if(func->f_type->type == "void" && ret_decl->e){
			RaiseError(RET_IN_VOID_FUNC_INCOMPATIBLE, name);
			return ERROR;
		}
		/* Has return statement and no expression but function isn't void */
		if(func->f_type->type != "void" && !ret_decl->e){
			RaiseError(RET_IN_NONVOID_FUNC_INCOMPATIBLE, name);
			return ERROR;
		}
	}

	/*for(ReturnStmt* ret_decl : *ret_decl_list){
		if(ret_decl->e->)
	}*/

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
	
	/* acv->index != NULL represents to access an Array */
	if(acv->index){
		ArraySymbol* v;
		if(sym_table->s_arr.count(name)){
			v = sym_table->s_arr[name];
		}else{
			RaiseError(ARR_NOT_DEFINE, name);
			return ERROR;
		}
		if(acv->index < 0 || acv->index->num.number >= v->size){
			RaiseError(ARR_INDEX_OUT_OF_BOUND, name);
			return ERROR;
		}
	}else{
		IdSymbol* v;
		if(sym_table->s_id.count(name)){
			v = sym_table->s_id[name];
		}else{
			RaiseError(ID_NOT_DEFINE, name);
			return ERROR;
		}
	}
	
	return SUCCESS;
}

int SemanticCheckVisitor::visit(FunctionInvocation* func_invoke){
	SymbolTable* sym_table = this->sym_table;
	string name = func_invoke->id->name;
	if(!sym_table->s_func.count(name)){
		RaiseError(FUNC_NOT_DEFINE, name);
		return ERROR;
	}
	return SUCCESS;
}
void RaiseError(Error error_type, string name=""){
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

		case ID_NOT_DEFINE:
		printf("Error type %d: ID identifier named '%s' is not defined\n", error_type, name.c_str());
		break;

		case ARR_NOT_DEFINE:
		printf("Error type %d: Array identifier named '%s' is not defined\n", error_type, name.c_str());
		break;

		case FUNC_NOT_DEFINE:
		printf("Error type %d: Function named '%s' is not defined\n", error_type, name.c_str());
		break;

		case ARR_INDEX_OUT_OF_BOUND:
		printf("Error type %d: Array identifier named '%s',  index out of bound\n", error_type, name.c_str());
		break;

		case ARR_INDEX_ACCESS_TYPE_INCOMPATIBLE:
		printf("Error type %d: Array identifier named '%s', array index type only support 'int' type\n", error_type, name.c_str());
		break;

		case RET_IN_VOID_FUNC_INCOMPATIBLE:
		printf("Error type %d: A function named '%s' with 'void' return value has return value\n", error_type, name.c_str());
		break;

		case RET_IN_NONVOID_FUNC_INCOMPATIBLE:
		printf("Error type %d: A function named '%s' with 'non-void' return value doesn't has return value\n", error_type, name.c_str());
		break;

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