#include "../header/visitor.h"
#include "../header/ast.h"
#include "../header/symbol.h"
#include "../header/codegen.h"	
#define RET_FROM_BINOP 114514.1919810
#define ERROR -1
#define SUCCESS 1

void RaiseError(Error error_type, string name="", int arg_num=0, int param_num=0, string arg_type="", string param_type=""){
	switch(error_type){
		case FUNC_REDECL:
		printf("Error type %d: Function named '%s' re-declaration\n",  
				error_type, name.c_str());
		break;

		case ID_REDECL:
		printf("Error type %d: Identifier named '%s' re-declaration\n", 
				error_type, name.c_str());
		break;

		case ARR_REDECL:
		printf("Error type %d: Array identifier named '%s' re-declaration\n", 
				error_type, name.c_str());
		break;

		case ID_NOT_DEFINE:
		printf("Error type %d: ID identifier named '%s' is not defined\n", 
				error_type, name.c_str());
		break;

		case ARR_NOT_DEFINE:
		printf("Error type %d: Array identifier named '%s' is not defined\n", 
				error_type, name.c_str());
		break;

		case FUNC_NOT_DEFINE:
		printf("Error type %d: Function named '%s' is not defined\n", 
				error_type, name.c_str());
		break;

		case ARR_INDEX_OUT_OF_BOUND:
		printf("Error type %d: Array identifier named '%s',  index out of bound\n",
				error_type, name.c_str());
		break;

		case ARR_INDEX_ACCESS_TYPE_INCOMPATIBLE:
		printf("Error type %d: Array identifier named '%s', array index type only support 'int' type\n",
				error_type, name.c_str());
		break;

		case RET_IN_VOID_FUNC_INCOMPATIBLE:
		printf("Error type %d: A function named '%s' with 'void' return value has return value\n",
				error_type, name.c_str());
		break;

		case RET_IN_NONVOID_FUNC_INCOMPATIBLE:
		printf("Error type %d: A function named '%s' with 'non-void' return value doesn't has return value\n",
				error_type, name.c_str());
		break;
		
		case FUNC_PARAMETER_INCOMPATIBLE:
		printf("Error type %d: Function named '%s' invocation args number is incompatibale with Function params number, has %d, expect %d\n",
				error_type, name.c_str(), arg_num, param_num);
		break;

		case FUNC_PARAMETER_TYPE_INCOMPATIBLE:
		printf("Error type %d: Function named '%s' invocation args type is incompatibale with Function params type, has '%s', expect '%s'\n",
				error_type, name.c_str(), arg_type.c_str(), param_type.c_str());
		break;

		default:
		printf("No such Error type\n");
		break;
	}
}

