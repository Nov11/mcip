#ifndef errormsg_HEADER
#define errormsg_HEADER

#include "util.h"

extern bool EM_anyErrors;

void EM_newline(void);

extern int EM_tokPos;
extern FILE* yyin;
void EM_error(int, string,...);
void EM_impossible(string,...);
void EM_reset(string filename);
#endif // !errormsg_HEADER


