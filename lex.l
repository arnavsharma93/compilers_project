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
char_literal (\'){char}(\')
string_literal (\"){char}*(\")
char [^(\\)(\")(\')]|(\\)(\')|(\\)(\")|(\\)(\\)|\\[nt]

%%

\/\/.*$  {}
"class"     {return CLASS;}
"Program"   {return PROGRAM;}
"void"      {return VOID;}
"if"        {return IF;}
"else"      {return ELSE;}
"for"       {return FOR;}
"return"    {return RETURN;}
"break"     {return BREAK;}
"continue"  {return CONTINUE;}
"callout"   {return CALLOUT;}
"int"|"boolean" {return TYPE;}
"true"|"false"  {return BOOL_LITERAL;}
"+="        {return PLUSEQUAL;}
"-="        {return MINUSEQUAL;}
"<="        {return LESSEQUAL;}
">="        {return GTEQUAL;}
"=="        {return EQEQUAL;}
"!="        {return NOTEQUAL;}
"&&"        {return COND_AND;}
"||"        {return COND_OR;}
{alpha}{alpha_num}*  {return ID;}
{int_literal} {return INT_LITERAL;}
{char_literal} {return CHAR_LITERAL;}
{string_literal} {return STRING_LITERAL;}

{delim}+    {}
. { return *yytext; }

%%


int
main (void)
{
    printf("Return Code %d\n", yyparse());
}