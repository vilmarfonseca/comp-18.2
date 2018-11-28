etapa6: y.tab.o lex.yy.o hash.o ast.o semantic.o main.o tac.o genco.o
	gcc lex.yy.o hash.o ast.o semantic.o main.o y.tab.o tac.o genco.o -o etapa6

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

genco.o: genco.c
	gcc -c genco.c

clean:
	rm *.o etapa6 lex.yy.c lex.yy.h y.tab.c y.tab.h *.bin *.s