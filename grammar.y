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
%token COMMA
%token ID
%%

program: CLASS PROGRAM OPENBLOCK field_decl_star CLOSEBLOCK {printf("In program rule\n");}

field_decl_star: /*empty string*/
				| field_decl_star  field_decl
				;

id_plus_comma: ID | id_plus_comma COMMA ID

field_decl: TYPE id_plus_comma SEMICOLON
;
%%

