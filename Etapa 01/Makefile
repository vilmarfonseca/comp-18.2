scanner: lex.yy.o hash.o
	gcc lex.yy.o hash.o -o scanner

hash.o: hash.c
	gcc -c hash.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

clean:
	rm scanner
	rm lex.yy.c lex.yy.h
	rm *.o


	