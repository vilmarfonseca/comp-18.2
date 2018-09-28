#include <stdio.h>

//CONSTANTS




//NODE

typedef struct ast_node{
	int type;
	HASH_NODE *symbols_pointer;
	ast_node *sons[4];
} AST_NODE;


AST_NODE *initAst(int type, HASH_NODE *symbols_pointer, AST_NODE *son0, AST_NODE *son1, AST_NODE *son2, AST_NODE *son3);
void printAstNode(AST_NODE *node);
void printAst(AST_NODE *node);