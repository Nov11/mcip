#pragma once
#include <stdio.h>
#include "prog1.h"

//these are mentioned in the book.

void interp(A_stm stm);

//interp stm
typedef struct table* Table_;
struct table { string id; int value; Table_ tail; };
Table_ Table(string id, int value, Table_ tail);
Table_ interpStm(A_stm s, Table_ t);

Table_ update(Table_ t, string id, int value);
int lookup(Table_ t, string key);

//interp exp
typedef struct intAndTable* IntAndTable_;
struct intAndTable { int i; Table_ t; };
IntAndTable_ IntAndTable(int i, Table_ t);
IntAndTable_ interpExp(A_exp e, Table_ t);

//interp explist
typedef struct valueListAndTable* ValueListAndTable_;
struct valueListAndTable { int value; ValueListAndTable_ next; Table_ t; };
ValueListAndTable_ ValueListAndTable(int value, ValueListAndTable_ next, Table_ t);
ValueListAndTable_ interExpList(A_expList expList, Table_ t);
//utilies
void printTable(Table_ t);