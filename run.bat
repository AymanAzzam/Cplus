flex cplus.l
bison -d cplus.y
g++ lex.yy.c cplus.tab.c
a.exe
