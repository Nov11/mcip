#pragma once
#include "util.h"
typedef struct tree* T_tree;
//I don't want another typedef, so just use char here instead of 'String'
//alright I'll use KEY
typedef char KEY;
struct tree { T_tree left; KEY key; T_tree right; void* binding; };
T_tree Tree(T_tree left, KEY value, void* binding, T_tree right);
T_tree insert(KEY value, void* binding, T_tree tree);
bool member(KEY value, T_tree tree);
void* lookupTree(KEY value, T_tree tree);
T_tree testCase(char list[], int len);