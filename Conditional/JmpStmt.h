#ifndef LEX_AND_YACC_JMPSTMT_H
#define LEX_AND_YACC_JMPSTMT_H

#include <iostream>
#include "../Stmt.h"

using namespace std;

class BreakStmt : public Stmt {
public:

    void execute() override {
        cout << "jmp L" << breakLabel.top() << endl;
    }
};

class ContinueStmt : public Stmt {
public:

    void execute() override {
        cout << "jmp L" << continueLabel.top() << endl;
    }
};

#endif //LEX_AND_YACC_JMPSTMT_H