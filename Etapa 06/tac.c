//
//  tac.c
//  
//
//  Created by Vilmar Fonseca on 10/11/18.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "tac.h"

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2){
    TAC *new;
    new = (TAC *) calloc(1, sizeof(TAC));
    new->type = type;
    new->res = res;
    new->op1 = op1;
    new->op2 = op2;
    new->prev = 0;
    new->next = 0;
    return new;
}

void tacPrintPrev(TAC* node){
    if(node){
        tacPrintNode(node);
        tacPrintPrev(node->prev);
    }
}

void tacPrintNext(TAC* node){
    if(node){
        tacPrintNode(node);
        tacPrintNext(node->next);
    }
}

TAC *tacReverse(TAC *ultimo){
    TAC *tac;
    for(tac=ultimo; tac->prev; tac = tac->prev){
        tac->prev->next = tac;
    }
    
    return tac;
}

TAC *tacJoin(TAC *tac1, TAC *tac2){
    TAC *iterator;
    if (!tac1)
        return tac2;
    if (!tac2)
        return tac1;
    
    for(iterator = tac2; iterator->prev; iterator = iterator->prev);
    
    iterator->prev = tac1;
    
    return tac2;
}

TAC *tacGenerate(AST_NODE *node){
    int i = 0;
    TAC *code[4];
    TAC *result;
    
    if(!node)
        return 0;
    
    for(i = 0; i < 4; ++i){
        code[i] = tacGenerate(node->sons[i]);
    }
    
    switch(node->type){
            
        case AST_IDENTIFIER:        result = tacCreate(AST_IDENTIFIER, node->symbol, 0, 0); break;
        case AST_VARIABLE:          result = makeVar(node->symbol, code);  break;
        case AST_ARRAY_EMPTY:       result = makeArray(node->symbol, code); break;
        case AST_LIT_SEQUENCE:      result = makeArrayInit(node->sons[0]->symbol, code);    break;
        case AST_RETURN:            result = makeReturn(code);  break;
        case AST_FUNCTION:          result = makeFunctionDefinition(node->symbol, code); break;
        case AST_READ:              result = makeRead(node->symbol);    break;
        case AST_PRINT:             result = makePrint(code);   break;
        case AST_ADD:               result = makeOperacaoBinaria(TAC_ADD, code);    break;
        case AST_SUB:               result = makeOperacaoBinaria(TAC_SUB, code);    break;
        case AST_MULT:              result = makeOperacaoBinaria(TAC_MULT, code);   break;
        case AST_DIV:               result = makeOperacaoBinaria(TAC_DIV, code);    break;
        case AST_AND:               result = makeOperacaoBinaria(TAC_AND, code);    break;
        case AST_OR:                result = makeOperacaoBinaria(TAC_OR,  code);    break;
        case AST_LE:                result = makeOperacaoBinaria(TAC_LE,  code);    break;
        case AST_GE:                result = makeOperacaoBinaria(TAC_GE,  code);    break;
        case AST_EQ:                result = makeOperacaoBinaria(TAC_EQ,  code);    break;
        case AST_NOT:               result = makeOperacaoBinaria(TAC_NOT, code);    break;
        case AST_LESS:              result = makeOperacaoBinaria(TAC_LESS, code);   break;
        case AST_ATTR_SINGLE:       result = makeAtribuicao(node->symbol, code);    break;
        case AST_ATTR_ARRAY:        result = makeAtribuicaoArray(node->symbol, code);   break;
        case AST_WHILE:             result = makeWhile(code); break;
        case AST_IF:                result = makeIfThen(code);    break;
        case AST_IF_ELSE:           result = makeIfThenElse(code);    break;
        default:                    result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]) , code[3]);
    }
    
    return result;
}

