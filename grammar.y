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
%token CONTINUE
%token PLUSEQUAL
%token MINUSEQUAL
%token BOOL_LITERAL
%token LESSEQUAL
%token GTEQUAL
%token EQEQUAL
%token NOTEQUAL
%token COND_AND
%token COND_OR
%token CHAR_LITERAL
%token STRING_LITERAL
%token CALLOUT

%nonassoc "empty"
%nonassoc TYPE

%left COND_OR
%left COND_AND
%left EQEQUAL NOTEQUAL
%left '<' LESSEQUAL GTEQUAL '>'
%left '+' '-'
%left '*' '/' '%'
%nonassoc "not"
%nonassoc "negate"
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
         | CONTINUE ';'
         | block

location: ID
        | ID '[' expr ']'        /* TODO : Add expr here */

assign_op: '='
         | PLUSEQUAL
         | MINUSEQUAL

expr: location
    | method_call
    | literal
    | '(' expr ')'
    | '!' expr %prec "not"
    | '-' expr %prec "negate"
    | expr '*' expr | expr '/' expr | expr '%' expr 
    | expr '+' expr | expr '-' expr
    | expr '<' expr | expr LESSEQUAL expr | expr GTEQUAL expr | expr '>' expr
    | expr EQEQUAL expr | expr NOTEQUAL expr
    | expr COND_AND expr | expr COND_OR expr

comma_expr: /* empty string */ 
          | ',' expr comma_expr

method_call: ID '(' ')'
          | ID '(' expr comma_expr ')'
          | CALLOUT '(' STRING_LITERAL ')'
          | CALLOUT '(' STRING_LITERAL ',' callout_arg comma_callout_arg ')'

callout_arg: expr | STRING_LITERAL;

comma_callout_arg: /* empty string */ 
                 | ',' callout_arg comma_callout_arg
                 ;

literal: INT_LITERAL
       | CHAR_LITERAL
       | BOOL_LITERAL


/*
bin_op: arith_op | rel_op | eq_op | cond_op;
arith_op: '+' | '-' | '*' | '/' | '%';
rel_op: '<' | '>' | LESSEQUAL | GTEQUAL;
eq_op: NOTEQUAL | EQEQUAL;
cond_op: COND_OP;
*/

field_decl_star: /* empty string */ %prec "empty"
               | field_decl_star field_decl

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

