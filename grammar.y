%{
	#define YYSTYPE float
	#include<stdio.h>
	#include<math.h>
    int yydebug=1;
%}

%token ID
%token CLASS
%token PROGRAM
%token VOID
%token TYPE

%nonassoc "empty"
%nonassoc TYPE
%%

program: CLASS PROGRAM '{' field_decl_star method_decl_star '}' {printf("In program rule\n");}

method_decl_star: /*empty string */
                | method_decl method_decl_star

method_decl: VOID ID '(' ')'
           | VOID ID '(' TYPE ID comma_type_id ')'
           | TYPE ID '(' TYPE ID comma_type_id ')'
           | TYPE ID '(' ')'
           ;

comma_type_id: /* empty string */
             | ',' TYPE ID comma_type_id


field_decl_star: /* empty string */ %prec "empty"
               | field_decl field_decl_star

field_decl: TYPE ID comma_id ';';

comma_id: /* empty string */ 
        | ',' ID comma_id



%%

