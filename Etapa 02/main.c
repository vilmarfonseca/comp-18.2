
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
	
    while(isRunning()){

        tok = yylex();
		if(!isRunning())
			break;

        switch(tok){
			case KW_INT:
				fprintf(stderr, "Found KW_INT (Token:%d) on line %i\n",	tok, getLineNumber());
				break;
			case KW_FLOAT:
				fprintf(stderr, "Found KW_FLOAT (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case KW_CHAR:
				fprintf(stderr, "Found KW_CHAR (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case KW_IF:
				fprintf(stderr, "Found KW_IF (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case KW_THEN:
				fprintf(stderr, "Found KW_THEN (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case KW_ELSE:
				fprintf(stderr, "Found KW_ELSE (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case KW_WHILE:
				fprintf(stderr, "Found KW_WHILE (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case KW_READ:
				fprintf(stderr, "Found KW_READ (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case KW_PRINT:
				fprintf(stderr, "Found KW_PRINT (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case KW_RETURN:
				fprintf(stderr, "Found KW_RETURN (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case OPERATOR_LE:
				fprintf(stderr, "Found OPERATOR_LE (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case OPERATOR_GE:
				fprintf(stderr, "Found OPERATOR_GE (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "Found OPERATOR_EQ (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case OPERATOR_AND:
				fprintf(stderr, "Found OPERATOR_AND (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case OPERATOR_OR:
				fprintf(stderr, "Found OPERATOR_OR (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case OPERATOR_NOT:
				fprintf(stderr, "Found OPERATOR_NOT (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case LIT_INTEGER:
				fprintf(stderr, "Found LIT_INTEGER (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case LIT_FLOAT:
				fprintf(stderr, "Found LIT_FLOAT (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case LIT_CHAR:
				fprintf(stderr, "Found LIT_CHAR (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case LIT_STRING:
				fprintf(stderr, "Found LIT_STRING (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case TK_IDENTIFIER:
				fprintf(stderr, "Found TK_IDENTIFIER (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			case TOKEN_ERROR:
				fprintf(stderr, "Found TOKEN_ERROR (Token:%d) on line %i\n", tok, getLineNumber());
				break;
			default:
				fprintf(stderr, "Found %c (ASCII: %d) on line %i\n", tok, tok, getLineNumber());
				break;
		}
    }

	printf("\n-----------------------HASH TABLE-----------------------\n");
	
	hashPrint();

	printf("-----------------------END HASH TABLE-----------------------\n");
	
	running = 0;
	return 1;

}