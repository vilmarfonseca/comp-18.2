%{

#include "hash.c"
#include "tokens.h"

int lineNumber = 1;
int running = 1;

int isRunning();
int getLineNumber();
int init();

%}

%x COMMENT

%%

	/* PALAVRAS RESERVADAS DA LINGUAGEM */
char 							{ return KW_CHAR; }
int  	 						{ return KW_INT; }
float 							{ return KW_FLOAT; }	
if								{ return KW_IF; }
then							{ return KW_THEN; }
else							{ return KW_ELSE; }
while							{ return KW_WHILE; }
or								{ return OPERATOR_OR; } 
and 							{ return OPERATOR_AND; }
not 							{ return OPERATOR_NOT; }
read 							{ return KW_READ; }
print 							{ return KW_PRINT; }
return							{ return KW_RETURN; }


	/* OPERADORES COMPOSTOS */
\<=								{ return OPERATOR_LE; }
>=								{ return OPERATOR_GE; }   
==								{ return OPERATOR_EQ; }

	/*LITERAIS E IDENTIFICADORES*/
([-A-Za-z_]|"]")[-A-Za-z_0-9]*	{ hashInsert(TK_IDENTIFIER, yytext); return TK_IDENTIFIER; }
[0-9]+							{ hashInsert(LIT_INTEGER, yytext); return LIT_INTEGER; }
\'.\' 							{ hashInsert(LIT_CHAR, yytext); return LIT_CHAR; }
\"([^\"\\\n]|\\.)*\" 			{ hashInsert(LIT_STRING, yytext); return LIT_STRING; }
[0-9]+\.[0-9]+					{ hashInsert(LIT_FLOAT, yytext); return LIT_FLOAT; }
	
	/* CARACTERES ESPECIAIS */
[,;:dbqp{}+=*/<>=!&$#]			{ return yytext[0]; }

	/* COMENTÁRIOS, NOVA LINHA E TABULAÇÃO */
"//".*							{ }
"/*"							{ BEGIN(COMMENT); }
<COMMENT>"\n"					{ lineNumber++; }
<COMMENT>"*/"					{ BEGIN(INITIAL); }
<COMMENT>.						{ }
[ \t]							{ }
"\n"							{ lineNumber++; }	
.	                        	{ return TOKEN_ERROR; }

%%
#include <stdio.h>
#include "main.c"

int getLineNumber(){
	return lineNumber;	
}


int isRunning(){
	return running;
}

int init()
{
	running = 1;
	lineNumber = 1;
	hashInit();

	return 0;
}

int yywrap()
{
    running = 0;
	return 1;
}

