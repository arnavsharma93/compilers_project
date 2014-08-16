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
alpha	[a-zA-Z]
delim   [ \t\n]

%%
"class"     {return CLASS;}
"Program"   {return PROGRAM;}
"void"      {return VOID;}
"int"|"boolean" {return TYPE;}
"{"         {return OPENBLOCK;}
"}"         {return CLOSEBLOCK;}

{delim}+    {}

{digit}+    {
                yylval = (float)atoi( yytext );
				return NUM;
            }

%%


int
main (void)
{
    printf("Return Code %d\n", yyparse());
}