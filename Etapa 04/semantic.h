#ifndef semantic_h
#define semantic_h

#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"

void setDeclaration(AST_NODE *node);
void checkUndeclared();
void checkOperands(AST_NODE *node);

#endif /* semantic_h */
