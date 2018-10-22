#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

LIST_FUNC_DECL* listFuncDecl = 0; //Inicializa Struct

int numErrors;

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
