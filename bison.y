/*
* @name bison.yxx
* @description Cminus Language Syntax Analysis
* @date 05/26/2020 
* @author Rongqing Li
*/

%language "C++"
%defines
%locations
%skeleton "lalr1.cc"
%debug 

%code requires{
	#define YYDEBUG 1
	#include "header/ast.h"
	#include "header/visitor.h"
	#include "header/codegen.h"
	#include "header/symbol.h"
}

%code{
	#include <iostream>
	#include <unistd.h>
	#include <string>
	using namespace std;
	int yydebug=1;
	SymbolTable* sym_table = new SymbolTable();
}

%union{
	AstNode* a;
	Expression* e;
	Identifier* id;
	AccessVar* acv;
	Statement* stmt;
	BlockStmt* comp_stmt;
	vector<Statement*>* stmt_decl_list;
	vector<Variable*>* variable_list;
	vector<Expression*>* arg_list;
	Int10* int10;
	Real10* real10;
	Assign* assign;
	PrimitiveType* type;
	Variable* variable;
	Function* function;
	SyntaxRoot* syntax_root;
	int n;
	float d;
}

%parse-param {vector<string>** grammar_tree} {vector<string>* tokens}
%lex-param { vector<string>* tokens }

/* declearation */
%token END_OF_FILE
%token EOL
%token <real10> REAL10
%token <int10> INT10 
%token <e> ADD SUB MUL DIV 
%token <assign> ASSIGN
%token IF
%token LP RP MLP MRP LLP LRP 
%token WHILE ELSE RETURN TYPE_INT TYPE_VOID TYPE_FLOAT
%token LT GT  SEMICOLON COMMA
%token EQ GET LET NEQ
%token AND OR NOT
%token <id> ID

%type <e> expression simple_expression relop additive_expression addop term mulop factor call
		  //binary_logic unary_logic
%type <stmt> expression_stmt statement selection_stmt 
			 iteration_stmt return_stmt var_declearation fun_declearation 
			 declearation
%type <comp_stmt> compound_stmt 
%type <type> type_specifier
%type <variable> param
%type <variable_list> param_list params 
%type <arg_list> arg_list args
%type <stmt_decl_list> local_declearations statement_list declearation_list
%type <syntax_root> program
%type <acv> var
%nonassoc V_ELSE
%nonassoc ELSE
%{
	extern int yylex(yy::parser::semantic_type *yylval, yy::parser::location_type *yylloc, vector<string>* tokens);
%}

