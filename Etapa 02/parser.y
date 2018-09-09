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
%token <symbol>TK_IDENTIFIER 
%token <symbol>LIT_INTEGER   
%token <symbol>LIT_FLOAT     
%token <symbol>LIT_CHAR      
%token <symbol>LIT_STRING    
%token TOKEN_ERROR 


%union {HASH_NODE *symbol;}


%%

/*PROGRAM*/
program:
	declaration |
	program declaration
	;

declaration: 
	function |
	global';'
	;

global: 
	variable |
	array
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

/*VARIABLE: type name '=' init_value*/
variable:
		 type TK_IDENTIFIER '=' literal
		 ;

array:
	type TK_IDENTIFIER 'q'LIT_INTEGER'p'|
	type TK_IDENTIFIER 'q'LIT_INTEGER'p' literal_sequence
	;

/*COMANDOS*/
command:
	block|
	attribution|
	flow_control|
	read|
	print|
	return|
	/*empty*/
	;

/*BLOCO DE COMANDOS*/
block:
	'{' '}'|
	'{' command_sequence '}'
	;

command_sequence:
	command ';' command_sequence |
	/*empty*/
	;

/*COMMANDS DEFINITION*/
attribution:
	TK_IDENTIFIER '=' expression |
	TK_IDENTIFIER 'q' expression 'p' '=' expression
	;

flow_control:
	command_if|
	command_if_else|
	command_while
	;

command_if:
	KW_IF expression KW_THEN command
	;

command_if_else:
	KW_IF expression KW_THEN command KW_ELSE command
	;

command_while:
	KW_WHILE expression command
	;

read:
	KW_READ TK_IDENTIFIER
	;

print:
	KW_PRINT printable_list
	;

return:
	KW_RETURN expression
	;

printable_list:
	expression ',' list_expressions |
	expression
	;

list_expressions:
	expression |
	/*empty*/
	;

/*EXPRESSIONS*/
expression:
	TK_IDENTIFIER |
	TK_IDENTIFIER 'q' expression 'p' |
	literal |
	expression OPERATOR_LE expression |  
 	expression OPERATOR_GE expression |
 	expression OPERATOR_EQ expression |
 	expression OPERATOR_OR expression |   
	expression OPERATOR_AND expression | 
	expression OPERATOR_NOT expression | 
	expression '<' expression |
	expression '+' expression |
	expression '-' expression |
	expression '*' expression |
	expression '/' expression |
	expression '>' expression |
	function
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

%%

int yyerror() 
{	 
	fprintf(stderr, "Syntax error at line: %d.\n", getLineNumber());
	exit(3);
}