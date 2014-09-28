
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
	${CCC} -c AST.cpp

y.tab.o: grammar.y
	${YACC} ${YFLAGS} grammar.y
	${CCC} ${CCFLAGS} y.tab.c -c 

lex.yy.o: lex.l
	${LEX} $(LFLAGS) lex.l
	${CCC} ${CCFLAGS} lex.yy.c -c 

clean:
	/bin/rm -f lex.yy.* y.tab.* *.o Parser
