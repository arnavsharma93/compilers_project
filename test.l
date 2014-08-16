%{
#define YYSTYPE float
#include "grammar.tab.h"

#include <stdio.h>
#include <math.h>

void yyerror (char const *s) {
    printf ("Error : %s\n", s);
}

%}

digit	[0-9]
alpha	[a-zA-Z_]
delim   [ \t\n]
alpha_num  {alpha}|{digit}
hex_digit {digit}|[a-fA-F]
decimal_literal {digit}{digit}*
hex_literal 0x{hex_digit}{hex_digit}*
int_literal  {decimal_literal}|{hex_literal}

%%
"class"     {return CLASS;}
"Program"   {return PROGRAM;}
"void"      {return VOID;}
"if"        {return IF;}
"else"      {return ELSE;}
"for"       {return FOR;}
"return"    {return RETURN;}
"break"     {return BREAK;}
"int"|"boolean" {return TYPE;}
{alpha}{alpha_num}*  {return ID;}
{int_literal} {return INT_LITERAL;}

{delim}+    {}

. { return *yytext; }

%%


int
main (void)
{
    printf("Return Code %d\n", yyparse());
}