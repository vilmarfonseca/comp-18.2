%{
    #include "hash.c"
    #include<stdio.h>
    #include<stdlib.h>

    int getLineNumber();
    int yyerror();
    int yylex();
%}

/*--------TOKENS--------*/
%token KW_CHAR       
%token KW_INT        
%token KW_FLOAT      
%token KW_IF         
%token KW_THEN       
%token KW_ELSE       
%token KW_WHILE      
%token KW_READ       
%token KW_RETURN     
%token KW_PRINT      
%token OPERATOR_LE   
%token OPERATOR_GE   
%token OPERATOR_EQ   
%token OPERATOR_OR   
%token OPERATOR_AND  
%token OPERATOR_NOT  
%token TK_IDENTIFIER 
%token LIT_INTEGER   
%token LIT_FLOAT     
%token LIT_CHAR      
%token LIT_STRING    
%token TOKEN_ERROR 

/* PROGRAM - declaring of functions or variables/globals */

/*VARIABLE: type name '=' init_value*/
variavel:
		 type TK_IDENTIFIER '=' literal
		 ;

array:
	type TK_IDENTIFIER 'q'LIT_INTEGER'p'|
	type TK_IDENTIFIER 'q'LIT_INTEGER'p' : literal_sequence
	;


/*FUNCTION:*/
function:
	type TK_IDENTIFIER 'd'argument_list'b' block |
	type TK_IDENTIFIER 'd' 'b' block
	;

argument_list:
	argument |
	argument ',' argument_list
	;

argument:
	type TK_IDENTIFIER
	;

/*TYPES:*/
type:
	KW_CHAR |
	KW_INT |
	KW_FLOAT
	; 

/*LITERALS:*/
literal:
	LIT_INTEGER |
	LIT_FLOAT |
	LIT_CHAR |
	LIT_STRING
	;

literal_sequence:
	literal |
	literal literal_sequence
	;