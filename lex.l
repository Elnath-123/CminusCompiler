/*
* @name lex.l
* @description Cminus Language Lexical Analysis
* @date 05/24/2020 
* @author Rongqing Li
*/

%option noyywrap nodefault yylineno
%{
#include "bison.tab.hh"
#include "header/ast.h"
#include <cstdarg>
#include <iostream>
#include <cstdio>
using namespace std;
#define YY_DECL int yylex(yy::parser::semantic_type *yylval, \
		yy::parser::location_type *yylloc, vector<string>* tokens)

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
			base = 1.0 / 16;
			for(int i = dotpos + 1; i < hex.size(); i++){
				sum += 1.0 * numchar2int(hex[i]) * base;
				base /= 16;
			}
		}
		return sum;
	}
	int _vscprintf (const char * format, va_list pargs) { 
		int retval; 
		va_list argcopy; 
		va_copy(argcopy, pargs); 
		retval = vsnprintf(NULL, 0, format, argcopy); 
		va_end(argcopy); 
		return retval; 
    }
	std::string format(const char *pszFmt, ...){
		std::string str;
		va_list args;
		va_start(args, pszFmt);
		{
			int nLength = _vscprintf(pszFmt, args);
			nLength += 1;  
			std::vector<char> vectorChars(nLength);
			vsnprintf(vectorChars.data(), nLength, pszFmt, args);
			str.assign(vectorChars.data());
		}
		va_end(args);
		return str;
	}
FILE* fp = fopen("./output/task1.txt", "w");
%}

IDN    [a-zA-Z][a-zA-Z0-9]*|[a-zA-Z][a-zA-Z0-9]*[._][a-zA-Z0-9]+
REAL16 0x[0-9a-f]+[.][0-9a-f]+
REAL10 (0|[1-9][0-9]*)[.][0-9]+
REAL8  0[0-7]+[.][0-7]+ 
INT16  0x[0-9a-f][0-9a-f]*
INT10  0|[1-9][0-9]* 
INT8   0[1-7][0-7]* 
NextLine \n
Space [ \t\r]
OtherCharacter .
%%

"if"     {tokens->push_back("if\t\t\t_\n\n");   return yy::parser::token::IF;}
"while"  {tokens->push_back("while\t\t_\n\n");  return yy::parser::token::WHILE;}
"else"   {tokens->push_back("else\t\t_\n\n");   return yy::parser::token::ELSE;}
"return" {tokens->push_back("return\t\t_\n\n"); return yy::parser::token::RETURN;}
"int"    {tokens->push_back("int\t\t\t_\n\n");  return yy::parser::token::TYPE_INT;}
"float"  {tokens->push_back("float\t\t_\n\n");  return yy::parser::token::TYPE_FLOAT;}
"void"   {tokens->push_back("void\t\t\t_\n\n"); return yy::parser::token::TYPE_VOID;}
"+"      {tokens->push_back("+\t\t\t_\n\n");    return yy::parser::token::ADD;}
"-"      {tokens->push_back("-\t\t\t_\n\n");    return yy::parser::token::SUB;}
"*"      {tokens->push_back("*\t\t\t_\n\n");    return yy::parser::token::MUL;}
"/"      {tokens->push_back("/\t\t\t_\n\n");    return yy::parser::token::DIV;}
">"      {tokens->push_back(">\t\t\t_\n\n");    return yy::parser::token::GT;}
"<"      {tokens->push_back("<\t\t\t_\n\n");    return yy::parser::token::LT;}
";"      {tokens->push_back(";\t\t\t_\n\n");    return yy::parser::token::SEMICOLON;}
"="      {tokens->push_back("=\t\t\t_\n\n");    return yy::parser::token::ASSIGN;}
"<="     {tokens->push_back("<=\t\t\t_\n\n");   return yy::parser::token::LET;}
">="     {tokens->push_back(">=\t\t\t_\n\n");   return yy::parser::token::GET;}
"=="     {tokens->push_back("==\t\t\t_\n\n");   return yy::parser::token::EQ;}
"!="     {tokens->push_back("!=\t\t\t_\n\n");   return yy::parser::token::NEQ;}
"("      {tokens->push_back("(\t\t\t_\n\n");    return yy::parser::token::LP;}
")"      {tokens->push_back(")\t\t\t_\n\n");    return yy::parser::token::RP;}
"["      {tokens->push_back("[\t\t\t_\n\n");    return yy::parser::token::MLP;}
"]"      {tokens->push_back("]\t\t\t_\n\n");    return yy::parser::token::MRP;}
"{"      {tokens->push_back("{\t\t\t_\n\n");    return yy::parser::token::LLP;}
"}"      {tokens->push_back("}\t\t\t_\n\n");    return yy::parser::token::LRP;}
","      {tokens->push_back(",\t\t\t_\n\n");    return yy::parser::token::COMMA;}
"&&"     {return yy::parser::token::AND;}
"||"     {return yy::parser::token::OR;}
"!"      {return yy::parser::token::NOT;}


{IDN}   {
			tokens->push_back(format("IDN\t\t\t%s\n\n", yytext));
			yylval->id = new Identifier(yytext);
			return yy::parser::token::ID;
	    }
  

{INT16} {
			tokens->push_back(format("INT16\t\t%d\n\n", (int)_hex2dec(yytext)));
			yylval->int10 = new Int10(_hex2dec(yytext)); 
			return yy::parser::token::INT10;
		}

{INT10} {
			tokens->push_back(format("INT10\t\t%d\n\n", atoi(yytext)));
			yylval->int10 = new Int10(atoi(yytext));
			return yy::parser::token::INT10;
		}

{INT8}  {
			tokens->push_back(format("INT8\t\t%d\n\n", (int)_oct2dec(yytext)));
			yylval->int10 = new Int10(_oct2dec(yytext));
			return yy::parser::token::INT10;
		}

{REAL10} {
			tokens->push_back(format("REAL10\t\t%f\n\n", atof(yytext)));
			yylval->real10 = new Real10(atof(yytext));
			return yy::parser::token::REAL10;
		 }

{REAL8} {
			tokens->push_back(format("REAL8\t\t%f\n\n", _oct2dec(yytext)));
			yylval->real10 = new Real10(_oct2dec(yytext)); 
			return yy::parser::token::REAL10;
		}

{REAL16} {
			tokens->push_back(format("REAL16\t\t%f\n\n", _hex2dec(yytext)));
			yylval->real10 = new Real10(_hex2dec(yytext)); 
			return yy::parser::token::REAL10;
        }

{NextLine}       { yylloc->lines(1);}
{Space}          { yylloc->step();}
{OtherCharacter} {printf("Invalid token %s\n\n", yytext);}
%%
