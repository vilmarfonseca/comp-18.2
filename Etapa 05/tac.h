//
//  tac.h
//  
//
//  Created by Vilmar Fonseca on 10/11/18.
//

#ifndef tac_h
#define tac_h

#include "ast.h"
#include "hash.h"
#include "semantic.h"

#define TAC_SYMBOL 1
#define TAC_LABEL 2

/* GLOBAIS */
#define TAC_VAR 10
#define TAC_ARRAY_NAO_DECLARADO 11
#define TAC_ARRAY_DECLARADO 12

/* FUNÇÕES */
#define TAC_RETURN 20
#define TAC_BEGIN_FUNCTION 21
#define TAC_END_FUNCTION 22
#define TAC_ARG 23
#define TAC_CALL 24

/* PRINT, READ, ETC */
#define TAC_READ 30
#define TAC_PRINT 31
#define TAC_INCREMENT 32

/* OPERADORES ARITMÉTICOS */
#define TAC_SUB 40
#define TAC_ADD 41
#define TAC_MULT 42
#define TAC_DIV 43

/* OPERADORES LÓGICOS */
#define TAC_OR 50
#define TAC_AND 51
#define TAC_NE 52
#define TAC_EQ 53
#define TAC_GE 54
#define TAC_LE 55
#define TAC_LESS 57
#define TAC_NOT 58

/* CONTROLE DE FLUXO */
#define TAC_IFZ 60
#define TAC_JUMP 61
#define TAC_FOR 62 // TODO
#define TAC_WHILE 63 // TODO

/* ATRIBUIÇÃO */
#define TAC_ATRIBUICAO 70
#define TAC_ATRIBUICAO_ARRAY 71

typedef struct tac_struct
{
    int type;
    
    HASH_NODE *res;
    HASH_NODE *op1;
    HASH_NODE *op2;
    
    struct tac_struct *next;
    struct tac_struct *prev;
    
} TAC;

TAC *tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
TAC *tacJoin(TAC *tac1, TAC *tac2);
TAC *tacGenerate(AST_NODE *node);
TAC *tacReverse(TAC *last);
void tacPrintPrev(TAC* tacNode);
void tacPrintNext(TAC* tacNode);
void tacPrintNode(TAC *node);

/* OPERAÇÕES */
TAC* makeOperacaoBinaria(int operation, TAC** code);
TAC* makeAtribuicao(HASH_NODE* res, TAC **code);
TAC* makeAtribuicaoArray(HASH_NODE* res, TAC **code);
TAC* makeWhenThen(TAC** code);
TAC* makeWhenThenElse(TAC** code);
TAC* makeReturn(TAC **code);
TAC* makeFnDef(HASH_NODE *identifier, TAC** code);
TAC* makeFnCall(AST_NODE *fnCall);
TAC* makeArgumentos(AST_NODE *args, AST_NODE *expressoes);
TAC* makeVariavel(HASH_NODE *res, TAC **code);
TAC* makeArray(HASH_NODE *res, TAC **code);
TAC* makeArrayInicializado(HASH_NODE *res, TAC **code);
TAC* makeRead(HASH_NODE *identifier);
TAC* makePrint(TAC **code);
TAC* makeForTo(HASH_NODE *res, TAC **code);
TAC* makeWhile(TAC **node);

#endif /* tac_h */
