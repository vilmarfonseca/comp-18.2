%{
#include "hash.h"
#include "ast.h"
#include "y.tab.h"


int lineNumber = 1;
int running = 1;

int isRunning();
int getLineNumber();
void initMe();

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
and	 							{ return OPERATOR_AND; }
not	 							{ return OPERATOR_NOT; }
read 							{ return KW_READ; }
print 							{ return KW_PRINT; }
return							{ return KW_RETURN; }


	/* OPERADORES COMPOSTOS */
\<=								{ return OPERATOR_LE; }
>=								{ return OPERATOR_GE; }   
==								{ return OPERATOR_EQ; }

	/*LITERAIS, ESPECIAIS E IDENTIFICADORES*/
[0-9]*							{ yylval.symbol = hashInsert(SYMBOL_LITINT, yytext, DATATYPE_INT, lineNumber); return LIT_INTEGER; }
\"(\\.|[^"\\])*\"    			{ yylval.symbol = hashInsert(SYMBOL_LITINT, yytext, DATATYPE_CHAR, lineNumber); return LIT_STRING; }
[-,;:dbqp+*\{\}/<>=!&$#]		{ return yytext[0]; }
[-ACE-OR-Zace-or-z_0-9]*		{ yylval.symbol = hashInsert(SYMBOL_NOT_DEFINED, yytext, DATATYPE_NOT_DEFINED, lineNumber); return TK_IDENTIFIER; }
\'[-ACE-OR-Zace-or-z]?\'	    { yylval.symbol = hashInsert(SYMBOL_LITINT, yytext, DATATYPE_CHAR, lineNumber); return LIT_CHAR; }
[0-9]*\.[0-9]*					{ yylval.symbol = hashInsert(SYMBOL_LITINT, yytext, DATATYPE_INT, lineNumber); return LIT_FLOAT; }


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

int getLineNumber(){
	return lineNumber;	
}

int yywrap()
{
	running = 0;
	return 1;
}

int isRunning(){
	return running;
}

void initMe(){
	running = 1;
	lineNumber = 1;
	hashInit();
}
