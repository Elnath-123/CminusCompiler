%option noyywrap nodefault yylineno
%{
#include <stdio.h>
#include <iostream>
using namespace std;
/* Convert number in the format of char to number*/
	int numchar2int(char num){
		if(num >= '0' && num <= '9') return num - '0';	
		else if (num >= 'a' && num <= 'f') return num - 'a' + 10;
	}
	double _oct2dec(string oct){
		double base = 1;
		int dotpos = 0;
		for(int i = 0; i < oct.size(); i++)
			if(oct[i] == '.'){
				dotpos = i;
				break;
			}
		double sum = 0;
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
	double _hex2dec(string hex){
		double base = 1;
		int dotpos = 0;
		for(int i = 0; i < hex.size(); i++)
			if(hex[i] == '.'){
				dotpos = i;
				break;
			}
		double sum = 0;
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

"if" {}
"then" {}
"while" {}
"else" {}
"do" {}
"return" {}
"int" {}
"void" {}
"+" {}
"-" {}
"*" {}
"/" {}
">" {}
"<" {}
";" {}
"=" {}
"<=" {}
">=" {}
"==" {}
"!=" {}
"(" {}
")" {}
"[" {}
"]" {}
"{" {}
"}" {}
"," {}


[a-zA-Z][a-zA-Z0-9]*|[a-zA-Z][a-zA-Z0-9]*[._][a-zA-Z0-9]+ {}

0|[1-9][0-9]* { }
0[1-7][0-7]* { }
0x[0-9a-f][0-9a-f]* { }

(0|[1-9][0-9]*)[.][0-9]+ { }
0[0-7]+[.][0-7]+ {}
0x[0-9a-f]+[.][0-9a-f]+ {}


\n {}
[ \t] {}
. {printf("Invalid character %c\n", *yytext);}
%%

int main(){
    yylex();
}