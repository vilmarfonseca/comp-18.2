etapa4: y.tab.o lex.yy.o hash.o ast.o semantic.o main.o 
	gcc lex.yy.o hash.o ast.o semantic.o main.o y.tab.o -o etapa4 -Wall -g

main.o: main.c
	gcc -c main.c -Wall -g

hash.o: hash.c
	gcc -c hash.c -Wall -g

semantic.o: semantic.c
	gcc -c semantic.c -Wall -g

y.tab.o: y.tab.c
	gcc -c y.tab.c -Wall -g

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c -Wall -g

y.tab.c: parser.y lex.yy.c
	yacc -d parser.y

lex.yy.c: scanner.l
	lex --header-file=lex.yy.h scanner.l

ast.o: ast.c
	gcc -c ast.c -Wall -g

clean:
	rm *.o etapa4 lex.yy.c lex.yy.h y.tab.c y.tab.h
