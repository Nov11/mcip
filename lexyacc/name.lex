%{
#define YYSTYPE char*
#include "name.tab.h"
#include <stdio.h>
#include <string.h>
%}
char [A-Za-z]
num [0-9]
eq [=]
name {char}+
age {num}+
blank [ \t\n]
p [~`!@#$%^&*()_+\-={}\[\]:";'<>,.?/|\\]
printable ({char}|{num}|{p})
%%
{name} { yylval = strdup(yytext);        return NAME; }
{eq} { return EQ; }
{age} { yylval = strdup(yytext);        return AGE; }
\"{printable}\" {ECHO;}
%%
int yywrap()
{
    return 1;
}