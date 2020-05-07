target: lex.l bison.yxx ast.h visitor.h visitor.cpp driver.cpp codegen.cpp
	bison bison.yxx -d -v --debug
	flex -d lex.l
	g++ -o $@ bison.tab.cxx lex.yy.c ast.cpp codegen.cpp visitor.cpp driver.cpp -g

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

