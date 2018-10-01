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

void printAst(AST_NODE *node, FILE* file)
{
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
			fprintf(file, "%s", node->symbols_pointer->text);
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
			if(node->symbols_pointer)
				fprintf(file, "%s", node->symbols_pointer->text);
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
			fprintf(file, "%s", node->symbols_pointer->text);
			printAst(node->sons[1], file);
			fprintf(file, ";\n");
			break;

		case AST_ARRAY_EMPTY: //type TK_IDENTIFIER 'q'LIT_INTEGER'p' 
			printAst(node->sons[0], file);
			fprintf(file, "%s", node->symbols_pointer->text);
			fprintf(file, "q");
			printAst(node->sons[1], file);
			fprintf(file, "p");
			fprintf(file, ";\n");
			break;

		case AST_ARRAY_INIT: //type TK_IDENTIFIER 'q'LIT_INTEGER'p' ':' literal_sequence
			printAst(node->sons[0], file);
			fprintf(file, "%s", node->symbols_pointer->text);
			fprintf(file, "q");
			printAst(node->sons[1], file);
			fprintf(file, "p : ");
			printAst(node->sons[2], file);
			break;

		case AST_LIT_ONLY:
			fprintf(file, "%s", node->symbols_pointer->text);
			break;

		case AST_LIT_SEQUENCE:
			printAst(node->sons[0], file);
			if(node->sons[1])
				printAst(node->sons[1], file);
			break;

		case AST_FUNCTION:
			printAst(node->sons[0], file);
			fprintf(file, "%s d", node->symbols_pointer->text);
			if(node->sons[1])
				printAst(node>sons[1], file);
			fprintf(file, "b");
			printAst(node>sons[2], file);

		case AST_ARGUMENT: //type TK_IDENTIFIER
			printAst(node->sons[0], file);
			fprintf(file, "%s d", node->symbols_pointer->text);
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
			if(node->sons[0])
				printAst(node->sons[0], file);
			fprintf(file, "}");
			break;

		case AST_COMMAND_SEQUENCE:
			if(node->sons[0]){
				printAst(node->sons[0], file);
				fprintf(file, ";");
				printAst(node->sons[1], file);
			}
			break;

		case AST_IF: //KW_IF expression KW_THEN command 
			fprintf(file, "if ");
			printAst(node->sons[0], file);
			fprintf(file, " then");
			printAst(node->sons[1], file);
			break;

		case AST_IF_ELSE: //KW_IF expression KW_THEN command KW_ELSE command
			fprintf(file, "if ");
			printAst(node->sons[0], file);
			fprintf(file, " then");
			printAst(node->sons[1], file);
			fprintf(file, " else");
			printAst(node->sons[2], file);
			break;

		case AST_WHILE: //KW_WHILE expression command
			fprintf(file, "while");
			printAst(node->sons[0], file);
			printAst(node->sons[1], file);
			break;

		//EXPRESSIONS
		case AST_EXPRESSION_ID: //TK_IDENTIFIER
			fprintf(file, "%s", node->symbols_pointer->text);
			break;

		case AST_EXPRESSION_FUNCTION: //TK_IDENTIFIER 'q' expression 'p'
			fprintf(file, "%s q", node->symbols_pointer->text);
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
			fprintf(file, "%s d b", node->symbols_pointer->text);
			break;

		case AST_EXPRESSION_DB // 'd' expression 'b'
			fprintf(file, "d");
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
			fprintf(file, " || ");
			printAst(node->sons[1], file);
			break;

		case AST_AND:
			printAst(node->sons[0], file);
			fprintf(file, " && ");
			printAst(node->sons[1], file);
			break;

		case AST_NOT:
			printAst(node->sons[0], file);
			fprintf(file, " ! ");
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

		case AST_EXPRESSION_DB:
			fprintf(file, "d");
			printAst(node->sons[0], file);
			fprintf(file, "b");
			break;

		case AST_ATTR_SINGLE: //TK_IDENTIFIER '=' expression 
			fprintf(file, "%s = ");
			printAst(node->sons[0], file);
			break;

		case AST_ATTR_ARRAY: //TK_IDENTIFIER 'q' expression 'p' '=' expression
			fprintf(file, "%s q");
			printAst(node->sons[0], file);
			fprintf(file, "p = ");
			printAst(node->sons[1], file);
			break;

			default:
				fprintf(file, "nothing was found!\n");
				break;


	}
}