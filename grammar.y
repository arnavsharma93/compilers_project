%{
	#define YYSTYPE float
	#include<stdio.h>
	#include<math.h>
%}

%token CLASS
%token PROGRAM
%token VOID
%token TYPE
%token OPENBLOCK
%token CLOSEBLOCK
%token WHITESPACE

%token NUM
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token POW
%token LINEBREAK
%token WORD

%%

program: CLASS PROGRAM OPENBLOCK CLOSEBLOCK {printf("In program rule\n");}
;

%%

