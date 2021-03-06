
#ifndef _ASTH_
#define _ASTH_

#include <stdio.h>
#include "hash.h"

//CONSTANTS

#define AST_PROGRAM 1
#define AST_IDENTIFIER 2
#define AST_VARIABLE 3
#define AST_ARRAY_EMPTY 4
#define AST_ARRAY_INIT 5

#define AST_FUNCTION 10
#define AST_ARG_LIST 11
#define AST_ARGUMENT 12

#define AST_CHAR 20
#define AST_INT 21
#define AST_FLOAT 22

#define AST_LIT_ONLY 30
#define AST_LIT_SEQUENCE 31

#define AST_COMMAND 40
#define AST_COMMAND_BLOCK 41
#define AST_COMMAND_SEQUENCE 42

#define AST_IF 50
#define AST_IF_ELSE 51
#define AST_WHILE 52
#define AST_READ 53
#define AST_PRINT 54
#define AST_RETURN 55

#define AST_EXPRESSION_DB_ID 59
#define AST_EXPRESSION_ID 60
#define AST_EXPRESSION_FUNCTION 61
#define AST_EXPRESSION_ARRAY 62
#define AST_EXPRESSION_LIST 63
#define AST_EXPRESSION_DB_EMPTY 64
#define AST_EXPRESSION_DB 65
#define AST_LE 66
#define AST_GE 67
#define AST_EQ 68
#define AST_OR 69
#define AST_AND 70
#define AST_NOT 71
#define AST_LESS 72
#define AST_ADD 73
#define AST_SUB 74
#define AST_MULT 75
#define AST_DIV 76
#define AST_GREATER 77
#define AST_ATTR_SINGLE 78
#define AST_ATTR_ARRAY 79


//NODE

typedef struct ast_node{
	int type;
	HASH_NODE* symbol;
	struct ast_node* sons[4];

	//part 4
	int lineNumber;
	int dataType;
} AST_NODE;

AST_NODE *root;
FILE *output;

AST_NODE* findFuncDeclaration(AST_NODE *funcall_node);
AST_NODE *initAst(int type, int lineNumber, HASH_NODE *symbol, AST_NODE *son0, AST_NODE *son1, AST_NODE *son2, AST_NODE *son3);
void printAstNode(AST_NODE *node, int level);
void printAst(AST_NODE *node, FILE* output);

#endif
