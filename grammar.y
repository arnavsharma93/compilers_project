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
%token OPENSQ
%token CLOSESQ
%token SEMICOLON
%token ID
%%

program: CLASS PROGRAM OPENBLOCK ID CLOSEBLOCK {printf("In program rule\n");}
;
%%

