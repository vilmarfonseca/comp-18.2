
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

	init();
	
    while(isRunning()){

        tok = yylex();
		if(!isRunning())
			break;

        switch(tok){
			case KW_INT:
				fprintf(stderr, "Found KW_INT on line %i\n", getLineNumber());
				break;
			case KW_FLOAT:
				fprintf(stderr, "Found KW_FLOAT on line %i\n", getLineNumber());
				break;
			case KW_CHAR:
				fprintf(stderr, "Found KW_CHAR on line %i\n", getLineNumber());
				break;
			case KW_IF:
				fprintf(stderr, "Found KW_IF on line %i\n", getLineNumber());
				break;
			case KW_THEN:
				fprintf(stderr, "Found KW_THEN on line %i\n", getLineNumber());
				break;
			case KW_ELSE:
				fprintf(stderr, "Found KW_ELSE on line %i\n", getLineNumber());
				break;
			case KW_WHILE:
				fprintf(stderr, "Found KW_WHILE on line %i\n", getLineNumber());
				break;
			case KW_READ:
				fprintf(stderr, "Found KW_READ on line %i\n", getLineNumber());
				break;
			case KW_PRINT:
				fprintf(stderr, "Found KW_PRINT on line %i\n", getLineNumber());
				break;
			case KW_RETURN:
				fprintf(stderr, "Found KW_RETURN on line %i\n", getLineNumber());
				break;
			case OPERATOR_LE:
				fprintf(stderr, "Found OPERATOR_LE on line %i\n", getLineNumber());
				break;
			case OPERATOR_GE:
				fprintf(stderr, "Found OPERATOR_GE on line %i\n", getLineNumber());
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "Found OPERATOR_EQ on line %i\n", getLineNumber());
				break;
			case OPERATOR_AND:
				fprintf(stderr, "Found OPERATOR_AND on line %i\n", getLineNumber());
				break;
			case OPERATOR_OR:
				fprintf(stderr, "Found OPERATOR_OR on line %i\n", getLineNumber());
				break;
			case OPERATOR_NOT:
				fprintf(stderr, "Found OPERATOR_NOT on line %i\n", getLineNumber());
				break;
			case LIT_INTEGER:
				fprintf(stderr, "Found LIT_INTEGER on line %i\n", getLineNumber());
				break;
			case LIT_FLOAT:
				fprintf(stderr, "Found LIT_FLOAT on line %i\n", getLineNumber());
				break;
			case LIT_CHAR:
				fprintf(stderr, "Found LIT_CHAR on line %i\n", getLineNumber());
				break;
			case LIT_STRING:
				fprintf(stderr, "Found LIT_STRING on line %i\n", getLineNumber());
				break;
			case TK_IDENTIFIER:
				fprintf(stderr, "Found TK_IDENTIFIER on line %i\n", getLineNumber());
				break;
			case TOKEN_ERROR:
				fprintf(stderr, "Found TOKEN_ERROR on line %i\n", getLineNumber());
				break;
			default:
				fprintf(stderr, "Found %c on line %i\n", tok, getLineNumber());
				break;
		}
    }

	printf("\n\n-----------------------HASH TABLE-----------------------\n");
	
	hashPrint();
	
	running = 0;
	return 1;

}