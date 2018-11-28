#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "semantic.h"
#include "genco.h"





void tac_to_asm(TAC* node, FILE* output);




void initTempVar(FILE *output){
    HASH_NODE *node;
    int i;
    for(i = 0; i < HASH_SIZE; i++) {
        for (node = Table[i]; node; node = node->next){
            if(node->dataType == DATATYPE_TEMP){
                fprintf(output, "\t.globl\t%s\n", node->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.align\t4\n");
                fprintf(output, "\t.size\t%s, 4\n", node->text);
                fprintf(output, "%s:\n", node->text);
                fprintf(output, "\t.zero\t4\n");
            }
        }
    }
}

void initParamVar(FILE *output) {
    LIST_FUNC_DECL *func;
    AST_NODE *listArguments;
    AST_NODE *argument;
    for(fun = listFuncDecl; fun; fun = fun->next) {
        listArguments = fun->ast_node->sons[1];

        while(listArguments) {
            argument = listArguments->sons[0];
            
            else if(argument->dataType == DATATYPE_INT || argument->dataType == DATATYPE_BOOL || argument->dataType == DATATYPE_FLOAT ) {
                fprintf(output, "\t.globl\t%s\n", argument->symbol->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.align\t4\n");
                fprintf(output, "\t.size\t%s, 4\n", argument->symbol->text);
                fprintf(output, "%s:\n", argument->symbol->text);
                fprintf(output, "\t.long\t0\n");
            }
            
            else if(argument->dataType == DATATYPE_CHAR) {
                fprintf(output, "\t.globl\t%s\n", argument->symbol->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.size\t%s, 1\n", argument->symbol->text);
                fprintf(output, "%s:\n", argument->symbol->text);
            }
            listArguments = listArguments->sons[1];
        }
    }
}