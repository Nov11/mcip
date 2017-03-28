#include "combine.tab.h"
#include<stdio.h>
int main()
{
	yyparse();
	return 0;
}
void yyerror(char *msg)
{
	printf("Error encountered: %s \n", msg);
}