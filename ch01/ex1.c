#include "ex1.h"

T_tree Tree(T_tree left, KEY value, void* binding, T_tree right)
{
	T_tree ptr = checked_malloc(sizeof(*ptr));
	ptr->left = left;
	ptr->key = value;
	ptr->right = right;
	ptr->binding = binding;
	return ptr;
}

T_tree insert(KEY value, void* binding, T_tree tree)
{
	if (tree == NULL) { return Tree(NULL, value, binding, NULL); }
	if (value == tree->key) { return Tree(tree->left, value, binding, tree->right); }
	else if (value < tree->key) { return Tree(insert(value, binding, tree->left), tree->key, tree->binding, tree->right); }
	else if (value > tree->key) { return Tree(tree->left, tree->key, tree->binding, insert(value, binding, tree->right)); }
	return NULL;
}

bool member(KEY value, T_tree tree)
{
	if (tree == NULL) { return FALSE; }
	if (tree->key == value) {return TRUE;}
	else if (tree->key > value) { return member(value, tree->left); }
	else if (tree->key < value) { return member(value, tree->right); }
	return FALSE;
}

void* lookupTree(KEY value, T_tree tree)
{
	if (tree == NULL) { return NULL; }
	if (tree->key == value) { return tree->binding; }
	else if (tree->key > value) { return lookupTree(value, tree->left); }
	else if (tree->key < value) { return lookupTree(value, tree->right); }
	return NULL;
}

T_tree testCase(char list[], int len) {
	T_tree ret = NULL;
	for (int i = 0; i < len; i++) {
		ret = insert(list[i], (void*)list[i], ret);
	}
	return ret;
}