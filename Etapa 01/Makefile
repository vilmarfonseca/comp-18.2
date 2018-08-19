myscanner: hash.c hash.h tokens.h lex.yy.c
	cc hash.c lex.yy.c -ll -o myscanner 

lex.yy.c: LexScanner.input
	lex LexScanner.input

clean:
	rm myscanner
	rm lex.yy.c