/*
* util.c - commonly used utility functions.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
	string p = checked_malloc(len);//this will waste some memory¡£ or we need iterate through 's' again¡£
	string ptr = p;
	string start = &s[1];
	int charLen = len - 1;//1 for terminate NULL

	for (int i = 0; i < charLen; ) {
		char fst = start[i];
		//first back slash
		if (fst != '\\') {
			*ptr++ = fst;
			i++;
		}
		else {
			//c is back slash
			//if this is not the last charactor
			//possible literals are \\n \\t \" \\124 \\
						//which means double qoute or back slash exists after the first back slash
			if (i + 1 < charLen) {
				char snd = start[i + 1];
				if (snd == '\\') {
					//*ptr++ = '\\';
					//i += 2;
					//if (i < len - 1 && isdigit(start[i])) {
					//	//there should be three digits
					//	char* inner = &start[i];
					//	if (i + 2 < len - 1 && isdigit(*inner) && isdigit(*(inner + 1)) && isdigit(*(inner + 2))) {
					//		*ptr++ = (*inner) * 8 * 8 + (*(inner + 1)) * 8 + (*(inner + 2));
					//		i += 3;
					//	}
					//	else {
					//		printf("illegal token.there should be three digits here.");
					//	}
					//}
					if (i + 2 < charLen) {
						char trd = start[i + 2];
						if (trd == 'n') {
							*ptr++ = '\n';
							i += 3;
						}
						else if (trd == 't') {
							*ptr++ = '\t';
							i += 3;
						}
						else {
							//just double back slash
							*ptr++ = '\\';
							i += 2;
						}
					}
					else {
						// double back slash in the end of string
						// that is single slash in the result
						*ptr++ = '\\';
						i += 2;
					}

				}
				else if (snd == '\"') {
					*ptr++ = '\"';
					i += 2;
				}
				else
				{
					printf("what is \\^[a-z] or \\f___f\\ ?\n");
					exit(1);
				}
			}
			else {
				//there should not be any case that single back slash occours in string literal
				printf("singe back slash occurs in string literal\n");
				exit(1);
			}
			// deal with back slash end
		}
	}
	//terminate the string with NULL
	*ptr = 0;
	return p;
}

U_boolList U_BoolList(bool head, U_boolList tail)
{
	U_boolList list = checked_malloc(sizeof(*list));
	list->head = head;
	list->tail = tail;
	return list;
}
