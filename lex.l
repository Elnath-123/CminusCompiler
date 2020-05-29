/*
* @name lex.l
* @description Cminus Language Lexical Analysis
* @date 05/24/2020 
* @author Rongqing Li
*/

%option noyywrap nodefault yylineno
%{
#include "bison.tab.hxx"
#include "ast.h"
#include <iostream>
#include <cstdio>
using namespace std;
#define YY_DECL int yylex(yy::parser::semantic_type *yylval, \
		yy::parser::location_type *yylloc)

/* Convert number in the format of char to number*/
	int numchar2int(char num){
		if(num >= '0' && num <= '9') return num - '0';	
		else if (num >= 'a' && num <= 'f') return num - 'a' + 10;
	}
	float _oct2dec(string oct){
		float base = 1;
		int dotpos = oct.size();
		for(int i = 0; i < oct.size(); i++)
			if(oct[i] == '.'){
				dotpos = i;
				break;
			}
		float sum = 0;
		for(int i = dotpos - 1; i >= 1; i--){
			sum += numchar2int(oct[i]) * base;
			base *= 8;
		}
		if(dotpos != oct.size()){
			base = 1.0/8;
			for(int i = dotpos + 1; i < oct.size(); i++){
				sum += 1.0 * numchar2int(oct[i]) * base;
				base /= 8;
			}
		}
		return sum;
	}
	float _hex2dec(string hex){
		float base = 1;
		int dotpos = hex.size();
		for(int i = 0; i < hex.size(); i++)
			if(hex[i] == '.'){
				dotpos = i;
				break;
			}
		float sum = 0;
		for(int i = dotpos - 1; i >= 2; i--){
			sum += numchar2int(hex[i]) * base;
			base *= 16;
		}
		if(dotpos != hex.size()){
			base = 1.0/8;
			for(int i = dotpos + 1; i < hex.size(); i++){
				sum += 1.0 * numchar2int(hex[i]) * base;
				base /= 16;
			}
		}
		return sum;
	}
FILE* fp = fopen("task1.txt", "w");

/*fp = fopen("task1.output", "w") == NULL){
	printf("open task1.output error!\n\n");
}*/
%}

%%

"if" {fprintf(fp, "if\t\t\t_\n\n");return yy::parser::token::IF;}
"while" {fprintf(fp, "while\t\t_\n\n");return yy::parser::token::WHILE;}
"else" {fprintf(fp, "else\t\t_\n\n");return yy::parser::token::ELSE;}
"return" {fprintf(fp, "return\t\t_\n\n");return yy::parser::token::RETURN;}
"int" {fprintf(fp, "int\t\t\t_\n\n");return yy::parser::token::TYPE_INT;}
"float" {fprintf(fp, "float\t\t_\n\n");return yy::parser::token::TYPE_FLOAT;}
"void" {fprintf(fp, "void\t\t\t_\n\n");return yy::parser::token::TYPE_VOID;}
"+" {fprintf(fp, "+\t\t\t_\n\n");return yy::parser::token::ADD;}
"-" {fprintf(fp, "-\t\t\t_\n\n");return yy::parser::token::SUB;}
"*" {fprintf(fp, "*\t\t\t_\n\n");return yy::parser::token::MUL;}
"/" {fprintf(fp, "/\t\t\t_\n\n");return yy::parser::token::DIV;}
">" {fprintf(fp, ">\t\t\t_\n\n");return yy::parser::token::GT;}
"<" {fprintf(fp, "<\t\t\t_\n\n");return yy::parser::token::LT;}
";" {fprintf(fp, ";\t\t\t_\n\n");return yy::parser::token::SEMICOLON;}
"=" {fprintf(fp, "=\t\t\t_\n\n");return yy::parser::token::ASSIGN;}
"<=" {fprintf(fp, "<=\t\t\t_\n\n");return yy::parser::token::LET;}
">=" {fprintf(fp, ">=\t\t\t_\n\n");return yy::parser::token::GET;}
"==" {fprintf(fp, "==\t\t\t_\n\n");return yy::parser::token::EQ;}
"!=" {fprintf(fp, "!=\t\t\t_\n\n");return yy::parser::token::NEQ;}
"(" {fprintf(fp, "(\t\t\t_\n\n");return yy::parser::token::LP;}
")" {fprintf(fp, ")\t\t\t_\n\n");return yy::parser::token::RP;}
"[" {fprintf(fp, "[\t\t\t_\n\n");return yy::parser::token::MLP;}
"]" {fprintf(fp, "]\t\t\t_\n\n");return yy::parser::token::MRP;}
"{" {fprintf(fp, "{\t\t\t_\n\n");return yy::parser::token::LLP;}
"}" {fprintf(fp, "}\t\t\t_\n\n");return yy::parser::token::LRP;}
"," {fprintf(fp, ",\t\t\t_\n\n");return yy::parser::token::COMMA;}
"&&" {return yy::parser::token::AND;}
"||" {return yy::parser::token::OR;}
"!"  {return yy::parser::token::NOT;}


[a-zA-Z][a-zA-Z0-9]*|[a-zA-Z][a-zA-Z0-9]*[._][a-zA-Z0-9]+ {fprintf(fp, "IDN\t\t\t%s\n\n", yytext);yylval->id = new Identifier("ID", yytext); return yy::parser::token::ID;}


0x[0-9a-f][0-9a-f]* {fprintf(fp, "INT16\t\t%d\n\n", (int)_hex2dec(yytext));yylval->int10 = new Int10(_hex2dec(yytext)); return yy::parser::token::INT10;}
0|[1-9][0-9]* {fprintf(fp, "INT10\t\t%d\n\n", atoi(yytext));yylval->int10 = new Int10(atoi(yytext)); return yy::parser::token::INT10;}
0[1-7][0-7]* {fprintf(fp, "INT8\t\t%d\n\n", (int)_oct2dec(yytext));yylval->int10 = new Int10(_oct2dec(yytext)); return yy::parser::token::INT10;}

(0|[1-9][0-9]*)[.][0-9]+ {fprintf(fp, "REAL10\t\t%f\n\n", atof(yytext));yylval->real10 = new Real10(atof(yytext)); return yy::parser::token::REAL10;}
0[0-7]+[.][0-7]+ {fprintf(fp, "REAL8\t\t%f\n\n", _oct2dec(yytext));yylval->real10 = new Real10(_oct2dec(yytext));  return yy::parser::token::REAL10;}
0x[0-9a-f]+[.][0-9a-f]+ {fprintf(fp, "REAL16\t\t%f\n\n", _hex2dec(yytext));yylval->real10 = new Real10(_hex2dec(yytext)); return yy::parser::token::REAL10;}


\n { yylloc->lines(1);}
[ \t] { yylloc->step(); }
. {printf("Invalid character %c\n\n", *yytext);}
%%
