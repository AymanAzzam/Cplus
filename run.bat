flex cplus.l
mv lex.yy.c lex.yy.cpp
bison -d cplus.y
mv cplus.tab.c cplus.tab.cpp
