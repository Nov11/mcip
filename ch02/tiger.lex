%{
#include <string.h>
#include "util.h"
#include "tokens.h"
#include "errormsg.h"

int charPos=1;

int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

%}

char [a-zA-Z]
num [0-9]
blank [ \t\n]
allprintable [`~!@#$%^&*()_+\-={}|\[\]\\:";'<>?,./"]
printableInDoubleQoute [`~!@#$%^&*()_+\-={}|\[\]:;'<>?,./]
 //what is \^a ? what is \f___f\ ?
allow ("\\n"|"\\t"|\\^[a-z]|\\[0-9]{3}|\\\"|\\\\|\\f___f\\)

str1 \"({allow}|{blank}|{printableInDoubleQoute}|{char}|{num})*\"
%%
"while" {adjust();return WHILE;}
"for" {adjust();return FOR;}
"to" {adjust();return TO;}
"break" {adjust();return BREAK;}
"let" {adjust();return LET;}
"in" {adjust();return IN;}
"end" {adjust();return END;}
"function" {adjust();return FUNCTION;}
"var" {adjust();return VAR;}
"type" {adjust();return TYPE;}
"array" {adjust();return ARRAY;}
"if" {adjust();return IF;}
"then" {adjust();return THEN;}
"else" {adjust();return ELSE;}
"do" {adjust();return DO;}
"of" {adjust();return OF;}
"nil" {adjust();return NIL;}


[ \t] {adjust(); continue;}
\n	 {adjust(); EM_newline(); continue;}
","	 {adjust(); return COMMA;}
":" {adjust(); return COLON;}
";" {adjust(); return SEMICOLON;}
"(" {adjust(); return LPAREN;}
")" {adjust(); return RPAREN;}
"[" {adjust(); return LBRACK;}
"]" {adjust(); return RBRACK;}
"{" {adjust(); return LBRACE;}
"}" {adjust(); return RBRACE;}
"." {adjust(); return DOT;}
"+" {adjust(); return PLUS;}
"-" {adjust(); return MINUS;}
"*" {adjust(); return TIMES;}
"/" {adjust(); return DIVIDE;}
"=" {adjust(); return EQ;}
"<" {adjust(); return LT;}
">" {adjust(); return GT;}
"<>" {adjust(); return NEQ;}
"<=" {adjust(); return LE;}
">=" {adjust(); return GE;}
"&" {adjust(); return AND;}
"|" {adjust(); return OR;}
":=" {adjust(); return ASSIGN;}
([1-9][0-9]*|0)	 {adjust(); yylval.ival=atoi(yytext); return INT;}
[a-zA-Z][_a-zA-Z0-9]*	{adjust();yylval.sval=String(yytext);return ID;}
{str1}  {adjust();yylval.sval = StringTrimDoubleQoute(yytext); return STRING;}

"/*"  {adjust();comment();}
.	 {adjust(); EM_error(EM_tokPos,"illegal token");}
%%

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