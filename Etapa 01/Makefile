scanner: lex.yy.o hash.o
	gcc lex.yy.o hash.o -o scanner

hash.o: hash.c
	gcc -c hash.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: LexScanner.input
	lex --header-file=lex.yy.h LexScanner.input

clean:
	rm scanner
	rm lex.yy.c lex.yy.h
	rm *.o


	