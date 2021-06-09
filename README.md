# Cplus
Compiler for C++ using Flex(Lex) and Bison(Yacc), that compiles:
1. if else, switch case default.
2. for, do while, while.
3. fuctions, nested blocks.
4. expressions, all operators(arithmetic, assignment, ..etc). 
5. data types (int, float, char, bool, const).
6. break, continue.

### Dependencies
| JRE | Flex | Bison | Cmake | G++ |
| ------ | ------ | ------ | ------ | ------ |
| User | Dev | Dev | Dev | Dev |

### Build Code to compile without GUI
Run the following commands from the current directory:
```sh
lex cplus.l && bison -d cplus.y
mv cplus.tab.c cplus.tab.cpp && mv lex.yy.c lex.yy.cpp
mkdir build && cd build
cmake ..
make
```

### Compile a program without the GUI
Put your code file in build folder and name it 'source.cp' then run the followig command from the build directory:
```sh
./cplus
```
You will get 3 output files:
- **quad.txt** contains the quadruples.
- **log.txt** contains any errors and warnings.
- **table.txt** contains the data in the symbol table after compiling the program.

### Team Members
1. [Ayman Azzam](https://github.com/AymanAzzam)
2. [Ayman Elakwah](https://github.com/aymanElakwah)
3. [AymanAbdelnaby](https://github.com/AymanAbdelnaby)
4. [Khaled Moataz](https://github.com/KhaledMoataz)
