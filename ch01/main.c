//#include <iostream>
#include <stdio.h>
#include "prog1.h"
#include "maxargs.h"
//using namespace std;


int main() {
	A_stm stm = prog();
	printf("maxargs:%d\n", maxargs(stm));
	return 0;
}