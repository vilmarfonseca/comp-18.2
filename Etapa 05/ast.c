#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "hash.h"

AST_NODE *initAst(int type, int lineNumber, HASH_NODE *symbol, AST_NODE *son0, AST_NODE *son1, AST_NODE *son2, AST_NODE *son3)
{
	AST_NODE *new_node;

	if(!(new_node = (AST_NODE*) calloc(1, sizeof(AST_NODE)))){
		fprintf(stderr, "Couldn't allocate memory\n");
		exit(1);
	}

    new_node->dataType = DATATYPE_NOT_DEFINED;
    new_node->lineNumber = lineNumber;
	new_node->type = type;
	new_node->symbol = symbol;
	new_node->sons[0] = son0;
	new_node->sons[1] = son1;
	new_node->sons[2] = son2;
	new_node->sons[3] = son3;

	return new_node;
}

void printAstNode(AST_NODE *node, int level){
    int i;
    for(i=0; i<level; i++)
        fprintf(stderr, "   ");
	if(node){
        switch (node->type) {
            case AST_PROGRAM: fprintf(stderr, "AST_PROGRAM - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_IDENTIFIER: fprintf(stderr, "AST_IDENTIFIER - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_VARIABLE: fprintf(stderr, "AST_VARIABLE - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_ARRAY_EMPTY: fprintf(stderr, "AST_ARRAY_EMPTY - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_ARRAY_INIT: fprintf(stderr, "AST_ARRAY_INIT - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_FUNCTION: fprintf(stderr, "AST_FUNCTION - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_ARG_LIST: fprintf(stderr, "AST_ARG_LIST - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_ARGUMENT: fprintf(stderr, "AST_ARGUMENT - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_CHAR: fprintf(stderr, "AST_CHAR - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_INT: fprintf(stderr, "AST_INT - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_FLOAT: fprintf(stderr, "AST_FLOAT - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_LIT_ONLY: fprintf(stderr, "AST_LIT_ONLY - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_LIT_SEQUENCE: fprintf(stderr, "AST_LIT_SEQUENCE - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_COMMAND: fprintf(stderr, "AST_COMMAND - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_COMMAND_BLOCK: fprintf(stderr, "AST_COMMAND_BLOCK - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_COMMAND_SEQUENCE: fprintf(stderr, "AST_COMMAND_SEQUENCE - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_IF: fprintf(stderr, "AST_IF - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_IF_ELSE: fprintf(stderr, "AST_IF_ELSE - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_WHILE: fprintf(stderr, "AST_WHILE - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_READ: fprintf(stderr, "AST_READ - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_PRINT: fprintf(stderr, "AST_PRINT - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_RETURN: fprintf(stderr, "AST_RETURN - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_EXPRESSION_DB_ID: fprintf(stderr, "AST_EXPRESSION_DB_ID - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_EXPRESSION_ID: fprintf(stderr, "AST_EXPRESSION_ID - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_EXPRESSION_FUNCTION: fprintf(stderr, "AST_EXPRESSION_FUNCTION - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_EXPRESSION_ARRAY: fprintf(stderr, "AST_EXPRESSION_ARRAY - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_EXPRESSION_LIST: fprintf(stderr, "AST_EXPRESSION_LIST - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_EXPRESSION_DB_EMPTY: fprintf(stderr, "AST_EXPRESSION_DB_EMPTY - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_EXPRESSION_DB: fprintf(stderr, "AST_EXPRESSION_DB - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_LE: fprintf(stderr, "AST_LE - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_GE: fprintf(stderr, "AST_GE - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_EQ: fprintf(stderr, "AST_EQ - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_OR: fprintf(stderr, "AST_OR - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_AND: fprintf(stderr, "AST_AND - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_NOT: fprintf(stderr, "AST_NOT - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_LESS: fprintf(stderr, "AST_LESS - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_ADD: fprintf(stderr, "AST_ADD - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_SUB: fprintf(stderr, "AST_SUB - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_MULT: fprintf(stderr, "AST_MULT - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_DIV: fprintf(stderr, "AST_DIV - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_GREATER: fprintf(stderr, "AST_GREATER - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_ATTR_SINGLE: fprintf(stderr, "AST_ATTR_SINGLE - %d, line: %d ", node->type, node->lineNumber);break;
            case AST_ATTR_ARRAY: fprintf(stderr, "AST_ATTR_ARRAY - %d, line: %d ", node->type, node->lineNumber);break;
            default: fprintf(stderr,"AST_UNKNOWN "); break;
        }
        if(node->symbol != 0)
            fprintf(stderr, "%s, \n", node->symbol->text);
        else
            fprintf(stderr, "<no symbol>, \n");
		if(node->sons[0])
			printAstNode(node->sons[0], level+1);
		if(node->sons[1])
			printAstNode(node->sons[1], level+1);
		if(node->sons[2])
			printAstNode(node->sons[2], level+1);
		if(node->sons[3])
			printAstNode(node->sons[3], level+1);
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
