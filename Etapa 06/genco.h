/*
 * created by Hermes Tessaro
*/

 #ifndef _GENCO_H_
 #define _GENCO_H_

 #include <stdio.h>
 #include <stdlib.h>
 #include "tac.h"
 #include "hash.h"
 #include "ast.h"


void gencoVarDecl(FILE* output, TAC *tac);
void gencoLongLiteralDecl(FILE *output, HASH_NODE *hashNode, TAC* tac);
void gencoByteLiteralDecl(FILE *output, HASH_NODE *hashNode, TAC* tac);
void gencoArrayDecl(FILE* output, TAC *tac);
void gencoByteArrayDecl(FILE *output, HASH_NODE *hashNode, TAC *tac);
void gencoLongArrayDecl(FILE* output, TAC *tac);
void gencoNumOp(TAC* tac, FILE* output);
void initTempVar(FILE *output);
void initParamVar(FILE *output);
void tac_to_asm(TAC* node, FILE* output);

#endif