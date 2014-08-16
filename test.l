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

%%
"class"     {return CLASS;}
"Program"   {return PROGRAM;}
"void"      {return VOID;}

"int"|"boolean" {return TYPE;}
{alpha}{alpha_num}*  {return ID;}

{delim}+    {}

. { return *yytext; }

%%


int
main (void)
{
    printf("Return Code %d\n", yyparse());
}