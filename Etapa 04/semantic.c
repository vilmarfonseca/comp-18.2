#include <stdio.h>
#include <stdlib.h>
#include "semantic.h"


void checkOperands(AST_NODE *node){
    int  i;
    
    if (node == 0)
        return;
    for (i = 0; i<MAX_SONS; i++)
        checkOperands(node->son[i]);
}
