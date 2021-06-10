#! /bin/sh

if [ -d "build" ]; then
  # Take action if $DIR exists. #
  echo "build directory is exist"
else
  mkdir build
fi

lex cplus.l

bison cplus.y -d

mv cplus.tab.c cplus.tab.cpp

mv lex.yy.c lex.yy.cpp

cd build

cmake ..

make

cp cplus ../Executables/

