/*
 * created by Hermes Tessaro
*/

 #ifndef(GENCO_H)
 #define GENCO_H

 #include <stdio.h>
 #include <stdlib.h>
 #include "tac.h"
 #include "hash.h"
 #include "ast.h"


void gencoVarDecl(FILE* output, TAC *tac);
void gencoLongLiteralDeclaration(FILE *output, HASH_NODE *hashNode, TAC* tac);
void gencoByteLiteralDeclaration(FILE *output, HASH_NODE *hashNode, TAC* tac);

void gencoArrayDeclaration(FILE* output, TAC *tac);
void gencoByteArrayDeclaration(FILE *output, HASH_NODE *hashNode, TAC *tac);
void gencoLongArrayDeclaration(FILE* output, TAC *tac);

void initTempVar(FILE *output);
void initParamVar(FILE *output);
void tac_to_asm(TAC* node, FILE* output);

#endif