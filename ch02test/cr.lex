%{
#include <stdio.h>
#include "util.h"
%}


char [a-zA-Z]
num [0-9]
blank [ \t\n]
allprintable [`~!@#$%^&*()_+\-={}|\[\]\\:";'<>?,./"]
printableInDoubleQoute [`~!@#$%^&*()_+\-={}|\[\]:;'<>?,./]
 //what is \^a ? what is \f___f\ ?
allow ("\\n"|"\\t"|\\^[a-z]|\\[0-9]{3}|\\\"|\\\\|\\f___f\\)

str \"({printableInDoubleQoute}|{allow}|{blank}|{char}|{num})*\"
str1 \"({allow}|{blank}|{printableInDoubleQoute}|{char}|{num})*\"
%%

[1-9][0-9]*	 {printf("MATCH int :%d\n", atoi(yytext)); }
{str1} {printf("MATCH STRING: %s len : %d\n", yytext, yyleng);string ret = StringTrimDoubleQoute(yytext);for(int i= 0; i< strlen(ret);i++){printf("|%c %d| ", ret[i], ret[i]);}}
"/*" {printf("start of comment\n");comment();printf("end of comment\n");}
%%
int yywrap(){return 1;}
int main(){yylex();return 0;}

void comment()
{
	int commentBegin = 1;
	do {
		//find first start
		char c1 = input();
		char c0 = 255;
		while (c1 != 0 && c1 != '*') {
			c0 = c1;
			c1 = input();
		}
		if (c1 == 0) {
			printf("comment not terminated\n");
			return;
		}
		//if we encountered nested comment
		if (c0 == '/') {
			commentBegin++;
			continue;
		}
		char lookAhead = input();
		if (lookAhead != '/') {
			continue;
		}
		commentBegin--;
	} while (commentBegin > 0);

}
