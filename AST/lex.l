%{
#include "AST.h"
#include "y.tab.h"

#include <stdio.h>
extern int line_num;

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
"void"      {yylval.type = strdup(yytext);return VOID;}
"if"        {return IF;}
"else"      {return ELSE;}
"for"       {return FOR;}
"return"    {return RETURN;}
"break"     {return BREAK;}
"continue"  {return CONTINUE;}
"callout"   {return CALLOUT;}
"int"|"boolean" {yylval.type = strdup(yytext);return TYPE;}
"true"		{return BOOL_LITERAL;}
"false"  	{return BOOL_LITERAL;}
"+="        {return PLUSEQUAL;}
"-="        {return MINUSEQUAL;}
"<="        {return LESSEQUAL;}
">="        {return GTEQUAL;}
"=="        {return EQEQUAL;}
"!="        {return NOTEQUAL;}
"&&"        {return COND_AND;}
"||"        {return COND_OR;}
{alpha}{alpha_num}*  {yylval.id = strdup(yytext);return ID;}
{hex_literal}	{
					yylval.int_literal = (int)strtol(yytext, NULL, 16);
					return INT_LITERAL;
				}
{decimal_literal} 	{
						yylval.int_literal = (int)strtol(yytext, NULL, 10);
						return INT_LITERAL;
					}
{char_literal}  {
					yylval.char_literal = strdup(yytext);
					return CHAR_LITERAL;
				}
{string_literal} {
					yylval.string_literal = strdup(yytext);
					return STRING_LITERAL;
				 }

{delim}+    {}
. { return *yytext; }

%%