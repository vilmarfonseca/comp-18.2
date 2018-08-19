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

    while(isRunning()){
        tok = yylex();

        switch(tok){
			case KW_INT:
				fprintf(stderr, "Found KW_INT - line %i\n", lineNumber);
				break;
			case KW_FLOAT:
				fprintf(stderr, "Found KW_FLOAT - line %i\n", lineNumber);
				break;
			case KW_CHAR:
				fprintf(stderr, "Found KW_CHAR - line %i\n", lineNumber);
				break;
			case KW_IF:
				fprintf(stderr, "Found KW_IF - line %i\n", lineNumber);
				break;
			case KW_THEN:
				fprintf(stderr, "Found KW_THEN - line %i\n", lineNumber);
				break;
			case KW_ELSE:
				fprintf(stderr, "Found KW_ELSE - line %i\n", lineNumber);
				break;
			case KW_READ:
				fprintf(stderr, "Found KW_READ - line %i\n", lineNumber);
				break;
			case KW_PRINT:
				fprintf(stderr, "Found KW_PRINT - line %i\n", lineNumber);
				break;
			case KW_RETURN:
				fprintf(stderr, "Found KW_RETURN - line %i\n", lineNumber);
				break;
			case OPERATOR_LE:
				fprintf(stderr, "Found OPERATOR_LE - line %i\n", lineNumber);
				break;
			case OPERATOR_GE:
				fprintf(stderr, "Found OPERATOR_GE - line %i\n", lineNumber);
				break;
			case OPERATOR_EQ:
				fprintf(stderr, "Found OPERATOR_EQ - line %i\n", lineNumber);
				break;
			case OPERATOR_AND:
				fprintf(stderr, "Found OPERATOR_AND - line %i\n", lineNumber);
				break;
			case OPERATOR_OR:
				fprintf(stderr, "Found OPERATOR_OR - line %i\n", lineNumber);
				break;
			case LIT_INTEGER:
				fprintf(stderr, "Found LIT_INTEGER - line %i\n", lineNumber);
				#ifdef DEBUG
                debug_hashPrint();
                #endif // DEBUG
				break;

			case LIT_CHAR:
				fprintf(stderr, "Found LIT_CHAR - line %i\n", lineNumber);
				#ifdef DEBUG
                debug_hashPrint();
                #endif // DEBUG
				break;

			case LIT_STRING:
				fprintf(stderr, "Found LIT_STRING - line %i\n", lineNumber);
				#ifdef DEBUG
                debug_hashPrint();
                #endif // DEBUG
				break;

			case TK_IDENTIFIER:
				fprintf(stderr, "Found TK_IDENTIFIER - line %i\n", lineNumber);
				#ifdef DEBUG
                debug_hashPrint();
                #endif // DEBUG
				break;

			case TOKEN_ERROR:
				fprintf(stderr, "Found TOKEN_ERROR - line %i\n", lineNumber);
				break;
			default:
				fprintf(stderr, "Found %c - line %i\n", tok, lineNumber);
				break;
		}
    }
	exit(0);

}