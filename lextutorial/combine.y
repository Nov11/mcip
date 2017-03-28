%{
#include <stdio.h>
typedef char* string;
#define YYSTYPE char*
int yylex();
void yyerror(char*);
%}
%token NAME EQ AGE
%%
file : record file| record;
record : NAME EQ AGE {printf("%s is %s years old!!!\n", $1, $3); };
%%