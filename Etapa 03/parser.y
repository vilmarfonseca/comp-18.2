%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "hash.h"
    #include "ast.h"

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

%start root
%right '='
%left OPERATOR_NOT OPERATOR_AND OPERATOR_OR
%left OPERATOR_EQ OPERATOR_GE OPERATOR_LE '>' '<'
%left '+' '-'
%left '*' '/'
%right KW_IF KW_THEN KW_ELSE

%type<ast> program declaration global variable array function argument_list argument type literal literal_sequence command
%type<ast> block command_sequence attribution flow_control command_if command_if_else command_while read print return list_expressions expression

%union 
{
	HASH_NODE *symbol; 
	AST_NODE *ast;
}



%%



root: 	program 	{ root = $1; }
		;


/*PROGRAM*/
program:
	declaration 				{ $$ = initAst(AST_PROGRAM, 0, $1, 0, 0, 0); } |
	program declaration			{ $$ = initAst(AST_PROGRAM, 0, $1, $2, 0, 0); } 
	;

declaration: 
	function 					{ $$ = $1; }  |
	global';'					{ $$ = $1; }
	;

global: 
	variable 					{ $$ = $1; }  |
	array						{ $$ = $1; }
	;

function:
	type TK_IDENTIFIER 'd'argument_list'b' command 	{ $$ = initAst(AST_FUNCTION, $2, $1, $4, $6, 0); }	|
	type TK_IDENTIFIER 'd' 'b' command  		 	{ $$ = initAst(AST_FUNCTION, $2, $1, $5, 0, 0); }	
	;

argument_list:
	argument						{ $$ = initAst(AST_ARG_LIST, 0, $1, 0, 0, 0); }	|
	argument ',' argument_list		{ $$ = initAst(AST_ARG_LIST, 0, $1, $3, 0, 0); }
	;

argument:
	type TK_IDENTIFIER				{ $$ = initAst(AST_ARGUMENT, $2, $1, 0, 0, 0); }
	;

variable:
	type TK_IDENTIFIER '=' literal  { $$ = initAst(AST_VARIABLE, $2, $1, $4, 0, 0); }
	;

array:
	type TK_IDENTIFIER 'q'literal'p'  		{ $$ = initAst(AST_ARRAY_EMPTY, $2, $1, $4, 0, 0); } |
	type TK_IDENTIFIER 'q'literal'p' ':' literal_sequence  { $$ = initAst(AST_ARRAY_INIT, $2, $1, $4, $7, 0); }
	;

type:
	KW_CHAR 			{ $$ = initAst(AST_CHAR, 0, 0, 0, 0, 0); }	|
	KW_INT 				{ $$ = initAst(AST_INT, 0, 0, 0, 0, 0); }	 |
	KW_FLOAT 			{ $$ = initAst(AST_FLOAT, 0, 0, 0, 0, 0); }	
	; 

literal:
	LIT_INTEGER 		 { $$ = initAst(AST_IDENTIFIER, $1, 0, 0, 0, 0); }	|
	LIT_FLOAT 		 	 { $$ = initAst(AST_IDENTIFIER, $1, 0, 0, 0, 0); }	|
	LIT_CHAR 		 	 { $$ = initAst(AST_IDENTIFIER, $1, 0, 0, 0, 0); }	|
	LIT_STRING 		 	 { $$ = initAst(AST_IDENTIFIER, $1, 0, 0, 0, 0); }	
	;


literal_sequence:
	literal 			 	  { $$ = initAst(AST_LIT_ONLY, 0, $1, 0, 0, 0); } |
	literal literal_sequence  { $$ = initAst(AST_LIT_SEQUENCE, 0, $1, $2, 0, 0); }
	;

command:
	block					  { $$ = initAst(AST_COMMAND, 0, $1, 0, 0, 0); }|
	attribution				  { $$ = initAst(AST_COMMAND, 0, $1, 0, 0, 0); }|
	flow_control			  { $$ = initAst(AST_COMMAND, 0, $1, 0, 0, 0); }|
	read					  { $$ = initAst(AST_COMMAND, 0, $1, 0, 0, 0); }|
	print					  { $$ = initAst(AST_COMMAND, 0, $1, 0, 0, 0); }|
	return					  { $$ = initAst(AST_COMMAND, 0, $1, 0, 0, 0); }|
	/*empty*/				  { $$ = 0; }
	;

block:
	'{' '}'					 	 { $$ = 0; }|
	'{' command_sequence '}'     { $$ = initAst(AST_COMMAND_BLOCK, 0, $2, 0, 0, 0);}
	;

