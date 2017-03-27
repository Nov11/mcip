//#include <iostream>
#include <stdio.h>
#include "prog1.h"
//using namespace std;
int maxargsExp(A_exp exp) {
	if (exp == NULL) { return 0; }
	switch (exp->kind)
	{
	case A_idExp:
	case A_numExp:
	case A_opExp:
		return 0;
	case A_eseqExp:
		return maxargsImpl(exp->u.eseq.stm);
	}
}
int maxargsExpList(A_expList expl) {
	if (expl == NULL) { return 0; }
	switch (expl->kind)
	{
	case A_pairExpList:
	{
		A_expList t = expl->u.pair.tail;
		return 1 + maxargsExpList(t);
	}
	case A_lastExpList:
		return 1;
	}
}

int maxargsImpl(A_stm stm) {
	if (stm == NULL) { return 0; }
	switch (stm->kind) {
	case A_assignStm:
	{
		//may occur in exp
		return maxargsExp(stm->u.assign.exp);
	}
	case A_compoundStm:
	{
		//return the larger one
		int fst = maxargsImpl(stm->u.compound.stm1);
		int snd = maxargsImpl(stm->u.compound.stm2);
		return fst > snd ? fst : snd;
	}
	case A_printStm:
	{
		//check direct exp only print((a,b), a) --> 2 params
		int tmp = maxargsExpList(stm->u.print.exps);
		return tmp;
		//max = max < tmp ? tmp : max;
	}
	}
	//return max;
}

int maxargs(A_stm stm) {
	return maxargsImpl(stm);
}

int main() {
	A_stm stm = prog();
	printf("maxargs:%d\n", maxargs(stm));
	return 0;
}