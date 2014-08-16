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
%token IF
%token ELSE
%token INT_LITERAL
%token FOR
%token RETURN
%token BREAK

%nonassoc "empty"
%nonassoc TYPE
%%

/* COMPLETED */
program: CLASS PROGRAM '{' field_decl_star method_decl_star '}' {printf("In program rule\n");}

method_decl_star: /*empty string */
                | method_decl method_decl_star

/* COMPLETED */
method_decl: VOID ID '(' ')' block
           | VOID ID '(' TYPE ID comma_type_id ')' block
           | TYPE ID '(' TYPE ID comma_type_id ')' block
           | TYPE ID '(' ')' block
           ;

comma_type_id: /* empty string */
             | ',' TYPE ID comma_type_id

/* COMPLETED */
block: '{' var_decl_star statement_star '}'

var_decl_star: /* empty string */
             | var_decl var_decl_star

/* COMPLETED */
var_decl: TYPE ID comma_id ';'

statement_star: /* empty string */
              | statement statement_star

statement: location assign_op expr ';'
         | method_call ';'
         | IF '(' expr ')' block
         | IF '(' expr ')' block ELSE block
         | FOR ID '=' expr ',' expr block       /* TODO : Test this */
         | RETURN ';'
         | RETURN expr ';'
         | BREAK ';'

location: ID
        | ID '[' expr ']'        /* TODO : Add expr here */

assign_op: '='              /* TODO : Add -= and += */

expr: location
    | method_call 

comma_expr: /* empty string */ 
          | ',' expr comma_expr

method_call: ID '(' ')'
           | ID '(' expr comma_expr ')'

field_decl_star: /* empty string */ %prec "empty"
               | field_decl field_decl_star

field_decl: TYPE simple_or_array comma_simple_or_array';';

simple_or_array: ID
               | ID '[' INT_LITERAL ']'
               ;

comma_simple_or_array: /* empty string */ 
                     | ',' simple_or_array comma_simple_or_array
                     ;

comma_id: /* empty string */ 
        | ',' ID comma_id



%%

