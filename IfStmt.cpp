#include "IfStmt.h"
#include "Globals.h"
#include <iostream>

using namespace std;

IfStmt::IfStmt(CondExpr *condExpr, Stmt *ifBody, Stmt *elseBody) :
        condExpr(condExpr), ifBody(ifBody), elseBody(elseBody) {
}

void IfStmt::execute() {
    condExpr->execute();
    int label1, label2;
    cout << "jz L" << (label1 = labelNumber++) << endl;
    ifBody->execute();
    if (elseBody) {
        cout << "jmp L" << (label2 = labelNumber++) << endl;
        cout << "L" << label1 << ":" << endl;
        elseBody->execute();
        cout << "L" << label2 << ":" << endl;
    } else {
        cout << "L" << label1 << ":" << endl;
    }
}

IfStmt::~IfStmt() {
    delete condExpr;
    delete ifBody;
    delete elseBody;
}


