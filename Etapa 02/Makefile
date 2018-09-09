etapa2: y.tab.c lex.yy.c main.c
	gcc -o etapa2 lex.yy.c

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l y.tab.c
	lex  scanner.l

clean:
	rm -f *.o etapa2 lex.yy.c lex.yy.h y.tab.c y.tab.h