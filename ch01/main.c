//#include <iostream>
#include <stdio.h>
#include <string.h>
#include "prog1.h"
#include "maxargs.h"
#include "interp.h"
//using namespace std;
#include "ex1.h"

int main() {
	A_stm stm = prog();
	printf("maxargs:%d\n", maxargs(stm));

	printf("\ninterp stm\n");
	interp(stm);

	printf("\nex:\n");
	char list[] = { "zxcl;kjieaekmfsl" };
	T_tree test = testCase(list, strlen(list));
	for (size_t i = 0; i < strlen(list); i++) {
		assert(member(list[i], test) == TRUE);
	}
	void* lookupret = lookupTree('c', test);
	assert((char)lookupret == 'c');
	printf("test passed\n");
	return 0;
}