etapa5: y.tab.o lex.yy.o hash.o ast.o semantic.o main.o tac.o
	gcc lex.yy.o hash.o ast.o semantic.o main.o y.tab.o tac.o -o etapa5

main.o: main.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

semantic.o: semantic.c
	gcc -c semantic.c

y.tab.o: y.tab.c
	gcc -c y.tab.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

y.tab.c: parser.y lex.yy.c
	yacc -d parser.y

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

ast.o: ast.c
	gcc -c ast.c

tac.o: tac.c
	gcc -c tac.c

clean:
	rm *.o etapa5 lex.yy.c lex.yy.h y.tab.c y.tab.h
