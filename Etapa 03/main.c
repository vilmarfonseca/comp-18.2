#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "ast.h"
#include "lex.yy.h"
#include "y.tab.h"

extern AST_NODE *root;

int main (int argc, char **argv){
    

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
	FILE* output = fopen(argv[2], "w");

	if(!output){
		fprintf(stderr, "Cannot open file \%s\"\n", argv[2]);
		exit(3);
	}

	printAst(root, output);
	fprintf(stderr, "Finished.\n");
	fclose(output);

	exit(0);

}
