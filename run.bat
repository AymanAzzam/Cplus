bison -d cplus.y
flex cplus.l
g++ lex.yy.c cplus.tab.c *.cpp
a.exe
