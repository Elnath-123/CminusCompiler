%option noyywrap nodefault yylineno
%{
#include "bison.tab.hxx"
#include "ast.h"
#include <iostream>
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
%}

%%

"if" {return yy::parser::token::IF;}
"while" {return yy::parser::token::WHILE;}
"else" {return yy::parser::token::ELSE;}
"return" {return yy::parser::token::RETURN;}
"int" {return yy::parser::token::TYPE_INT;}
"float" {return yy::parser::token::TYPE_FLOAT;}
"void" {return yy::parser::token::TYPE_VOID;}
"+" {return yy::parser::token::ADD;}
"-" {return yy::parser::token::SUB;}
"*" {return yy::parser::token::MUL;}
"/" {return yy::parser::token::DIV;}
">" {return yy::parser::token::GT;}
"<" {return yy::parser::token::LT;}
";" {return yy::parser::token::SEMICOLON;}
"=" {return yy::parser::token::ASSIGN;}
"<=" {return yy::parser::token::LET;}
">=" {return yy::parser::token::GET;}
"==" {return yy::parser::token::EQ;}
"!=" {return yy::parser::token::NEQ;}
"(" {return yy::parser::token::LP;}
")" {return yy::parser::token::RP;}
"[" {return yy::parser::token::MLP;}
"]" {return yy::parser::token::MRP;}
"{" {return yy::parser::token::LLP;}
"}" {return yy::parser::token::LRP;}
"," {return yy::parser::token::COMMA;}
"&&" {return yy::parser::token::AND;}
"||" {return yy::parser::token::OR;}
"!"  {return yy::parser::token::NOT;}


[a-zA-Z][a-zA-Z0-9]*|[a-zA-Z][a-zA-Z0-9]*[._][a-zA-Z0-9]+ {yylval->id = new Identifier("ID", yytext); return yy::parser::token::ID;}


0x[0-9a-f][0-9a-f]* {yylval->int10 = new Int10(_hex2dec(yytext)); return yy::parser::token::INT10;}
0|[1-9][0-9]* {yylval->int10 = new Int10(atoi(yytext)); return yy::parser::token::INT10;}
0[1-7][0-7]* {yylval->int10 = new Int10(_oct2dec(yytext)); return yy::parser::token::INT10;}

(0|[1-9][0-9]*)[.][0-9]+ {yylval->real10 = new Real10(atof(yytext)); return yy::parser::token::REAL10;}
0[0-7]+[.][0-7]+ {yylval->real10 = new Real10(_oct2dec(yytext));  return yy::parser::token::REAL10;}
0x[0-9a-f]+[.][0-9a-f]+ {yylval->real10 = new Real10(_hex2dec(yytext)); return yy::parser::token::REAL10;}


\n { yylloc->lines(1);}
[ \t] { yylloc->step(); }
. {printf("Invalid character %c\n", *yytext);}
%%
