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
%token OPENROUND
%token CLOSEROUND
%token SEMICOLON
%token COMMA
%token ID

%%

program: CLASS PROGRAM OPENBLOCK field_decl_star method_decl_star CLOSEBLOCK {printf("In program rule\n");}

field_decl_star: /*empty string*/
		| field_decl_star  field_decl
		;
field_decl: TYPE id_plus_comma SEMICOLON;

method_decl_star: /*empty string*/
                | method_decl_star  method_decl
                ;

method_decl: TYPE ID OPENROUND CLOSEROUND
                    | TYPE ID OPENROUND type_id_plus_comma CLOSEROUND
                    | VOID ID OPENROUND CLOSEROUND
                    | VOID ID OPENROUND type_id_plus_comma CLOSEROUND
                    ;
type_id_plus_comma: TYPE ID | type_id_plus_comma COMMA TYPE ID;

id_plus_comma: ID | id_plus_comma COMMA ID;


%%

