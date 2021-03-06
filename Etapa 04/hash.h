#ifndef _HASHH_
#define _HASHH_

#define HASH_SIZE 997

#define SYMBOL_LITINT 1
#define SYMBOL_IDENTIFIER 2
#define SYMBOL_SCALAR 3
#define SYMBOL_VECTOR 4
#define SYMBOL_FUNCTION 5
#define SYMBOL_NOT_DEFINED 6

#define DATATYPE_INT 11
#define DATATYPE_CHAR 12
#define DATATYPE_FLOAT 13
#define DATATYPE_BOOL 14
#define DATATYPE_NOT_DEFINED 15
#define DATATYPE_FUNCTION 16

typedef struct hash_node
{
    int type;
    char *text;
    struct hash_node *next;
    int lineNumber;
    int dataType;
}   HASH_NODE;

HASH_NODE* Table[HASH_SIZE];

void hashInit(void);
int hashAddress(char *text);
HASH_NODE* hashInsert(int type, char *text, int dataType, int lineNumber);
HASH_NODE* hashFind(char *text);
void hashPrint(void);

#endif
