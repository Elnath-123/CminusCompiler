
target: lex.l bison.yxx header/ast.h header/visitor.h \
		src/visitor.cpp driver.cpp src/codegen.cpp src/symbol.cpp
	flex lex.l
	bison bison.yxx -d -v --debug
	g++ -std=c++11 -o $@ bison.tab.cxx lex.yy.c \
						 src/ast.cpp src/codegen.cpp \
						 src/visitor.cpp driver.cpp src/symbol.cpp \
						 -g

flex: lex.l
	flex lex.l
	g++ -o $@ lex.yy.c	

.PYHONY: clean
clean:
	rm bison.tab.cxx \
	bison.tab.hxx \
	lex.yy.c \
	location.hh \
	position.hh \
	stack.hh \
	target

