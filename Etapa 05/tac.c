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

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2)
{
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

void tacPrintPrev(TAC* node)
{
    if(node)
    {
        tacPrintNode(node);
        tacPrintPrev(node->prev);
    }
}

void tacPrintNext(TAC* node)
{
    if(node)
    {
        tacPrintNode(node);
        tacPrintNext(node->next);
    }
}

TAC *tacReverse(TAC *ultimo)
{
    TAC *tac;
    for(tac=ultimo; tac->prev; tac = tac->prev)
    {
        tac->prev->next = tac;
    }
    
    return tac;
}

TAC *tacJoin(TAC *tac1, TAC *tac2)
{
    TAC *iterator;
    if (!tac1)
        return tac2;
    if (!tac2)
        return tac1;
    
    for(iterator = tac2; iterator->prev; iterator = iterator->prev);
    
    iterator->prev = tac1;
    
    return tac2;
}

TAC *tacGenerate(AST_NODE *node)
{
    int i = 0;
    TAC *code[4];
    TAC *result;
    
    if(!node)
        return 0;
    
    if(node->type == AST_FUNCTION)
        return makeFnCall(node);
    
    for(i = 0; i < 4; ++i)
    {
        code[i] = tacGenerate(node->sons[i]);
    }
    
    switch(node->type)
    {
            
        case AST_IDENTIFIER:    result = tacCreate(AST_IDENTIFIER, node->symbol, 0, 0); break;
            
            /* GLOBAIS */
        case AST_VARIABLE:   result = makeVariavel(node->symbol, code);  break;
            
        case AST_ARRAY_EMPTY:   result = makeArray(node->symbol, code); break;
        case AST_LIT_SEQUENCE:  result = makeArrayInicializado(node->sons[0]->symbol, code);    break;
            
            /* FUNÇÕES */
        case AST_RETURN:    result = makeReturn(code);  break;
        case AST_FUNCTION:  result = makeFnDef(node->symbol, code); break;
            
            /* PRINT, READ, ETC */
        case AST_READ:  result = makeRead(node->symbol);    break;
        case AST_PRINT:    result = makePrint(code);   break;
            
            /* OPERADORES ARITMÉTICOS */
        case AST_ADD:   result = makeOperacaoBinaria(TAC_ADD, code);    break;
        case AST_SUB:   result = makeOperacaoBinaria(TAC_SUB, code);    break;
        case AST_MULT:  result = makeOperacaoBinaria(TAC_MULT, code);   break;
        case AST_DIV:   result = makeOperacaoBinaria(TAC_DIV, code);    break;
            
            /* OPERADORES LÓGICOS */
        case AST_AND:   result = makeOperacaoBinaria(TAC_AND, code);    break;
        case AST_OR:    result = makeOperacaoBinaria(TAC_OR,  code);    break;
        case AST_LE:    result = makeOperacaoBinaria(TAC_LE,  code);    break;
        case AST_GE:    result = makeOperacaoBinaria(TAC_GE,  code);    break;
        case AST_EQ:    result = makeOperacaoBinaria(TAC_EQ,  code);    break;
        case AST_NOT:   result = makeOperacaoBinaria(TAC_NOT, code);    break;
        case AST_LESS:  result = makeOperacaoBinaria(TAC_LESS, code);   break;
            
            /* ATRIBUIÇÃO */
        case AST_ATTR_SINGLE:   result = makeAtribuicao(node->symbol, code);    break;
        case AST_ATTR_ARRAY:    result = makeAtribuicaoArray(node->symbol, code);   break;
            
        default:    result = tacJoin(tacJoin(tacJoin(code[0], code[1]), code[2]) , code[3]);
    }
    
    return result;
}

void tacPrintNode(TAC *node)
{
    if(node->type != TAC_SYMBOL)
    {
        printf("TAC - ");
        
        switch(node->type)
        {
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
                
            case TAC_ATRIBUICAO:
                printf("TAC_ATRIBUICAO      ");
                break;
                
            case TAC_ATRIBUICAO_ARRAY:
                printf("TAC_ATRIBUICAO_ARRAY");
                break;
                
            case TAC_VAR:
                printf("TAC_VAR             ");
                break;
                
            case TAC_ARRAY_DECLARADO:
                printf("TAC_ARRAY_INIT      ");
                break;
                
            case TAC_ARRAY_NAO_DECLARADO:
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

TAC* makeAtribuicaoArray(HASH_NODE* res, TAC **code)
{
    TAC *newTac = tacCreate(TAC_ATRIBUICAO_ARRAY, res, code[0] ? code[0]->res : 0, code[1] ? code[1]->res : 0);
    return tacJoin(code[0], tacJoin(code[1], newTac));
}

TAC* makeOperacaoBinaria(int operation, TAC** code)
{
    
    return tacJoin(code[0], tacJoin(code[1], tacCreate( operation, makeTemp(), code[0]->res ? code[0]->res : 0, code[1]->res ? code[1]->res : 0 )));
}

TAC* makeAtribuicao(HASH_NODE* res, TAC **code)
{
    TAC *newTac = tacCreate(TAC_ATRIBUICAO, res, code[0] ? code[0]->res : 0, 0);
    return tacJoin(code[0], newTac);
}

TAC* makeReturn(TAC **code)
{
    TAC *expressao = code[0];
    TAC *tacReturn = tacCreate(TAC_RETURN, 0, expressao?expressao->res : 0, 0);
    return tacJoin(expressao, tacReturn);
}

TAC* makeWhenThen(TAC** code)
{
    TAC* expression;
    TAC* thenCmd;
    HASH_NODE *newLabel;
    newLabel = makeLabel();
    expression = tacCreate(TAC_IFZ, newLabel, code[0] ? code[0]->res : 0, 0);
    thenCmd = tacCreate(TAC_LABEL, newLabel, 0, 0);
    return tacJoin(tacJoin(tacJoin(code[0], expression), code[1]), thenCmd);
}

TAC* makeWhenThenElse(TAC** code)
{
    TAC *expression = code[0];
    TAC *thenCmd = code[1];
    TAC *elseCmd = code[2];
    
    HASH_NODE *labelThenCmd = makeLabel();
    TAC* tacLabelThenCmd = tacCreate(TAC_LABEL, labelThenCmd, 0, 0);
    
    HASH_NODE *labelElseCmd = makeLabel();
    TAC* tacLabelElseCmd = tacCreate(TAC_LABEL, labelElseCmd, 0, 0);
    
    /* VERDADEIRO CONTINUA, FALSO VAI PRA LABELTHENCMD */
    TAC *tacIfz = tacCreate(TAC_IFZ, labelThenCmd, expression ? expression->res : 0, 0);
    
    /* VERDADEIRO FAZ O JUMP */
    TAC *tacJump = tacCreate(TAC_JUMP, labelElseCmd, 0, 0);
    
    return tacJoin(expression,
                   tacJoin(tacIfz,
                           tacJoin(thenCmd,
                                   tacJoin(tacJump,
                                           tacJoin(tacLabelThenCmd,
                                                   tacJoin(elseCmd,
                                                           tacLabelElseCmd))))));
}

TAC* makeFnCall(AST_NODE *functionCall)
{
    AST_NODE *functionDefinition = findFuncDeclaration(functionCall);
    AST_NODE *expressoes = functionCall->sons[0];
    AST_NODE *args = functionDefinition->sons[1];
    
    TAC *tacArgs = makeArgumentos(args, expressoes);
    TAC *tacCall = tacCreate(TAC_CALL, makeTemp(), functionCall->symbol, NULL);
    
    return tacJoin(tacArgs, tacCall);
}

TAC* makeFnDef(HASH_NODE *identifier, TAC** code)
{
    TAC *fnBody = code[2];
    TAC *fbBegin = tacCreate(TAC_BEGIN_FUNCTION, identifier, 0, 0);
    TAC *fbEnd = tacCreate(TAC_END_FUNCTION, identifier, 0, 0);
    return tacJoin(fbBegin, tacJoin(fnBody, fbEnd));
}

TAC *makeArgumentos(AST_NODE *args, AST_NODE *expressoes)
{
    TAC *tacListOfArgs = 0;
    while(args && expressoes)
    {
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

TAC* makeVariavel(HASH_NODE* res, TAC **code)
{
    TAC *newTac = tacCreate(TAC_VAR, res, code[1] ? code[1]->res : 0, 0);
    return tacJoin(code[1], newTac);
}

TAC* makeArrayInicializado(HASH_NODE* res, TAC **code)
{
    TAC *newTac = tacCreate(TAC_ARRAY_DECLARADO, res, 0, 0);
    return tacJoin(newTac, code[1]);
}

TAC* makeArray(HASH_NODE* res, TAC **code)
{
    TAC *arrayTac = tacCreate(TAC_ARRAY_NAO_DECLARADO, res, code[1] ? code[1]->res : 0, code[2] ? makeLabelArray(res) : 0);
    if(code[2])
        return tacJoin(code[1], tacJoin(arrayTac, code[2]));
    
    return tacJoin(code[1], arrayTac);
}

TAC* makeRead(HASH_NODE *identifier)
{
    return tacCreate(TAC_READ, 0, identifier ? identifier : 0, 0);
}

TAC* makePrint(TAC **code)
{
    TAC *tacExpression = code[0];
    TAC *tacPrintList = code[1];
    
    if(!tacExpression)
        return 0;
    
    if(!tacPrintList)
    {
        TAC *tacPrint = tacCreate(TAC_PRINT, 0, tacExpression ? tacExpression->res : 0, 0);
        return tacJoin(tacExpression, tacPrint);
    }
    
    TAC *tacPrint = tacCreate(TAC_PRINT, 0, tacExpression ? tacExpression->res : 0, 0);
    return tacJoin(tacExpression, tacJoin(tacPrint, tacPrintList));
}

/* FOR (P = Q TO R) S */
TAC* makeForTo(HASH_NODE* res, TAC **code)
{
    TAC *tacExpressionFinalValue = code[1];
    TAC *tacLoopCmd = code[2];
    
    // P = Q
    TAC *tacAttr = makeAtribuicao(res, code);
    
    // ANTES DE R
    HASH_NODE *labelBeforeForToCondition = makeLabel();
    TAC *tacLabelBeforeForToCondition = tacCreate(TAC_LABEL, labelBeforeForToCondition, 0, 0);
    
    // P <= R ?
    TAC *tacCondition = tacCreate(TAC_LE, makeTemp(), res, tacExpressionFinalValue ? tacExpressionFinalValue->res : 0);
    
    /* INCREMENTO DO P */
    TAC *tacIncrement = tacCreate(TAC_INCREMENT, res, 0, 0);
    
    /* O QUE VEM DEPOIS DO S */
    HASH_NODE *labelAfterForToLoop = makeLabel();
    TAC *tacLabelAfterForToLoop = tacCreate(TAC_LABEL, labelAfterForToLoop, 0, 0);
    
    /* SE P MAIOR QUE R ENTÃO VAI PRA DEPOIS DE S (O QUE ESTÁ FORA DO LOOP */
    TAC *tacIfz = tacCreate(TAC_IFZ, labelAfterForToLoop, tacCondition ? tacCondition->res : 0, 0);
    
    /* CONTINUAÇÃO DO LOOP */
    TAC *tacJumpToBeginOfForTo = tacCreate(TAC_JUMP, labelBeforeForToCondition, 0, 0);
    
    return tacJoin(tacAttr,
                   tacJoin(tacLabelBeforeForToCondition,
                           tacJoin(tacCondition,
                                   tacJoin(tacIfz,
                                           tacJoin(tacLoopCmd,
                                                   tacJoin(tacIncrement,
                                                           tacJoin(tacJumpToBeginOfForTo, tacLabelAfterForToLoop)))))));
}

/* WHILE (P) Q */
TAC* makeWhile(TAC **code)
{
    TAC* tacExpression = code[0];
    TAC* tacCommand = code[1];
    
    HASH_NODE *labelBeforeP = makeLabel();
    TAC *tacLabelBeforeP = tacCreate(TAC_LABEL, labelBeforeP, 0, 0);
    
    HASH_NODE *labelAfterQ = makeLabel();
    TAC *tacLabelAfterQ = tacCreate(TAC_LABEL, labelAfterQ, 0, 0);
    
    TAC *tacIfz = tacCreate(TAC_IFZ, labelAfterQ, tacExpression ? tacExpression->res : 0, 0);
    
    TAC *tacJumpBack = tacCreate(TAC_JUMP, labelBeforeP, 0, 0);
    
    return tacJoin(tacLabelBeforeP,
                   tacJoin(tacExpression,
                           tacJoin(tacIfz,
                                   tacJoin(tacCommand,
                                           tacJoin(tacJumpBack,
                                                   tacLabelAfterQ)))));
}
