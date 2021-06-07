FLAGS :=  -Wall -g
CC := g++

a.out: lex.yy.c cplus.tab.c
	$(CC) $(FLAGS) lex.yy.c cplus.tab.c -o a.out

lex.yy.c: cplus.l 
	flex cplus.l 

cplus.tab.c: cplus.y 
	bison --debug -d cplus.y

clean:
	rm -f cplus.tab.c cplus.tab.h lex.yy.c *.out