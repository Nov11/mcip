%{
#define YYSTYPE char*
#include "combine.tab.h"
#include <stdio.h>
#include <string.h>
%}

char [A-Za-z]
num [0-9]
eq [=]
name {char}+
age {num}+
%%

{name} { yylval = strdup(yytext);return NAME; }
{eq} { return EQ; }
{age} { yylval = strdup(yytext);return AGE; }
%%

int yywrap()
{
return 1;
}
