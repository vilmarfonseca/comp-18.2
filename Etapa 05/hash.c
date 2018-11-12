#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"
#include "y.tab.h"

HASH_NODE* Table[HASH_SIZE];

void hashInit(void){
    int i;
    for(i = 0; i < HASH_SIZE; i++){
        Table[i] = 0;
    }
}

int hashAddress(char *text){
    int i = 0;
    int address = 1;
    for(i = 0; i < strlen(text); i++){
        address = (address * text[i]) % HASH_SIZE + 1;
    }
    return address - 1;
}

HASH_NODE* hashInsert(int type, char* text, int dataType, int lineNumber) {
    int address;
    HASH_NODE *newNode;
    address = hashAddress(text);
    
    if((newNode = hashFind(text))){
        return newNode;
    }
    newNode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    newNode->type = type;
    newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));
    newNode->lineNumber = lineNumber;
    newNode->dataType = dataType;
    strcpy(newNode->text, text);
    newNode->next = Table[address];
    Table[address] = newNode;
    return newNode;
}
HASH_NODE* hashFind(char *text){
    int address;
    HASH_NODE*node;
    address = hashAddress(text);
    for (node = Table[address]; node ; node = node->next){
        if(!strcmp(text, node->text)){
            return node;
        }
    }
    return 0;
}
void hashPrint(void) {
    int i= 0;
    HASH_NODE * node;
    for(i = 0; i < HASH_SIZE; i++){
        for(node = Table[i]; node; node = node->next){
            fprintf(stderr, "Table %d has %s\n", i, node->text);
        }
    }
}

HASH_NODE *makeTemp(void)
{
    static int serialNumber = 0;
    static char buffer[128];
    sprintf(buffer, "_temp_%d", serialNumber++);
    return hashInsert(SYMBOL_LITINT, buffer, 0, 0);
}

HASH_NODE *makeLabel(void)
{
    static int serialNumber = 0;
    static char buffer[128];
    sprintf(buffer, "_label_%d", serialNumber++);
    return hashInsert(SYMBOL_LABEL, buffer, 0, 0);
}

HASH_NODE *makeLabelArray(HASH_NODE *node)
{
    static char buffer[256];
    sprintf(buffer, "_arrayLabel_%s", node->text);
    return hashInsert(SYMBOL_LABEL, buffer, 0, 0);
}
