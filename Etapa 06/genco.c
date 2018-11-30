/*
 * created by Hermes Tessaro
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "semantic.h"
#include "genco.h"


int init_genco = 0;


void tac_to_asm(TAC* node, FILE* output){
    
    int halt_decl = 0;
    TAC *tac;

    if(init_genco == 0){
        initTempVar(output);
        initParamVar(output);
        init_genco = 1;
    }

    for(tac = node; tac; tac = tac->next){
        switch(tac->type){
            case TAC_VAR:
                gencoVarDecl(output, tac);
                break;
            case TAC_ARRAY_DECLARED:
                gencoArrayDecl(output, tac);
                break;
            case TAC_BEGIN_FUNCTION:
                if(strcmp(tac->res->text, "main") == 0){
                    fprintf(output, ".PINT:\n\t.string\t\"%%d\\n\"\n"
                                    ".RINT:\n\t.string\t\"%%d\"n"
                                    ".PCHAR:\n\t.string\t\"%%c\\n\"\n");
                    halt_decl = 1;
                }

                fprintf(output, "\t.globl\t%s\n", tac->res->text);
                fprintf(output, "%s:\n"
                            "\tpushq\t%%rbp\n"
                            "\tmovq\t%%rsp, %%rbp\n", tac->res->text);
                break;
            case TAC_END_FUNCTION:
                fprintf(output, "\tpopq\t%%rbp\n\tret\n");
                break;
            case TAC_ADD:
            case TAC_SUB:
            case TAC_MULT:
                gencoNumOp(tac, output);
                break;
            case TAC_ATTR:
                if(tac->op1->type == TAC_LABEL || tac->op1->type == SYMBOL_LITINT) 
                    fprintf(output, "\tmovl\t%s(%%rip), %%eax\n"
                                    "\tmovl\t%%eax, %s(%%rip)\n", tac->op1->text, tac->res->text);
                else 
                    fprintf(output, "\tmovl\t$%s, %s(%%rip)\n", tac->op1->text, tac->res->text);
                break;
            case TAC_ATTR_ARRAY: //value then array index
                if(tac->op2->type == TAC_LABEL) 
                    fprintf(output, "\tmovl\t%s(%%rip), %%ebx\n", tac->op2->text);
                else 
                    fprintf(output, "\tmovl\t$%s, %%ebx\n", tac->op2->text);
                if(tac->op1->type == TAC_LABEL) {
                    fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                    fprintf(output, "\tcltq\n");
                    fprintf(output, "\tmovl\t%%ebx, %s(,%%rax,4)\n", tac->res->text);
                }
                else {
                    fprintf(output, "\tmovl\t%%ebx, %s+%s*4(%%rip)\n", tac->res->text, tac->op1->text);
                }
                break;
            case TAC_PRINT:
                if(tac->op1->dataType == DATATYPE_CHAR) {
                    fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                    fprintf(output, "\tmovl\t%%eax, %%esi\n");
                    fprintf(output, "\tmovl\t$.PCHAR, %%edi\n");
                    fprintf(output, "\tcall\tprintf\n");
                }
                else{
                    if(tac->op1->type == TAC_LABEL)
                    {
                        fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                        fprintf(output, "\tmovl\t%%eax, %%esi\n");
                        fprintf(output, "\tmovl\t$.PINT, %%edi\n");
                        fprintf(output, "\tcall\tprintf\n");
                    }
                    else {
                        fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);
                        fprintf(output, "\tmovl\t%%eax, %%esi\n");
                        fprintf(output, "\tmovl\t$.PINT, %%edi\n");
                        fprintf(output, "\tcall\tprintf\n");
                    }
                }
                break;
            case TAC_LABEL:
                fprintf(output, "%s:\n", tac->res->text);
                break;
            case TAC_INCREMENT:
                fprintf(output, "\tmovl\t%s(%%rip), %%eax\n"
                            "\taddl\t$1, %%eax\n"
                            "\tmovl\t%%eax, %s(%%rip)\n", tac->res->text, tac->res->text);
                break;
            case TAC_LE:
                fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                if(tac->op2->type == TAC_SYMBOL || tac->op2->type == SYMBOL_LITINT)
                    fprintf(output, "\tcmpl\t$%s, %%eax\n", tac->op2->text);
                else {
                    fprintf(output, "\tmovl\t%s(%%rip), %%ecx\n", tac->op2->text);
                    fprintf(output, "\tcmpl\t%%ecx, %%eax\n");
                }
                fprintf(output, "\tsetle\t%%al\n");
                break;
            case TAC_IFZ:
                if(tac->op1->dataType != DATATYPE_TEMP) 
                    fprintf(output, "problem\n");
                else 
                    fprintf(output, "\tmovzbl\t%%al, %%eax\n");
                fprintf(output, "\tjz\t%s\n", tac->res->text);
                break;
            case TAC_JUMP:
                fprintf(output, "\tjmp\t%s\n", tac->res->text);
                break;
            case TAC_READ:
                if(tac->op1->dataType == DATATYPE_INT) {
                    fprintf(output, "\tmovl\t$%s, %%esi\n", tac->op1->text);
                    fprintf(output, "\tmovl\t$.RINT, %%edi\n");
                    fprintf(output, "\tmovl\t$0, %%eax\n");
                    fprintf(output, "\tcall\t__isoc99_scanf\n");
                }
                break;
            case TAC_CALL:
                fprintf(output, "\tcall\t%s\n", tac->op1->text);
                fprintf(output, "\tmovl\t%%eax, %s(%%rip)\n", tac->res->text);
                break;
            case TAC_RETURN:
                if(tac->op1->type == TAC_LABEL)
                    fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                else
                    fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);
                break;
            case TAC_ARG:
                if(tac->op1->type == TAC_LABEL)
                    fprintf(output, "\tmovl\t%s(%%rip), %%eax\n", tac->op1->text);
                else
                    fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);
                fprintf(output, "\tmovl\t%%eax, %s(%%rip)\n", tac->res->text);
                break;
        }
    }
    init_genco = 0;

}




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
    for(func = listFuncDecl; func; func = func->next) {
        listArguments = func->ast_node->sons[1];

        while(listArguments) {
            argument = listArguments->sons[0];
            
            if(argument->dataType == DATATYPE_INT || argument->dataType == DATATYPE_FLOAT ) {
                fprintf(output, "\t.globl\t%s\n", argument->symbol->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.align\t4\n");
                fprintf(output, "\t.size\t%s, 4\n", argument->symbol->text);
                fprintf(output, "%s:\n", argument->symbol->text);
                fprintf(output, "\t.long\t0\n");
            }
            
            else if(argument->dataType == DATATYPE_CHAR || argument->dataType == DATATYPE_BOOL) {
                fprintf(output, "\t.globl\t%s\n", argument->symbol->text);
                fprintf(output, "\t.data\n");
                fprintf(output, "\t.size\t%s, 1\n", argument->symbol->text);
                fprintf(output, "%s:\n", argument->symbol->text);
            }
            listArguments = listArguments->sons[1];
        }
    }
}

void gencoVarDecl(FILE* output, TAC* tac){
    HASH_NODE* node;
    if(tac->res){
        node = hashFind(tac->res->text);
    }
    else{
        node = NULL;
    }

    if(node){
        switch(node->dataType) {
            case DATATYPE_INT:
            case DATATYPE_FLOAT:
                gencoLongLiteralDecl(output, node, tac);
                break;
            case DATATYPE_BOOL:
            case DATATYPE_CHAR:
                gencoByteLiteralDecl(output, node, tac);
                break;
        }
    }
}

void gencoArrayDecl(FILE* output, TAC* tac){
    HASH_NODE* node;
    if(tac->res){
        HASH_NODE* node = hashFind(tac->res->text);
    }
    else{
        HASH_NODE* node = NULL;
    }

    if(node){
        switch(node->dataType) {
            case DATATYPE_INT:
            case DATATYPE_FLOAT:
                gencoLongArrayDecl(output, tac);
                break;
            case DATATYPE_BOOL:
            case DATATYPE_CHAR:
                gencoByteArrayDecl(output, node, tac);
                break;
        }
    }
}

void gencoByteLiteralDecl(FILE* output, HASH_NODE* node, TAC* tac){
    int litValue = 0;

    fprintf(output, "\t.globl\t%s\n", tac->res->text);
    fprintf(output, "\t.data\n");
    fprintf(output, "\t.align\t8\n");
    fprintf(output, "\t.size\t%s, 8\n", tac->res->text);
    fprintf(output, "%s:\n", tac->res->text);
    fprintf(output, "\t.long\t%d\n", atoi(tac->op1->text));

    if(node->dataType == DATATYPE_CHAR) {
        litValue = tac->op1->text[1];
    }
    else{
        if(strcmp(tac->op1->text, "TRUE") == 0)
            litValue = 1;
        else
            litValue = 0;
    }

    fprintf(output, "\t.byte\t%d\n", litValue);
}

void gencoLongLiteralDecl(FILE* output, HASH_NODE* node, TAC* tac){
    fprintf(output, "\t.globl\t%s\n", tac->res->text);
    fprintf(output, "\t.data\n");
    fprintf(output, "\t.align\t4\n");
    fprintf(output, "\t.size\t%s, 4\n", tac->res->text);
    fprintf(output, "%s:\n", tac->res->text);
    fprintf(output, "\t.long\t%d\n", atoi(tac->op1->text));
}

void gencoByteArrayDecl(FILE* output, HASH_NODE* node, TAC *tac){
    int size = atoi(tac->op1->text);
    int litValue = 0;
    TAC *tmp = tac->next;


    fprintf(output, "\t.globl\t%s\n", tac->res->text);
    fprintf(output, "\t.data\n");
    fprintf(output, "\t.size\t%s, %d\n", tac->res->text, size);
    fprintf(output, "%s:\n", tac->res->text);

    if(tac->op2){
        for (int i = 0; i < size; i++)
        {
            if(node->dataType == DATATYPE_CHAR)
                litValue = tmp->res->text[1];
            else{
                if(strcmp(tmp->res->text, "TRUE") == 0)
                    litValue = 1;
                else
                    litValue = 0;
            }
            fprintf(output, "\t.byte\t%d\n", litValue);
            tmp = tmp->next;
        }
    }
}

void gencoLongArrayDecl(FILE *output, TAC *tac){
    int size = atoi(tac->op1->text);

    fprintf(output, "\t.globl\t%s\n", tac->res->text);
    fprintf(output, "\t.data\n");
    fprintf(output, "\t.size\t%s, %d\n", tac->res->text, size * 4);
    fprintf(output, "%s:\n", tac->res->text);

    TAC *tmp = tac->next;
    if(tac->op2){
        for (int i = 0; i < size; i++) {
            fprintf(output, "\t.long\t%d\n", atoi(tmp->res->text));
            tmp = tmp->next;
        }
    }
}

void gencoNumOp(TAC* tac, FILE* output){
    char op[8];
    switch(tac->type){
        case TAC_ADD:
            strcpy(op, "addl");
            break;
        case TAC_SUB:
            strcpy(op, "subl");
            break;
        case TAC_MULT:
            strcpy(op, "imull");
            break;
        default:
            return;
    }

    if(tac->op1->type == TAC_LABEL) 
        fprintf(output, "\tmovl\t%s(%%rip, %%eax)\n", tac->op1->text);
    else
        fprintf(output, "\tmovl\t$%s, %%eax\n", tac->op1->text);

    if(tac->op2->type == TAC_LABEL) 
        fprintf(output, "\tmovl\t%s(%%rip), %%ebx\n", tac->op2->text);
    else
        fprintf(output, "\tmovl\t$%s, %%ebx\n", tac->op2->text);
    
    fprintf(output, "\t%s\t%%ebx, %%eax\n", op);
    fprintf(output, "\tmovl\t%%eax, %s\n", tac->res->text);
}