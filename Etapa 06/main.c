#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"
#include "semantic.h"
#include "lex.yy.h"
#include "y.tab.h"
#include "tac.h"
#include "genco.h"

extern AST_NODE *root;

int main (int argc, char **argv){
    
	yyin = fopen(argv[1], "r");
	if (argc < 3) 
	{
		fprintf(stderr, "Call: ./a input_file output_file\n");
		exit(1);
	}

	if ((yyin = fopen(argv[1], "r")) == 0)
	{
		fprintf(stderr, "Cannot open file \%s\"\n", argv[1]);
		exit(2);
	}
	
	yyparse();
    
    int semanticErrors = checkSemantic(root);
    
    //printAstNode(root, 0); DEBUG TREE
    
    if(semanticErrors)
    {
        fprintf(stderr, "\nNumber of semantic erros: %d!\n\n", semanticErrors);
        //exit(4);
    }
    
	FILE* output = fopen(argv[2], "w");
	FILE* output2 = stdout;

	if(!output){
		fprintf(stderr, "Cannot open file \%s\"\n", argv[2]);
		exit(3);
	}


	printAst(root, output2);
	fprintf(stderr, "Success generating code.\n");
    TAC *tac = tacGenerate(root);
	TAC *invertedTac = tacReverse(tac);
    tacPrintNext(invertedTac);

    fprintf(stderr, "\nWriting Assembly code...\n\n");
	tac_to_asm(invertedTac, output);
	fclose(yyin);
	fclose(output);
	fclose(output2);
    fprintf(stderr, "\nWriting Assembly code finished!!\n");
	

	exit(0);

}
