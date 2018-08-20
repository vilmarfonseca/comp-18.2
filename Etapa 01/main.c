
int main (int argc, char **argv){
    
    int tok;

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

        switch(tok){
			case KW_INT:
				fprintf(stderr, "Found KW_INT - line %i\n", getLineNumber());
				break;
			case KW_FLOAT:
				fprintf(stderr, "Found KW_FLOAT - line %i\n", getLineNumber());
				break;
			case KW_CHAR:
				fprintf(stderr, "Found KW_CHAR - line %i\n", getLineNumber());
				break;
			case KW_IF:
				fprintf(stderr, "Found KW_IF - line %i\n", getLineNumber());
				break;
			case KW_THEN:
				fprintf(stderr, "Found KW_THEN - line %i\n", getLineNumber());
				break;
			case KW_ELSE:
				fprintf(stderr, "Found KW_ELSE - line %i\n", getLineNumber());
				break;
			case KW_WHILE:
				fprintf(stderr, "Found KW_WHILE - line %i\n", getLineNumber());
				break;
			case KW_READ:
				fprintf(stderr, "Found KW_READ - line %i\n", getLineNumber());
				break;
			case KW_PRINT:
				fprintf(stderr, "Found KW_PRINT - line %i\n", getLineNumber());
				break;
			case KW_RETURN:
				fprintf(stderr, "Found KW_RETURN - line %i\n", getLineNumber());
				break;
			case OPERATOR_LE:
				fprintf(stderr, "Found OPERATOR_LE - line %i\n", getLineNumber());
				break;
			case OPERATOR_GE:
				fprintf(stderr, "Found OPERATOR_GE - line %i\n", getLineNumber());
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "Found OPERATOR_EQ - line %i\n", getLineNumber());
				break;
			case OPERATOR_AND:
				fprintf(stderr, "Found OPERATOR_AND - line %i\n", getLineNumber());
				break;
			case OPERATOR_OR:
				fprintf(stderr, "Found OPERATOR_OR - line %i\n", getLineNumber());
				break;
			case OPERATOR_NOT:
				fprintf(stderr, "Found OPERATOR_NOT - line %i\n", getLineNumber());
				break;
			case LIT_INTEGER:
				fprintf(stderr, "Found LIT_INTEGER - line %i\n", getLineNumber());
				break;
			case LIT_FLOAT:
				fprintf(stderr, "Found LIT_FLOAT - line %i\n", getLineNumber());
				break;
			case LIT_CHAR:
				fprintf(stderr, "Found LIT_CHAR - line %i\n", getLineNumber());
				break;
			case LIT_STRING:
				fprintf(stderr, "Found LIT_STRING - line %i\n", getLineNumber());
				break;
			case TK_IDENTIFIER:
				fprintf(stderr, "Found TK_IDENTIFIER - line %i\n", getLineNumber());
				break;
			case TOKEN_ERROR:
				fprintf(stderr, "Found TOKEN_ERROR - line %i\n", getLineNumber());
				break;
			default:
				fprintf(stderr, "Found %c - line %i\n", tok, getLineNumber());
				break;
		}
    }
	
	hashPrint();
	
	return 1;

}