#include "IfStmt.h"
#include "../SymbolTable/SymbolTable.h"
#include <iostream>

using namespace std;

IfStmt::IfStmt(Node *condExpr, Stmt *ifBody, Stmt *elseBody) :
        condExpr(condExpr), ifBody(ifBody), elseBody(elseBody) {
}

void IfStmt::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();
    sym->startScope(BLOCK);
    condExpr->execute();
    int label1, label2;
    cout << "JZ L" << (label1 = labelNumber++) << endl;
    ifBody->execute();
    if (elseBody) {
        cout << "JMP L" << (label2 = labelNumber++) << endl;
        cout << "L" << label1 << ":" << endl;
        elseBody->execute();
        cout << "L" << label2 << ":" << endl;
    } else {
        cout << "L" << label1 << ":" << endl;
    }
    sym->finishScope();
}

IfStmt::~IfStmt() {
    delete condExpr;
    delete ifBody;
    delete elseBody;
}


