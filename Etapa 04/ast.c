#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "hash.h"

AST_NODE *initAst(int type, int line, HASH_NODE *symbol, AST_NODE *son0, AST_NODE *son1, AST_NODE *son2, AST_NODE *son3)
{
	AST_NODE *new_node;

	if(!(new_node = (AST_NODE*) calloc(1, sizeof(AST_NODE)))){
		fprintf(stderr, "Couldn't allocate memory\n");
		exit(1);
	}

    newNode->dataType = DATATYPE_NOT_DEFINED;
    newNode->line = line;
	new_node->type = type;
	new_node->symbol = symbol;
	new_node->sons[0] = son0;
	new_node->sons[1] = son1;
	new_node->sons[2] = son2;
	new_node->sons[3] = son3;



	return new_node;
}

void printAstNode(AST_NODE *node){
	if(node){
		fprintf(stderr, "%d %s\n", node->type, node->symbol->text);
		if(node->sons[0])
			printAstNode(node->sons[0]);
		if(node->sons[1])
			printAstNode(node->sons[1]);
		if(node->sons[2])
			printAstNode(node->sons[2]);
		if(node->sons[3])
			printAstNode(node->sons[3]);
	}
}

void printAst(AST_NODE *node, FILE* file)
{
	if(node){
		switch(node->type)
		{
			//PROGRAM
			case AST_PROGRAM:
				printAst(node->sons[0], file);
				if(node->sons[1])
					printAst(node->sons[1], file);
				break;

			//IDENTIFIER
			case AST_IDENTIFIER:
				fprintf(file, "%s", node->symbol->text);
				break;

			//TYPES
			case AST_CHAR:
				fprintf(file, "char ");
				break;

			case AST_INT:
				fprintf(file, "int ");
				break;

			case AST_FLOAT:
				fprintf(file, "float ");
				break;

			//READ, PRINT, RETURN
			case AST_READ:
				fprintf(file, "read ");
				if(node->symbol)
					fprintf(file, "%s", node->symbol->text);
				break;

			case AST_PRINT:
				fprintf(file, "print ");
				printAst(node->sons[0], file);
				break;

			case AST_RETURN:
				fprintf(file, "return ");
				printAst(node->sons[0], file);
				break;

			//GLOBALS
			case AST_VARIABLE: //type TK_IDENTIFIER '=' literal
				printAst(node->sons[0], file);
				fprintf(file, "%s", node->symbol->text);
				fprintf(file, " = ");
				printAst(node->sons[1], file);
				fprintf(file, ";\n");
				break;

			case AST_ARRAY_EMPTY: //type TK_IDENTIFIER 'q'literal'p' 
				printAst(node->sons[0], file);
				fprintf(file, "%s", node->symbol->text);
				fprintf(file, " q");
				printAst(node->sons[1], file);
				fprintf(file, "p ");
				fprintf(file, ";\n");
				break;

			case AST_ARRAY_INIT: //type TK_IDENTIFIER 'q'literal'p' ':' literal_sequence
				printAst(node->sons[0], file);
				fprintf(file, "%s", node->symbol->text);
				fprintf(file, " q");
				printAst(node->sons[1], file);
				fprintf(file, "p : ");
				printAst(node->sons[2], file);
				fprintf(file, ";\n");
				break;

			case AST_LIT_ONLY:
				printAst(node->sons[0], file);
				break;

			case AST_LIT_SEQUENCE:
				printAst(node->sons[0], file);
				if(node->sons[1])
					fprintf(file, " ");
					printAst(node->sons[1], file);
				break;

			case AST_FUNCTION: 	
			//type TK_IDENTIFIER 'd' 'b' command 
			//initAst(AST_FUNCTION, $2, $1, 0, $5, 0); }
				printAst(node->sons[0], file);
				if(node->symbol)
					fprintf(file, "%s d ", node->symbol->text);
				if(node->sons[1])
					printAst(node->sons[1], file);
				fprintf(file, " b");
				printAst(node->sons[2], file);
				fprintf(file, "\n");
				break;

			case AST_ARGUMENT: //type TK_IDENTIFIER
				printAst(node->sons[0], file);
				fprintf(file, "%s", node->symbol->text);
				break;

			case AST_ARG_LIST: //argument | argument ',' argument_list
				printAst(node->sons[0], file);
				if(node->sons[1]){
					fprintf(file, ",");
					printAst(node->sons[1], file);
				}
				break;

			case AST_COMMAND:
				printAst(node->sons[0], file);
				break;

			case AST_COMMAND_BLOCK:
				fprintf(file, "{");
				fprintf(file, "\n");
				if(node->sons[0])
					printAst(node->sons[0], file);
				fprintf(file, "}");
				break;

			case AST_COMMAND_SEQUENCE:
				printAst(node->sons[0], file);
				fprintf(file, ";\n");
				if(node->sons[1]){
					printAst(node->sons[1], file);
				}
				break;

			case AST_IF: //KW_IF expression KW_THEN command 
				fprintf(file, "if ");
				printAst(node->sons[0], file);
				fprintf(file, " then\n\t");
				printAst(node->sons[1], file);
				break;

			case AST_IF_ELSE: //KW_IF expression KW_THEN command KW_ELSE command
				fprintf(file, "if ");
				printAst(node->sons[0], file);
				fprintf(file, " then\n\t");
				printAst(node->sons[1], file);
				fprintf(file, "\nelse\n\t ");
				printAst(node->sons[2], file);
				break;

			case AST_WHILE: //KW_WHILE expression command
				fprintf(file, "while ");
				printAst(node->sons[0], file);
				printAst(node->sons[1], file);
				break;

			//EXPRESSIONS
			case AST_EXPRESSION_ID: //TK_IDENTIFIER
				fprintf(file, "%s", node->symbol->text);
				break;

			case AST_EXPRESSION_FUNCTION: //TK_IDENTIFIER 'q' expression 'p'
				fprintf(file, "%s q", node->symbol->text);
				printAst(node->sons[0], file);
				fprintf(file, "p");
				break;

			case AST_EXPRESSION_LIST: //expression ',' expression
				printAst(node->sons[0], file);
				if(node->sons[1]){
					fprintf(file, ",");
					printAst(node->sons[1], file);
				}
				break;

			case AST_EXPRESSION_DB_EMPTY: //TK_IDENTIFIER 'd' 'b' 
				fprintf(file, "%s d b", node->symbol->text);
				break;

			case AST_EXPRESSION_DB: // 'd' expression 'b'
				fprintf(file, "d");
				printAst(node->sons[0], file);
				fprintf(file, "b");
				break;			

			case AST_EXPRESSION_DB_ID: //TK_IDENTIFIER 'd'list_expressions'b'
				fprintf(file, "%s d", node->symbol->text);
				printAst(node->sons[0], file);
				fprintf(file, "b");
				break;

			case AST_LE:
				printAst(node->sons[0], file);
				fprintf(file, " <= ");
				printAst(node->sons[1], file);
				break;

			case AST_GE:
				printAst(node->sons[0], file);
				fprintf(file, " >= ");
				printAst(node->sons[1], file);
				break;

			case AST_EQ:
				printAst(node->sons[0], file);
				fprintf(file, " == ");
				printAst(node->sons[1], file);
				break;

			case AST_OR:
				printAst(node->sons[0], file);
				fprintf(file, " or ");
				printAst(node->sons[1], file);
				break;

			case AST_AND:
				printAst(node->sons[0], file);
				fprintf(file, " and ");
				printAst(node->sons[1], file);
				break;

			case AST_NOT:
				printAst(node->sons[0], file);
				fprintf(file, " not ");
				printAst(node->sons[1], file);
				break;

			case AST_LESS:
				printAst(node->sons[0], file);
				fprintf(file, " < ");
				printAst(node->sons[1], file);
				break;

			case AST_ADD:
				printAst(node->sons[0], file);
				fprintf(file, " + ");
				printAst(node->sons[1], file);
				break;

			case AST_SUB:
				printAst(node->sons[0], file);
				fprintf(file, " - ");
				printAst(node->sons[1], file);
				break;

			case AST_MULT:
				printAst(node->sons[0], file);
				fprintf(file, " * ");
				printAst(node->sons[1], file);
				break;

			case AST_DIV:
				printAst(node->sons[0], file);
				fprintf(file, " / ");
				printAst(node->sons[1], file);
				break;

			case AST_GREATER:
				printAst(node->sons[0], file);
				fprintf(file, " > ");
				printAst(node->sons[1], file);
				break;

			case AST_ATTR_SINGLE: //TK_IDENTIFIER '=' expression 
				fprintf(file, "%s = ", node->symbol->text);
				printAst(node->sons[0], file);
				break;

			case AST_ATTR_ARRAY: //TK_IDENTIFIER 'q' expression 'p' '=' expression
				fprintf(file, "%s q", node->symbol->text);
				printAst(node->sons[0], file);
				fprintf(file, "p = ");
				printAst(node->sons[1], file);
				break;

				default:
					fprintf(file, "nothing was found!\n");
					break;


		}
	}
}
