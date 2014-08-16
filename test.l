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

%%

{digit}+    {
                yylval = (float)atoi( yytext );
				return NUM;
            }
{alpha}+    {return WORD;}
"+"	        {return PLUS;}
"-"         {return MINUS;}
"*"	        {return MULTIPLY;}
"/"	        {return DIVIDE;}
"^"	        {return POW;}
"\n"        {return LINEBREAK;}
%%


int
main (void)
{
    printf("Return Code %d\n", yyparse());
}