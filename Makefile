
target: lex.l bison.y header/ast.h header/visitor.h \
		src/visitor.cpp driver.cpp src/codegen.cpp src/symbol.cpp
	flex -d lex.l
	bison bison.y -d -v --debug
	g++ -std=c++11 -o $@ bison.tab.cc lex.yy.c \
						 src/ast.cpp src/codegen.cpp \
						 src/visitor.cpp driver.cpp src/symbol.cpp \
						 -g

flex: lex.l
	flex lex.l
	g++ -o $@ lex.yy.c	

.PYHONY: clean
clean:
	rm bison.tab.cc \
	bison.tab.hh \
	lex.yy.c \
	location.hh \
	position.hh \
	stack.hh \
	target

