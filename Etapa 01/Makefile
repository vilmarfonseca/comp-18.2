myscanner: LexScanner.c tokens.h lex.yy.c
	cc LexScanner.c lex.yy.c -ll -o myscanner 

lex.yy.c: LexScanner.input
	lex LexScanner.input

clean:
	rm myscanner
	rm lex.yy.c