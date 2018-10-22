#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

LIST_FUNC_DECL* listFuncDecl = 0; //Inicializa Struct

int numErrors;

//Headers
int checkAttributionTypes(int type1, int type2);
int checkAritmeticOperation(int operator1Type, int operator2Type);
void semanticError(int lineNumber, char message[]);
int checkSemantic(AST_NODE *node);
void checkOperands(AST_NODE *node);

int checkAttributionTypes(int type1, int type2){
    if(type1 == DATATYPE_NOT_DEFINED || type2 == DATATYPE_NOT_DEFINED) {
        return 0;
    } else {
        return 1;
    }
}

int checkAritmeticOperation(int operator1Type, int operator2Type){ //Verifica se os operandos são válidos.
    switch(operator1Type){
        case DATATYPE_CHAR:
            if(operator2Type == DATATYPE_CHAR){ return DATATYPE_CHAR; }
            if(operator2Type == DATATYPE_INT){ return DATATYPE_INT; }
            if(operator2Type == DATATYPE_FLOAT){ return DATATYPE_FLOAT; }
            break;
        case DATATYPE_FLOAT:
            return DATATYPE_FLOAT;
        case DATATYPE_INT:
            if(operator2Type == DATATYPE_CHAR){ return DATATYPE_INT; }
            if(operator2Type == DATATYPE_INT){ return DATATYPE_INT; }
            if(operator2Type == DATATYPE_FLOAT){ return DATATYPE_FLOAT; }
            break;
    }
    return DATATYPE_NOT_DEFINED;
}

void semanticError(int lineNumber, char message[]){
    numErrors++;
    fprintf(stderr, "(SEMANTIC_ERROR) at %i - %s\n", lineNumber, message);

}
int checkSemantic(AST_NODE *node) { //Função que faz a verificação de todos os possíveis erros de sintaxe.
    fprintf(stderr, "\n******* Checking Semantic *******\n");
    numberOfErrors = 0;
    
    checkDeclarations(node);
    checkUndeclaredSymbols();
    checkCorrectUse(node);
    checkDataTypes(node);
    
    return numErrors;
}

void checkOperands(AST_NODE *node){
    int  i;
    
    if (node == 0)
        return;
    for (i = 0; i<MAX_SONS; i++)
        checkOperands(node->son[i]);
}
