#ifndef _HASHH_
#define _HASHH_

#define HASH_SIZE 997
#define SYMBOL_IDENTIFIER 1
#define SYMBOL_LIT_INTEGER 2
#define SYMBOL_LIT_CHAR 3
#define SYMBOL_LIT_STRING 4
#define SYMBOL_LIT_FLOAT 5

typedef struct hash_node
{
    int type;
    char *text;
    struct hash_node *next;
}   HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE* hashInsert(int type, char *text);
HASH_NODE* hashFind(char *text);
void hashPrint(void);

#endif