
int main (int argc, char **argv){
    
    int tok = 0;

	if (argc < 2) 
	{
		fprintf(stderr, "Call: a.out file_name\n");
		exit(1);
	}

	if ((yyin = fopen(argv[1], "r")) == 0)
	{
		fprintf(stderr, "Cannot open file \%s\"\n", argv[1]);
		exit(2);
	}	

	
	initMe();

	if (!yyparse()){
		fprintf(stderr, "\n*********************************************");
		fprintf(stderr, "\n           This syntax is correct!           \n");
		fprintf(stderr, "*********************************************\n");
	}
		
	else{
		fprintf(stderr, "\n*********************************************");
		fprintf(stderr, "\n           Parsing Error on line: %d         \n", getLineNumber());
		fprintf(stderr, "*********************************************\n");
	}


	printf("\n-----------------------HASH TABLE-----------------------\n");
	
	hashPrint();

	printf("-----------------------END HASH TABLE-----------------------\n");
	
	running = 0;
	return 1;

}