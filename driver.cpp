/*
 * @name driver.cpp
 * @description A driver for parse program
 * @date 03/31/2020
 * @author Lrq
 */

#include <iostream>
#include <unistd.h>
#include <string>
#include "bison.tab.hh"
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
void usage();
void dump_to_file(vector<string>*, vector<string>);
extern FILE* yyin;
using namespace std;

int main(int argc, char** argv)
{	
    /* Get command from shell */
	int lexical_output = 0;
	int syntax_output = 0;
	char opt;

	while((opt = getopt(argc, argv, "hls")) != -1){
		switch (opt){
			case 'h':
				usage();
			break;
			case 'l':
				lexical_output = 1;
			break;
			case 's':
				syntax_output = 1;
			break;
		default:
				usage();
		}
	}
	
	/* No argument */
	if(!lexical_output && !syntax_output) 
		printf("No output in command line, please check out output files!\n");
	
	/* Parse */
	vector<string>* grammar;
	vector<string> tokens;
	if(argc > 1)
		if(!(yyin = fopen(argv[argc - 1], "r"))){
			for(int i = 0; i < argc; i++){
				printf("%s\n", argv[i]);
			}
			std::cerr << "Read file error." << std::endl;
			return -1;
		}

	yy::parser parser(&grammar, &tokens);
	parser.parse();
	dump_to_file(grammar, tokens);

	if(lexical_output)
		for(string str : tokens)
			cout << str;
		
	if(syntax_output)
		for(string str : *grammar)
			cout << str;

	return 0;
}

void dump_to_file(vector<string> *grammar, vector<string> tokens){
	fstream f;
	f.open("./output/task1.txt", ios::out);
	for(string str : tokens){
		f << str;
	}
	f.close();
	
	f.open("./output/task2.txt", ios::out);
	for(string str : *grammar){
		f << str;
	}
	f.close();
}

void usage(){
	printf("Usage: target [-hls]\n");
	printf("   -h   print this message\n");
	printf("   -l   print lexical analysis result\n");
	printf("   -s   print syntax analysis result\n");
	exit(1);
}

