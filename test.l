%{
#define YYSTYPE float
#include "grammar.tab.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

void yyerror (char const *s) {
   		printf ("Error : %s\n", s);
 	}
%}

digit	[0-9]

%%

{digit}+	{
				yylval = (float)atoi( yytext );
				printf("yylval %f\n", yylval);
				return NUM;
			}
"+"			{return PLUS;}
"-"			{return MINUS;}
"*"			{return MULTIPLY;}
"/"			{return DIVIDE;}
"^"			{return POW;}
"\n"		{return LINEBREAK;}
%%


int
main (void)
{
	printf("Return Code %d\n", yyparse());
}