command_sequence:
	command ';' command_sequence	  { $$ = initAst(AST_COMMAND_SEQUENCE, 0, $1, $3, 0, 0); }|
	/*empty*/						  { $$ = 0; }
	;

attribution:
	TK_IDENTIFIER '=' expression 					{ $$ = initAst(AST_ATTR_SINGLE, $1, $3, 0, 0, 0); }|
	TK_IDENTIFIER 'q' expression 'p' '=' expression { $$ = initAst(AST_ATTR_ARRAY, $1, $3, $6, 0, 0); }
	;

flow_control:
	command_if 				{ $$ = $1; } |
	command_if_else 		{ $$ = $1; } |
	command_while 			{ $$ = $1; } 
	;

command_if:
	KW_IF expression KW_THEN command 	{ $$ = initAst(AST_IF, 0, $2, $4, 0, 0); }
	;

command_if_else:
	KW_IF expression KW_THEN command KW_ELSE command  { $$ = initAst(AST_IF_ELSE, 0, $2, $4, $6, 0); }
	;

command_while:
	KW_WHILE expression command 	{ $$ = initAst(AST_WHILE, 0, $2, $3, 0, 0); }
	;

read:
	KW_READ TK_IDENTIFIER			{ $$ = initAst(AST_READ, $2, 0, 0, 0, 0); }
	;

print:
	KW_PRINT list_expressions 		{ $$ = initAst(AST_PRINT, 0, $2, 0, 0, 0); }
	;

return:
	KW_RETURN expression 			{ $$ = initAst(AST_RETURN, 0, $2, 0, 0, 0); }
	;


list_expressions:
	expression 								{ $$ = initAst(AST_EXPRESSION_LIST, 0, $1, 0, 0, 0); } |
	expression ',' list_expressions 		{ $$ = initAst(AST_EXPRESSION_LIST, 0, $1, $3, 0, 0); }|
	/*empty*/								{ $$ = 0; }
	;

expression:
	TK_IDENTIFIER 							{ $$ = initAst(AST_EXPRESSION_ID, $1, 0, 0, 0, 0); } |
	TK_IDENTIFIER 'q' expression 'p' 		{ $$ = initAst(AST_EXPRESSION_FUNCTION, $1, $3, 0, 0, 0); } |
	TK_IDENTIFIER 'd' 'b' 					{ $$ = initAst(AST_EXPRESSION_DB_EMPTY, $1, 0, 0, 0, 0); } |
	TK_IDENTIFIER 'd'list_expressions'b'	{ $$ = initAst(AST_EXPRESSION_LIST, $1, $3, 0, 0, 0); } |
	literal 								{ $$ = $1; } |
	expression OPERATOR_LE expression 		{ $$ = initAst(AST_LE, 0, $1, $3, 0, 0); } |  
 	expression OPERATOR_GE expression 		{ $$ = initAst(AST_GE, 0, $1, $3, 0, 0); } |
 	expression OPERATOR_EQ expression 		{ $$ = initAst(AST_EQ, 0, $1, $3, 0, 0); } |
 	expression OPERATOR_OR expression 		{ $$ = initAst(AST_OR, 0, $1, $3, 0, 0); } |   
	expression OPERATOR_AND expression 		{ $$ = initAst(AST_AND, 0, $1, $3, 0, 0); } | 
	expression OPERATOR_NOT expression 		{ $$ = initAst(AST_NOT, 0, $1, $3, 0, 0); } | 
	expression '<' expression 				{ $$ = initAst(AST_LESS, 0, $1, $3, 0, 0); } |
	expression '+' expression 				{ $$ = initAst(AST_ADD, 0, $1, $3, 0, 0); } |
	expression '-' expression 				{ $$ = initAst(AST_SUB, 0, $1, $3, 0, 0); } |
	expression '*' expression 				{ $$ = initAst(AST_MULT, 0, $1, $3, 0, 0); } |
	expression '/' expression 				{ $$ = initAst(AST_DIV, 0, $1, $3, 0, 0); } |
	expression '>' expression 				{ $$ = initAst(AST_GREATER, 0, $1, $3, 0, 0); } |
	'd' expression 'b'						{ $$ = initAst(AST_EXPRESSION_DB, 0, $2, 0, 0, 0); } 
	;

%%

int yyerror() 
{	 
	fprintf(stderr, "Syntax error at line: %d.\n", getLineNumber());
	exit(3);
}
