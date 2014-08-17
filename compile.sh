bison -d --verbose --debug grammar.y
flex lex.l
gcc -g -c grammar.tab.c -o grammar.tab.o
gcc -g -c lex.yy.c -o lex.yy.o
gcc -g -o Parser lex.yy.o grammar.tab.o -ll
