Compilers Course Project -
	Somay Jain (201101054)
	Arnav Sharma (201125093)

Description :
	A parser for the decaf programming language with the following specifications - http://192.168.36.187/mediawiki/images/c/c2/Decafspec.pdf
	Made using flex and bison.

Compiling Instructions :
	bison -d grammar.y
	flex lex.l
	gcc -g -c grammar.tab.c -o grammar.tab.o
	gcc -g -c lex.yy.c -o lex.yy.o
	gcc -g -o Parser lex.yy.o grammar.tab.o -ll

	Note : Some UNIX systems might require -lfl instead of -ll in the last command.

Running the parser :

	./Parser < input_program

Sample input programs :
	prog1.txt
	prog2.txt
	prog3.txt
	prog4.txt
	prog5.txt
	prog6.txt

The input program is successfully parsed when the "Return Code 0" is printed on running the parser, otherwise "syntax error" is raised.