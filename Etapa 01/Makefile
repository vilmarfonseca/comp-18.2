scanner: lex.yy.c
	gcc -o scanner lex.yy.c

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm scanner lex.yy.c