void tacPrintNode(TAC *node){
    if(node->type != TAC_SYMBOL){
        printf("TAC - ");
        
        switch(node->type){
            case TAC_SYMBOL:    printf("TAC_SYMBOL          "); break;
                
            case TAC_ADD:
                printf("TAC_ADD             ");
                break;
                
            case TAC_SUB:
                printf("TAC_SUB             ");
                break;
                
            case TAC_MULT:
                printf("TAC_MULT            ");
                break;
                
            case TAC_DIV:
                printf("TAC_DIV             ");
                break;
                
            case TAC_OR:
                printf("TAC_OR              ");
                break;
                
            case TAC_AND:
                printf("TAC_AND             ");
                break;
                
            case TAC_EQ:
                printf("TAC_EQ              ");
                break;
                
            case TAC_GE:
                printf("TAC_GE              ");
                break;
                
            case TAC_LE:
                printf("TAC_LE              ");
                break;
                
            case TAC_LESS:
                printf("TAC_LESS            ");
                break;
                
            case TAC_LABEL:
                printf("TAC_LABEL           ");
                break;
                
            case TAC_BEGIN_FUNCTION:
                printf("TAC_BEGIN_FUNCTION  ");
                break;
                
            case TAC_END_FUNCTION:
                printf("TAC_END_FUNCTION    ");
                break;
                
            case TAC_IFZ:
                printf("TAC_IFZ             ");
                break;
                
            case TAC_JUMP:
                printf("TAC_JUMP            ");
                break;
                
            case TAC_CALL:
                printf("TAC_CALL            ");
                break;
                
            case TAC_ARG:
                printf("TAC_ARG             ");
                break;
                
            case TAC_RETURN:
                printf("TAC_RETURN          ");
                break;
                
            case TAC_PRINT:
                printf("TAC_PRINT           ");
                break;
                
            case TAC_READ:
                printf("TAC_READ            ");
                break;
                
            case TAC_ATTR:
                printf("TAC_ATRIBUICAO      ");
                break;
                
            case TAC_ATTR_ARRAY:
                printf("TAC_ATRIBUICAO_ARRAY");
                break;
                
            case TAC_VAR:
                printf("TAC_VAR             ");
                break;
                
            case TAC_ARRAY_DECLARED:
                printf("TAC_ARRAY_INIT      ");
                break;
                
            case TAC_ARRAY_NON_DECLARED:
                printf("TAC_ARRAY           ");
                break;
                
            case TAC_INCREMENT:
                printf("TAC_INCREMENT       ");
                break;
                
            default: printf("*%d*", node->type);
        }
        
        if(node->res) printf("  res: %8s", node->res->text);
        if(node->op1) printf("  op1: %s", node->op1->text);
        if(node->op2) printf("  op2: %s", node->op2->text);
        
        printf("\n");
    }
}

TAC* makeAtribuicaoArray(HASH_NODE* res, TAC **code){
    TAC *newTac = tacCreate(TAC_ATTR_ARRAY, res, code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0);
    return tacJoin(code[0], tacJoin(code[1], newTac));
}

TAC* makeOperacaoBinaria(int operation, TAC** code){
    return tacJoin(code[0], tacJoin(code[1], tacCreate( operation, makeTemp(), code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0 )));
}


TAC* makeAtribuicao(HASH_NODE* res, TAC **code){
    TAC *newTac = tacCreate(TAC_ATTR, res, code[0] ? code[0]->res : 0, 0);
    return tacJoin(code[0], newTac);
}

TAC* makeReturn(TAC **code){
    TAC *expressao = code[0];
    TAC *tacReturn = tacCreate(TAC_RETURN, 0, expressao?expressao->res : 0, 0);
    return tacJoin(expressao, tacReturn);
}

TAC* makeIfThen(TAC** code){
    TAC* expression;
    TAC* thenCmd;
    HASH_NODE *newLabel;
    newLabel = makeLabel();
    expression = tacCreate(TAC_IFZ, newLabel, code[0] ? code[0]->res : 0, 0);
    thenCmd = tacCreate(TAC_LABEL, newLabel, 0, 0);
    return tacJoin(tacJoin(tacJoin(code[0], expression), code[1]), thenCmd);
}

TAC* makeIfThenElse(TAC** code){
    TAC *expression = code[0];
    TAC *thenCmd = code[1];
    TAC *elseCmd = code[2];
    
    HASH_NODE *labelThenCmd = makeLabel();
    TAC* tacLabelThenCmd = tacCreate(TAC_LABEL, labelThenCmd, 0, 0);
    
    HASH_NODE *labelElseCmd = makeLabel();
    TAC* tacLabelElseCmd = tacCreate(TAC_LABEL, labelElseCmd, 0, 0);
    TAC *tacIfz = tacCreate(TAC_IFZ, labelThenCmd, expression ? expression->res : 0, 0);
    TAC *tacJump = tacCreate(TAC_JUMP, labelElseCmd, 0, 0);
    
    return tacJoin(expression,tacJoin(tacIfz,tacJoin(thenCmd,tacJoin(tacJump,tacJoin(tacLabelThenCmd,tacJoin(elseCmd,tacLabelElseCmd))))));
}

