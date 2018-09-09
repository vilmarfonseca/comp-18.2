%{
    #include "hash.c"
    #include<stdio.h>
    #include<stdlib.h>

    int getLineNumber();
    int yyerror();
    int yylex();
%}

/*--------TOKENS--------*/
%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_WHEN
%token KW_THEN
%token KW_ELSE
%token KW_FOR
%token KW_WHILE
%token KW_RETURN
%token KW_PRINT
%token KW_READ
%token KW_TO
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR
%token <symbol>TK_IDENTIFIER
%token <symbol>LIT_INTEGER
%token <symbol>LIT_CHAR
%token <symbol>LIT_STRING
%token <symbol>LIT_REAL
%token TOKEN_ERROR