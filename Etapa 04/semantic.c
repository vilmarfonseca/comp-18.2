#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"

//Headers
void listFuncDeclInsert(LIST_FUNC_DECL** listFuncDecl, AST_NODE* node);
void setSymbolType(AST_NODE *node);
void setDataType(AST_NODE *node);
void checkUndeclaredSymbols();
void checkParams(AST_NODE *funcall_node);
void checkDeclarations(AST_NODE *node);
void checkCorrectUse(AST_NODE *node);
void checkDataTypes(AST_NODE *node);
int checkAttributionTypes(int type1, int type2);
int checkAritmeticOperation(int operator1Type, int operator2Type);
void semanticError(int lineNumber, char message[]);
int checkSemantic(AST_NODE *node);
void checkOperands(AST_NODE *node);

//Declarations
int functionsCount = 0;
int numErrors;
LIST_FUNC_DECL* listFuncDecl = 0; //Inicializa Struct

void listFuncDeclInsert(LIST_FUNC_DECL** listFuncDecl, AST_NODE* node){
    LIST_FUNC_DECL *newNode;
    if(!(newNode = (LIST_FUNC_DECL*) calloc(1, sizeof(LIST_FUNC_DECL))) ){
        fprintf(stderr, "ERROR FUNC_DECL_LIST CREATE: out of memory! \n");
        exit(1);
    }
    
    newNode->ast_node = node;
    newNode->next = 0;
    
    if(*listFuncDecl == 0)
    {
        *listFuncDecl = newNode;
    }
    else
    {
        LIST_FUNC_DECL* temp = *listFuncDecl;
        while(temp->next != 0)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void setSymbolType(AST_NODE *node){
    switch(node->type){
        case AST_ARGUMENT:
            node->symbol->type = SYMBOL_SCALAR; break;
        case AST_VARIABLE:
            node->symbol->type = SYMBOL_SCALAR; break;
        case AST_ARRAY_INIT:
            node->symbol->type = SYMBOL_VECTOR; break;
        case AST_ARRAY_EMPTY:
            node->symbol->type = SYMBOL_VECTOR; break;
        case AST_FUNCTION:
            node->symbol->type = SYMBOL_FUNCTION; break;
        default:
            node->symbol->type = SYMBOL_NOT_DEFINED; break;
    }
}

void setDataType(AST_NODE *node){
    switch(node->sons[0]->type) {
            
        case AST_INT:
            node->symbol->dataType = DATATYPE_INT; break;
        case AST_FLOAT:
            node->symbol->dataType = DATATYPE_FLOAT; break;
        case AST_CHAR:
            node->symbol->dataType = DATATYPE_CHAR; break;
        default:
            node->symbol->dataType = DATATYPE_NOT_DEFINED; break;
    }
}

void checkUndeclaredSymbols() {
    int i;
    HASH_NODE *node;
    
    for(i = 0; i < HASH_SIZE; i++){
        if( (node = Table[i]) ) {
            while(node) {
                if(node->type == SYMBOL_NOT_DEFINED) {
                    semanticError(node->lineNumber, "Undeclared identifier.");
                }
                node = node->next;
            }
        }
    }
}

AST_NODE* findFuncDeclaration(AST_NODE *funcall_node){
    LIST_FUNC_DECL *temp;
    temp = listFuncDecl;
    while(temp != 0)
    {
        if(temp->ast_node->symbol->text == funcall_node->symbol->text)
            return temp->ast_node;
        temp = temp->next;
    }
    return 0;
}

void checkParams(AST_NODE *funcall_node){
    int numberOfParams = 0;
    
    AST_NODE *funcDeclaration = findFuncDeclaration(funcall_node);
    if(!funcDeclaration) {
        semanticError(funcall_node->lineNumber, "Undeclared function.");
        return;
    }
    
    AST_NODE *nodeFuncCall, *nodeFuncDef;
    
    nodeFuncCall = funcall_node->sons[0];
    nodeFuncDef = funcDeclaration->sons[1];
    if(nodeFuncCall && nodeFuncDef){
        while(nodeFuncCall && nodeFuncDef){
            numberOfParams++;
            if(nodeFuncCall->sons[0]->dataType != nodeFuncDef->sons[0]->dataType){
                semanticError(funcall_node->lineNumber, "Function call has type different from its definition.");
            }
            
            nodeFuncDef = nodeFuncDef->sons[1];
            nodeFuncCall = nodeFuncCall->sons[1];
        }
    }
    if(nodeFuncDef){
        semanticError(funcall_node->lineNumber, "Too few arguments to function.");
    }
    if(nodeFuncCall) {
        semanticError(funcall_node->lineNumber, "Too many arguments to function.");
    }
}

void checkDeclarations(AST_NODE *node) {
    
    if(!node) { return; }
    
    if(node->type == AST_VARIABLE || node->type == AST_ARRAY_INIT || node->type == AST_ARRAY_EMPTY || node->type == AST_FUNCTION || node->type == AST_ARGUMENT) {
        if(node->symbol->type != SYMBOL_NOT_DEFINED){
            if(node->symbol->type == SYMBOL_FUNCTION)
                semanticError(node->lineNumber, "Function was already declared.");
            else
                semanticError(node->lineNumber, "Identifier was already declared.");
        }
        setSymbolType(node);
        setDataType(node);
        node->dataType = node->symbol->dataType;
        
        if(node->type == AST_FUNCTION) {
            listFuncDeclInsert(&listFuncDecl, node);
        }
    }
    int i;
    for (i = 0; i < 4; i++) {
        checkDeclarations(node->sons[i]);
    }
}

void checkCorrectUse(AST_NODE *node){
    if(!node) { return; }
    
    switch(node->type) {
        case AST_VARIABLE: // var declaration
            if(node->symbol->type != SYMBOL_SCALAR)
                semanticError(node->lineNumber, "Incorrect use.");
            break;
        case AST_ATTR_SINGLE: // simple attribution
            if(node->symbol->type != SYMBOL_SCALAR)
                semanticError(node->lineNumber, "Incorrect use.");
            break;
        case AST_ATTR_ARRAY: //vector attribution
            if(node->symbol->type != SYMBOL_VECTOR)
                semanticError(node->lineNumber, "Incorrect use.");
            break;
    }
    
    int s;
    for (s = 0; s < 4; s++){
        checkCorrectUse(node->sons[s]);
    }
}

void checkDataTypes(AST_NODE *node){
    if(!node) { return; }
    
    int s;
    for (s = 0; s < 4; s++){
        checkDataTypes(node->sons[s]);
    }
    
    switch(node->type) {
        case AST_LIT_ONLY:
            node->dataType = node->symbol->dataType;
            break;
        case AST_GE:
        case AST_LE:
        case AST_EQ:
        case AST_OR:
        case AST_AND:
        case AST_NOT:
        case AST_LESS:
        case AST_GREATER:
            node->dataType = DATATYPE_INT;
            break;
        case AST_ADD:
        case AST_SUB:
        case AST_MULT:
            node->dataType = checkAritmeticOperation(node->sons[0]->dataType, node->sons[1]->dataType);
            break;
        case AST_DIV:
            node->dataType = DATATYPE_FLOAT;
            break;
        case AST_EXPRESSION_DB:
            node->dataType = node->sons[0]->dataType;
            break;
        case AST_ATTR_SINGLE:
            if(!(verifyAttributionTypes(node->symbol->dataType, node->sons[0]->dataType))){
                semanticError(node->lineNumber, "Attribution type conflict.");
            }
            break;
        case AST_ATTR_ARRAY:
            if(node->sons[0]->dataType != DATATYPE_INT) {
                semanticError(node->lineNumber, "Vector index access - Expected an integer value.");
            }
            if(!(verifyAttributionTypes(node->symbol->dataType, node->sons[1]->dataType))){
                semanticError(node->lineNumber, "Attribution type conflict.");
            }
            break;
        case AST_IF:
            if(node->sons[0]->dataType != DATATYPE_INT){
                semanticError(node->sons[0]->lineNumber, "Command IF - Expected a bool value.");
            }
            break;
    }
}

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
    numErrors = 0;
    
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
    for (i = 0; i<4; i++)
        checkOperands(node->sons[i]);
}