TAC* makeFunctionCall(AST_NODE *functionCall){
    AST_NODE *functionDefinition = findFuncDeclaration(functionCall);
    AST_NODE *expressoes = functionCall->sons[0];
    AST_NODE *args = functionDefinition->sons[1];
    
    TAC *tacArgs = makeArguments(args, expressoes);
    TAC *tacCall = tacCreate(TAC_CALL, makeTemp(), functionCall->symbol, NULL);
    
    return tacJoin(tacArgs, tacCall);
}

TAC* makeFunctionDefinition(HASH_NODE *identifier, TAC** code){
    TAC *fnBody = code[2];
    TAC *fbBegin = tacCreate(TAC_BEGIN_FUNCTION, identifier, 0, 0);
    TAC *fbEnd = tacCreate(TAC_END_FUNCTION, identifier, 0, 0);
    return tacJoin(fbBegin, tacJoin(fnBody, fbEnd));
}

TAC *makeArguments(AST_NODE *args, AST_NODE *expressoes){
    TAC *tacListOfArgs = 0;
    while(args && expressoes){
        HASH_NODE *argSymbol = args->sons[0]->symbol;
        AST_NODE *expr = expressoes->sons[0];
        
        TAC *tacExpression = tacGenerate(expr);
        
        TAC *tacArg = tacCreate(TAC_ARG, argSymbol, tacExpression ? tacExpression->res : 0, 0);
        
        tacListOfArgs = tacJoin(tacListOfArgs, tacJoin(tacExpression, tacArg));
        
        args = args->sons[1];
        
        expressoes = expressoes->sons[1];
    }
    
    return tacListOfArgs;
}

TAC* makeVar(HASH_NODE* res, TAC **code){
    TAC *newTac = tacCreate(TAC_VAR, res, code[1] ? code[1]->res : 0, 0);
    return tacJoin(code[1], newTac);
}

TAC* makeArrayInit(HASH_NODE* res, TAC **code){
    TAC *newTac = tacCreate(TAC_ARRAY_DECLARED, res, 0, 0);
    return tacJoin(newTac, code[1]);
}

TAC* makeArray(HASH_NODE* res, TAC **code){
    TAC *arrayTac = tacCreate(TAC_ARRAY_NON_DECLARED, res, code[1] ? code[1]->res : 0, code[2] ? makeLabelArray(res) : 0);
    if(code[2])
        return tacJoin(code[1], tacJoin(arrayTac, code[2]));
    
    return tacJoin(code[1], arrayTac);
}

TAC* makeRead(HASH_NODE *identifier){
    return tacCreate(TAC_READ, 0, identifier ? identifier : 0, 0);
}

TAC* makePrint(TAC **code){
    TAC *tacExpression = code[0];
    TAC *tacPrintList = code[1];
    
    if(!tacExpression)
        return 0;
    
    if(!tacPrintList){
        TAC *tacPrint = tacCreate(TAC_PRINT, 0, tacExpression ? tacExpression->res : 0, 0);
        return tacJoin(tacExpression, tacPrint);
    }
    
    TAC *tacPrint = tacCreate(TAC_PRINT, 0, tacExpression ? tacExpression->res : 0, 0);
    return tacJoin(tacExpression, tacJoin(tacPrint, tacPrintList));
}

TAC* makeWhile(TAC **code){
    TAC* tacExpression = code[0];
    TAC* tacCommand = code[1];
    
    HASH_NODE *labelBeforeP = makeLabel();
    TAC *tacLabelBeforeP = tacCreate(TAC_LABEL, labelBeforeP, 0, 0);
    
    HASH_NODE *labelAfterQ = makeLabel();
    TAC *tacLabelAfterQ = tacCreate(TAC_LABEL, labelAfterQ, 0, 0);
    
    TAC *tacIfz = tacCreate(TAC_IFZ, labelAfterQ, tacExpression ? tacExpression->res : 0, 0);
    
    TAC *tacJumpBack = tacCreate(TAC_JUMP, labelBeforeP, 0, 0);
    
    return tacJoin(tacLabelBeforeP,tacJoin(tacExpression,tacJoin(tacIfz,tacJoin(tacCommand,tacJoin(tacJumpBack,tacLabelAfterQ)))));
}
