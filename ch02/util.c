/*
* util.c - commonly used utility functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "errormsg.h"
void *checked_malloc(int len)
{
	void *p = malloc(len);
	if (!p) {
		fprintf(stderr, "\nRan out of memory!\n");
		exit(1);
	}
	return p;
}

string String(char *s)
{
	string p = checked_malloc(strlen(s) + 1);
	strcpy(p, s);
	return p;
}

string StringTrimDoubleQoute(char *s)
{
	//extract double qoute in the beginning and in the end
	int len = strlen(s) + 1 - 2;
	string p = checked_malloc(len);
	string ptr = p;
	string start = &s[1];
	for (int i = 0; i < len - 1; ) {
		char c = start[i];
		//first back slash
		if (c == '\\') {
			//if this is not the last charactor
			if (i + 1 < len - 1) {
				char tmp = start[i + 1];
				if (tmp == 'n') {
					*ptr++ = '\n';
					i += 2;
				}
				else if (tmp == 't') {
					*ptr++ = '\t';
					i += 2;
				}
				else if (tmp == '\\') {
					*ptr++ = '\\';
					i += 2;
					if (i < len - 1 && isdigit(start[i])) {
						//there should be three digits
						char* inner = &start[i];
						if (i + 2 < len - 1 && isdigit(*inner) && isdigit(*(inner + 1)) && isdigit(*(inner + 2))) {
							*ptr++ = (*inner) * 8 * 8 + (*(inner + 1)) * 8 + (*(inner + 2));
							i += 3;
						}
						else {
							EM_error(EM_tokPos, "illegal token.there should be three digits here.");
						}
					}
				}
				else if (tmp == '\"') {
					*ptr++ = '\"';
					i += 2;
				}
				else
				{
					printf("what is \\^[a-z] or \\f___f\\ ?\n");
				}
			}
			// deal with back slash end
		}
		else {
			*ptr++ = start[i];
			i++;
		}
	}
	*ptr = NULL;
	return p;
}

U_boolList U_BoolList(bool head, U_boolList tail)
{
	U_boolList list = checked_malloc(sizeof(*list));
	list->head = head;
	list->tail = tail;
	return list;
}

void comment()
{
	int commentBegin = 1;
	do {
		//find first start
		char c1 = fgetc(yyin);
		char c0 = 255;
		while (c1 != EOF && c1 != "*") {
			c0 = c1;
			c1 = fgetc(yyin);
		}
		if (c1 == EOF) {
			EM_error(EM_tokPos, "comment not terminated");
			return;
		}
		//if we encountered nested comment
		if (c0 == '/') {
			commentBegin++;
			continue;
		}
		char lookAhead = fgetc(yyin);
		if (lookAhead != '/') {
			continue;
		}
		commentBegin--;
	} while (commentBegin > 0);

}