bool redeclCheck(string name, SymbolTable* sym_table){
	if(sym_table->s_arr.count(name) > 0 ||
		   sym_table->s_func.count(name) > 0 ||
		   sym_table->s_id.count(name) > 0 ||
		   sym_table->s_keyword.count(name) > 0)
			return true;
	return false;	
}

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
int   SemanticCheckVisitor::visit(Variable* v){
	SymbolTable* sym_table = this->sym_table;
	string name = v->id->name;
	if(redeclCheck(name, sym_table)){
		RaiseError(ID_REDECL, name);
		return ERROR;
	}
	return SUCCESS;
}
int   SemanticCheckVisitor::visit(Function* func){
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
int   SemanticCheckVisitor::visit(ArrayVariable* arr_var){
	SymbolTable* sym_table = this->sym_table;
	string name = arr_var->id->name;
	if(redeclCheck(name, sym_table)){
		RaiseError(ARR_REDECL, name);
		return ERROR;
	}
	return SUCCESS;
}
int   SemanticCheckVisitor::visit(AccessVar* acv){
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
		if(acv->index->number_type != "int"){
			RaiseError(ARR_INDEX_ACCESS_TYPE_INCOMPATIBLE, name);
			return ERROR;
		}
		if(acv->index->num.number < 0 || acv->index->num.number >= v->size){
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
int   SemanticCheckVisitor::visit(FunctionInvocation* func_invoke){
	SymbolTable* sym_table = this->sym_table;
	string name = func_invoke->id->name;
	if(!sym_table->s_func.count(name)){
		RaiseError(FUNC_NOT_DEFINE, name);
		return ERROR;
	}

	FuncSymbol* func = sym_table->s_func[name];
	vector<Expression*>* arg_list = func_invoke->arg_list;
	vector<Variable*>* param_list = func->param_list;
	if(arg_list->size() != param_list->size()){
		RaiseError(FUNC_PARAMETER_INCOMPATIBLE, name, arg_list->size(), func->param_list->size());
		return ERROR;
	}
	for(int i = 0; i < (*arg_list).size(); i++){
		Expression* arg = (*arg_list)[i];
		Variable* var = (*param_list)[i];
		if(arg->number_type != var->v_type->type){
			RaiseError(FUNC_PARAMETER_TYPE_INCOMPATIBLE, name, 0, 0, arg->number_type, var->v_type->type);
		}
	}

	return SUCCESS;
}
int   SemanticCheckVisitor::visit (IfStmt* n){
	return 0;
}
int   SemanticCheckVisitor::visit (WhileStmt* n){
	return 0;
}
int   SemanticCheckVisitor::visit (BlockStmt* n){
	return 0;
}
int   SemanticCheckVisitor::visit (EmptyStmt* n){
	return 0;
}
int   SemanticCheckVisitor::visit (ReturnStmt* n){
	return 0;
}
int   SemanticCheckVisitor::visit (ExpStmt* n){
	return 0;
}
int   SemanticCheckVisitor::visit (PrimitiveType* n){
	return 0;
}
float   SemanticCheckVisitor::visit (BinOp* n){
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
int   SemanticCheckVisitor::visit (UnaryOp* n){
	return 0;
}
int   SemanticCheckVisitor::visit (SyntaxRoot* n){
	return 0;
}
  

void  SyntaxTreeVisitor::printTab(){
	for(int i = 0; i < this->depth; i++){
		cout << '\t';
	}
}
float SyntaxTreeVisitor::visit (Expression* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->left->accept(this);
	
	n->right->accept(this);
	this->depth--;
	return 0.0f;
}
float SyntaxTreeVisitor::visit (Int10* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	this->depth--;
	return 0.0f;
}
float SyntaxTreeVisitor::visit (Real10* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	this->depth--;
	return 0.0f;
}
float SyntaxTreeVisitor::visit (Identifier* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	this->depth--;
	return 0.0f;
}
int   SyntaxTreeVisitor::visit (Variable* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->id->accept(this);
	
	n->v_type->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (ArrayVariable* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->id->accept(this);
	
	n->v_type->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (Function* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->f_type->accept(this);
	
	n->id->accept(this);
	vector<Variable*>* param_list = n->param_list;
	for(Variable* var : *param_list){
		var->id->accept(this);
		var->v_type->accept(this);
	}
	
	n->block->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (AccessVar* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->id->accept(this);
	
	n->index->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (FunctionInvocation* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->id->accept(this);
	vector<Expression*>* arg_list = n->arg_list;
	for(Expression* arg : *arg_list){
		
		arg->accept(this);
		
		arg->accept(this);
	}
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (IfStmt* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->e->accept(this);
	
	n->s1->accept(this);
	
	n->s2->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (WhileStmt* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->e->accept(this);
	
	n->s->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (BlockStmt* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	vector<Statement*>* stmt_list = n->stmt_list;
	vector<Statement*>* local_decl_list = n->local_decl_list;

	for(Statement* stmt : *stmt_list){
		
		stmt->accept(this);
	}
	for(Statement* local_decl : *local_decl_list){
		
		local_decl->accept(this);
	}
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (EmptyStmt* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (ReturnStmt* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->e->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (ExpStmt* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->e->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (PrimitiveType* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	this->depth--;
	return 0;
}
float SyntaxTreeVisitor::visit (BinOp* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	
	n->left->accept(this);
	
	n->right->accept(this);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (UnaryOp* n){
	
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	this->depth--;
	return 0;
}
int   SyntaxTreeVisitor::visit (SyntaxRoot* n){
	string str;
	str += string(this->depth, '\t');
	this->depth++;
	str += n->type + '\n';
	this->grammar_tree->push_back(str);
	vector<Statement*>* stmt_list;
	stmt_list = n->stmt_list;
	for(Statement* stmt : *stmt_list){
		
		stmt->accept(this);
	}
	this->depth--;
	return 0;
}


float TACVisitor::visit (Expression* n){
	n->left->accept(this);
	n->right->accept(this);
	return 0.0f;
}
float TACVisitor::visit (Int10* n){
	return 0.0f;
}
float TACVisitor::visit (Real10* n){
	return 0.0f;
}
float TACVisitor::visit (Identifier* n){
	return 0.0f;
}
int   TACVisitor::visit (Variable* n){
	n->id->accept(this);
	n->v_type->accept(this);
	return 0;
}
int   TACVisitor::visit (ArrayVariable* n){
	n->id->accept(this);
	n->v_type->accept(this);
	return 0;
}
int   TACVisitor::visit (Function* n){
	n->f_type->accept(this);
	n->id->accept(this);
	vector<Variable*>* param_list = n->param_list;
	for(Variable* var : *param_list){
		var->id->accept(this);
		var->v_type->accept(this);
	}
	
	n->block->accept(this);
	return 0;
}
int   TACVisitor::visit (AccessVar* n){
	n->id->accept(this);
	n->index->accept(this);
	return 0;
}
int   TACVisitor::visit (FunctionInvocation* n){
	n->id->accept(this);
	vector<Expression*>* arg_list = n->arg_list;
	for(Expression* arg : *arg_list){
		arg->left->accept(this);
		arg->right->accept(this);
	}
	return 0;
}
int   TACVisitor::visit (IfStmt* n){
	n->e->accept(this);
	n->s1->accept(this);
	n->s2->accept(this);
	return 0;
}
int   TACVisitor::visit (WhileStmt* n){
	n->e->accept(this);
	n->s->accept(this);
	return 0;
}
int   TACVisitor::visit (BlockStmt* n){
	vector<Statement*>* stmt_list = n->stmt_list;
	vector<Statement*>* local_decl_list = n->local_decl_list;

	for(Statement* stmt : *stmt_list){
		
		stmt->accept(this);
	}
	for(Statement* local_decl : *local_decl_list){
		
		local_decl->accept(this);
	}
	return 0;
}
int   TACVisitor::visit (EmptyStmt* n){
	return 0;
}
int   TACVisitor::visit (ReturnStmt* n){
	n->e->accept(this);
	return 0;
}
int   TACVisitor::visit (ExpStmt* n){
	n->e->accept(this);
	return 0;
}
int   TACVisitor::visit (PrimitiveType* n){
	return 0;
}
float TACVisitor::visit (BinOp* n){
	n->left->accept(this);
	
	n->right->accept(this);
	return 0;
}
int   TACVisitor::visit (UnaryOp* n){
	return 0;
}
int   TACVisitor::visit (SyntaxRoot* n){
	vector<Statement*>* stmt_list;
	stmt_list = n->stmt_list;
	for(Statement* stmt : *stmt_list){
		stmt->accept(this);
	}
	return 0;
}
