cmake_minimum_required(VERSION 3.16)
project(Lex_and_Yacc)

set(CMAKE_CXX_STANDARD 14)

#add_executable(test Test.cpp)

add_executable(
        test
        Conditional/IfStmt.cpp Conditional/IfStmt.h Conditional/SwitchStmt.h constants.h cplus.tab.cpp cplus.tab.h expressions/expressions.h expressions/left_operand.cpp expressions/right_operand.cpp expressions/two_operands.cpp Functions/Function.cpp Functions/Function.h Headers.h JmpStmt.h lex.yy.cpp Loops/DoWhile.cpp Loops/DoWhile.h Loops/For.cpp Loops/For.h Loops/While.cpp Loops/While.h Node.cpp Node.h Quad.h Stmt.cpp Stmt.h StmtList.cpp StmtList.h SubExpr/CondExpr.cpp SubExpr/CondExpr.h SubExpr/EpsExpr.cpp SubExpr/EpsExpr.h SubExpr/ForExpr.cpp SubExpr/ForExpr.h SymbolTable/SymbolTable.cpp SymbolTable/SymbolTable.h utilities.cpp utilities.h Variables/ConstDef.cpp Variables/ConstDef.h Variables/Declaration.cpp Variables/Declaration.h Variables/Initialization.cpp Variables/Initialization.h Variables/MultiConstInit.cpp Variables/MultiConstInit.h Variables/MultiVarDef.cpp Variables/MultiVarDef.h
)