%%
	program: declearation_list {
		SyntaxTreeVisitor *stv = new SyntaxTreeVisitor();
		
		$$ = new SyntaxRoot($1);
		$$->accept(stv);
		*grammar_tree = stv->getGrammarTree();
		map<string, IdSymbol*> id_map = sym_table->s_id;
		for(auto it = id_map.begin(); it != id_map.end(); it++){
			IdSymbol* ids = it->second;
			cout << "Variable name=" << it->first << ", type=" << ids->type_specifier;
			if(ids->type_specifier == "int")
				cout << ", value=" << ids->num->val << endl; 
			else
				cout << ", value=" << ids->f_num->val << endl; 
		}
		Gen::genCode($1);
	}
	       ;

	declearation_list: declearation_list declearation{
		
		$1->push_back($2);
		$$ = $1;
	}
					 | declearation {
		
		$$ = new vector<Statement*>();
		$$->push_back($1);
	}
					 ;

	declearation: var_declearation {$$ = $1;}
				| fun_declearation {$$ = $1;}
				;

	var_declearation: type_specifier ID SEMICOLON {
		
		//semanticCheck($1, $2);
		/* name, (type, name, type_specifier) */
		
		Variable* v = new Variable($1, $2, "id_var");
		$$ = v;
		
		SemanticCheckVisitor *scv = new SemanticCheckVisitor(sym_table);
		if(-1 == v->accept(scv)){
			printf("Abort!\n");
			YYABORT;
		}
		sym_table->insertIdSymbol($2->name, new IdSymbol("id_var", $2->name, $1->type));
	}
					| type_specifier ID MLP INT10 MRP SEMICOLON {
		
		/* name, (type, name, type_specifier, size) */
		ArrayVariable* v = new ArrayVariable($1, $2, "arr_var", $4);
		$$ = v;
		

		SemanticCheckVisitor *scv = new SemanticCheckVisitor(sym_table);
		if(-1 == v->accept(scv)){
			printf("Abort!\n");
			YYABORT;
		}
		sym_table->insertArraySymbol($2->name, new ArraySymbol("arr_var", $2->name, $1->type, $4->val));
	}
					;

	type_specifier: TYPE_INT {$$ = new PrimitiveType("int");}
				  | TYPE_FLOAT{$$ = new PrimitiveType("float");}
				  | TYPE_VOID {$$ = new PrimitiveType("void");}
				  ;

	fun_declearation: type_specifier ID LP params RP compound_stmt{
		
		Function* func = new Function($1, $2, $4, $6);
		$$ = func;
		
		SemanticCheckVisitor *scv = new SemanticCheckVisitor(sym_table);
		if(-1 == func->accept(scv)){
			printf("Abort!\n");
			YYABORT;
		}
		sym_table->insertFuncSymbol($2->name, new FuncSymbol("func", $2->name, $1->type, $4));
		/* As for code generation, we only need
			function name($2) and function body($6) */
		Gen::genFunction($$, $2, $6);
		delete scv;
	}
					;

	params: param_list {$$ = $1;}
		  | TYPE_VOID  {
		
		/* Empty param list */
		$$ = new vector<Variable*>();
	}
		  | {$$ = new vector<Variable*>();}
		  ;

	param_list: param_list COMMA param{
		
		$1->push_back($3);
		$$ = $1;
	}
			  | param {
		$$ = new vector<Variable*>();
		$$->push_back($1);
		
	}
			  ;

	param: type_specifier ID {
		
		$$ = new Variable($1, $2, "param_id_var");
	}
		 | type_specifier ID MLP MRP {
		
		$$ = new ArrayVariable($1, $2, "param_arr_var");
	} 
		 ; 

	compound_stmt: LLP local_declearations statement_list LRP {
		/* Need to pass ($2, $3)->code to $$->code (implemented in construct function) */
		
		$$ = new BlockStmt("block", $2, $3);
	}
	;
	
	local_declearations: local_declearations var_declearation{
		
		$1->push_back($2);
		$$ = $1;		
	}
					   | {
		
		$$ = new vector<Statement*>();
	}
					   ;

	statement_list: statement_list statement {
		
		$1->push_back($2);
		$$ = $1;
	}
				  | {
		
		$$ = new vector<Statement*>();
	}
				  ;

	statement: expression_stmt {$$ = $1;} 
			 | compound_stmt {$$ = $1;}
			 | selection_stmt {$$ = $1;}
			 | iteration_stmt {$$ = $1;}
			 | return_stmt {$$ = $1;}
			 ;

	expression_stmt: expression SEMICOLON {
		/* Need to pass $1->code to $$->code (implemented in construct function) */
		
		$$ = new ExpStmt("exp", $1);
		$$->code = $1->code;
	}
				   | SEMICOLON {
		
		$$ = new EmptyStmt("empty");
	}
				   ;


	selection_stmt: IF LP expression RP	statement %prec V_ELSE{
		
		sym_table->insertKeywordSymbol("if", new KeyWordSymbol("if"));
		$$ = new IfStmt("if", $3, $5); 
		Gen::genIfStmt($$, $3, $5);
	}
				  | IF LP expression RP statement ELSE statement{
		
		$$ = new IfStmt("if", $3, $5, $7);
		Gen::genIfStmt($$, $3, $5, $7);
	}
	
	iteration_stmt: WHILE LP expression RP statement{
		
		$$ = new WhileStmt("while", $3, $5);
		Gen::genWhileStmt($$, $3, $5);
	}
				  ;
	
	return_stmt: RETURN SEMICOLON {$$ = new ReturnStmt(NULL, "empty_return");}
	           | RETURN expression SEMICOLON {
		
		$$ = new ReturnStmt($2, "return");
		Gen::genRetStmt($$, $2);
	}
			   ;

	expression: var ASSIGN expression {
		
		$2 = new Assign("=", $1->id, $3);
		if(!$1->index){
			IdSymbol* var =  sym_table->s_id[$1->id->name];
			string var_type = var->type_specifier;
			string exp_type = $3->number_type;
			if(var_type == "int"){
				if(exp_type == "int"){
					var->num->val = $3->num.number;
				}else if(exp_type == "float"){
					var->num->val = (int)$3->num.f_number;
				}
			}else if(var_type == "float"){
				if(exp_type == "float"){
					var->f_num->val = $3->num.f_number;
				}else if(exp_type == "int"){
					var->f_num->val = (float)$3->num.number;
				}
			}
		}
		SemanticCheckVisitor* scv = new SemanticCheckVisitor(sym_table);
		
		Gen::genAssign($2, $1->id, $3);
		$$ = $2; 
	}
	          | simple_expression {$$ = $1;}
			  ;

	var: ID { 
		
		AccessVar* v = new AccessVar($1);
		SemanticCheckVisitor *scv = new SemanticCheckVisitor(sym_table);
		if(-1 == v->accept(scv)){
			printf("abort!\n");
			YYABORT;
		}
		Gen::genId(v->id, $1);
		$$ = v;
	}
	   | ID MLP expression MRP {
		   
		   AccessVar* v = new AccessVar($1, $3);
		   SemanticCheckVisitor *scv = new SemanticCheckVisitor(sym_table);
		   if(-1 == v->accept(scv)){
		       printf("abort\n");
			   YYABORT;
		   }
		   Gen::genArr(v->id, $1, $3);
		   $$ = v;
		   
		}
	   ;
	
	simple_expression: additive_expression relop additive_expression{
		
		$2->left = $1; 
		$2->right = $3;
		Gen::genRelop($2, $1, $3, $2->type);
		$$ = $2;
	}
					 | additive_expression {$$ = $1;}

	relop: GT { $$ = new BinOp(">");}
		 | LT { $$ = new BinOp("<");}
		 | LET { $$ = new BinOp("<=");}
		 | GET { $$ = new BinOp(">=");}
		 | EQ { $$ = new BinOp("==");}
		 | NEQ { $$ = new BinOp("!=");}
		 ;	
	
	additive_expression: additive_expression addop term {
		
		$2->left = $1; 
		$2->right = $3; 
		
		SemanticCheckVisitor *scv = new SemanticCheckVisitor(sym_table);
		if($1->number_type == "int" && $3->number_type == "int"){
			$2->number_type = "int";
		}else{
			$2->number_type = "float";
		}
		
		if($2->number_type == "int"){
			$2->num.number = $2->accept(scv);
		}
		else{
			$2->num.f_number = $2->accept(scv);
		}
		Gen::genBinary($2, $1, $3, $2->type);
		$$ = $2;
	}
					   | term {$$ = $1;}
					   ;
	
	addop: ADD {
		
		$$ = new BinOp("+");
	}
	     | SUB {
		
		$$ = new BinOp("-");
	}
		 ;

	term: term mulop factor {
		
		$2->left = $1;
		$2->right = $3;

		SemanticCheckVisitor *scv = new SemanticCheckVisitor(sym_table);

		if($1->number_type == "float" && $3->number_type == "float" ||
		   $1->number_type != $3->number_type)
			$2->number_type = "float";
		else
			$2->number_type = "int";

		if($2->number_type == "int")
			$2->num.number = $2->accept(scv);
		else
			$2->num.f_number = $2->accept(scv);
		Gen::genBinary($2, $1, $3, $2->type);
		$$ = $2;
	}
	    | factor {
		
		$$ =  $1;
	}
		;
	
	mulop: MUL {
		
		$$ = new BinOp("*");
	}
	     | DIV {
		
		$$ = new BinOp("/");
	}
		 ;

	factor: LP expression RP {
		
		$$ = $2;
	}
	      | var {
		
		$1->id->number_type = sym_table->s_id[$1->id->name]->type_specifier;
		$$ = $1->id;
	} 
		  | call {
		
		$$ = $1;
	}
		  | INT10 {
		
		Gen::genInt10($$, $1); 
		$1->number_type = "int";
		$1->num.number = $1->val;
		$$ = $1;
	}
		  | REAL10 {
		
		Gen::genReal10($$, $1); 
		$1->number_type = "float";
		$1->num.f_number = $1->val;
		$$ = $1;
	}
		  ;

	call: ID LP args RP {
		
		FunctionInvocation* func_invoke = new FunctionInvocation($1, $3, "invoke");
		SemanticCheckVisitor *scv = new SemanticCheckVisitor(sym_table);
		if(-1 == func_invoke->accept(scv)){
			printf("Abort!\n");
			YYABORT;
		}
		$$ = func_invoke;
		Gen::genFunctionInvoke($$, $1, $3, sym_table);
		
	}
		;

	args: arg_list {$$ = $1;}
	    | {$$ = new vector<Expression*>();};

	arg_list: arg_list COMMA expression {
		
		$1->push_back($3);
	}
		    | expression {
		
		$$ = new vector<Expression*>();
		$$->push_back($1);
	}
			;
%%

namespace yy{
	void
	parser::error(location const &loc, const std::string &s){
			std::cerr << "syntax error at " << loc << ": " << s << std::endl;
	}
}
