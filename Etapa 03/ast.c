#include <stdio.h>
#include "ast.h"
#include "hash.h"

AST_NODE *initAst(int type, HASH_NODE *symbols_pointer, AST_NODE *son0, AST_NODE *son1, AST_NODE *son2, AST_NODE *son3)
{
	AST_NODE *new_node;

	new_node->type = type;
	new_node->symbols_pointer = symbols_pointer;
	new_node->sons[0] = son0;
	new_node->sons[1] = son0;
	new_node->sons[2] = son0;
	new_node->sons[3] = son0;

	return new_node;
}