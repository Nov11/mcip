#include <string.h>
#include "interp.h"

Table_ Table(string id, int value, Table_ tail) {
	Table_ t = checked_malloc(sizeof(*t));
	t->id = id;
	t->value = value;
	t->tail = tail;
	return t;
}

Table_ interpStm(A_stm s, Table_ t)
{
	if (s == NULL) { return t; }
	Table_ result = NULL;
	switch (s->kind) {
	case A_assignStm:
	{
		string id = s->u.assign.id;
		IntAndTable_ tmp = interpExp(s->u.assign.exp, t);
		int value = tmp->i;
		result = update(t, id, value);
		break;
	}
	case A_compoundStm:
	{
		Table_ ret = interpStm(s->u.compound.stm1, t);
		ret = interpStm(s->u.compound.stm2, ret);
		result = ret;
		break;
	}
	case A_printStm:
	{
		ValueListAndTable_ ret = interExpList(s->u.print.exps, t);
		//printf("print with exp final value: %d\n", ret->i);
		printf("print with value:\n(");
		int first = 0;
		while (ret != NULL) {
			if (first > 0) { printf(","); }
			else { first++; }
			printf("%d", ret->value);
			ret = ret->next;
		}
		printf(")\n");
		result = t;
	}
	}
	return result;
}

Table_ update(Table_ t, string id, int value)
{
	Table_ ptr = Table(id, value, t);
	return ptr;
}

int lookup(Table_ t, string key)
{
	while (t != NULL) {
		if (strcmp(t->id, key) == 0) {
			return t->value;
		}
		t = t->tail;
	}
	return 0;
}

IntAndTable_ IntAndTable(int i, Table_ t)
{
	IntAndTable_ ret = checked_malloc(sizeof(*ret));
	ret->i = i;
	ret->t = t;
	return ret;
}

IntAndTable_ interpExp(A_exp e, Table_ t)
{
	if (e == NULL) { return NULL; }
	// A_idExp, A_numExp, A_opExp, A_eseqExp
	IntAndTable_ ret = NULL;
	switch (e->kind) {
	case A_idExp:
	{
		int value = lookup(t, e->u.id);
		ret = IntAndTable(value, t);
	}
	break;
	case A_numExp:
	{
		ret = IntAndTable(e->u.num, t);
	}
	break;
	case A_opExp:
	{
		ret = interpExp(e->u.op.left, t);
		int left = ret->i;
		ret = interpExp(e->u.op.right, t);
		int right = ret->i;
		int result = 0;
		//A_plus, A_minus, A_times, A_div
		switch (e->u.op.oper) {
		case A_plus:
			result = left + right;
			break;
		case A_minus:
			result = left - right;
			break;
		case A_times:
			result = left * right;
			break;
		case A_div:
			result = left / right;
			break;
		}
		ret = IntAndTable(result, t);
	}
	break;
	case A_eseqExp:
	{
		t = interpStm(e->u.eseq.stm, t);
		ret = interpExp(e->u.eseq.exp, t);
	}
	break;
	}
	return ret;
}

ValueListAndTable_ ValueListAndTable(int value, ValueListAndTable_ next, Table_ t)
{
	ValueListAndTable_ ret = checked_malloc(sizeof(*ret));
	ret->next = next;
	ret->t = t;
	ret->value = value;
	return ret;
}

ValueListAndTable_ interExpList(A_expList expList, Table_ t)
{
	if (expList == NULL) { return NULL; }
	ValueListAndTable_ result = NULL;
	//A_pairExpList, A_lastExpList 
	switch (expList->kind) {
	case A_pairExpList:
	{
		IntAndTable_ ret = interpExp(expList->u.pair.head, t);
		ValueListAndTable_ next = interExpList(expList->u.pair.tail, t);
		result = ValueListAndTable(ret->i, next, t);
	}
	break;
	case A_lastExpList:
	{
		IntAndTable_ ret = interpExp(expList->u.last, t);
		result = ValueListAndTable(ret->i, NULL, t);
	}
	break;
	}
	return result;
}

void printTable(Table_ t)
{
	printf("\nprint variable table:\n");
	while (t != NULL) {
		printf("|variable: %s value: %d| ", t->id, t->value);
		t = t->tail;
	}
	printf("\n");
}

void interp(A_stm stm) {
	Table_ tablePtr = NULL;
	tablePtr = interpStm(stm, tablePtr);
	printTable(tablePtr);
}
