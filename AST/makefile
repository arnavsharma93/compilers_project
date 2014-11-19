
CCC = g++
CCFLAGS= -O2
LEX = flex
LFLAGS= -8     
YACC= bison 
YFLAGS= -d -t -y

RM = /bin/rm -f

Parser: AST.o y.tab.o lex.yy.o 
	${CCC} ${CCFLAGS} lex.yy.o y.tab.o AST.o -o Parser -ll

AST.o: AST.cpp AST.h
	clang++ -c -O3 AST.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core`

y.tab.o: grammar.y
	${YACC} ${YFLAGS} grammar.y
	${CCC} ${CCFLAGS} y.tab.c -c `llvm-config --cxxflags --ldflags --system-libs --libs core`

lex.yy.o: lex.l
	${LEX} $(LFLAGS) lex.l
	${CCC} ${CCFLAGS} lex.yy.c -c `llvm-config --cxxflags --ldflags --system-libs --libs core`

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o Parser
