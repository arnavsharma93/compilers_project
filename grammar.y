%{
	#define YYSTYPE float
	#include<stdio.h>
	#include<math.h>
	
%}

%token NUM
%token PLUS
%token MINUS
%token MULTIPLY
%token DIVIDE
%token POW
%token LINEBREAK

%%

input: /* empty */
| input line
;
line: LINEBREAK
| exp LINEBREAK { printf ("LINE RULE \t%.10g\n", $1); }
;
exp: NUM { $$ = $1; }
| exp exp PLUS { $$ = $1 + $2;}
| exp exp MINUS { $$ = $1 - $2; }
| exp exp MULTIPLY { $$ = $1 * $2; }
| exp exp DIVIDE { $$ = $1 / $2; }
/* Exponentiation */
| exp exp POW { $$ = pow ($1, $2); }
;
%%

