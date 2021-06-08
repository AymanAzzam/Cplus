bison -d cplus.y
flex cplus.l
g++ cplus.tab.c lex.yy.c *.cpp Loops/*.cpp SubExpr/*.cpp expressions/*.cpp Conditional/*.cpp
a.exe
