#include "IfStmt.h"
#include "../SymbolTable/SymbolTable.h"
#include "../utilities.h"
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
        writeAssembly(string_format("\tJMP L%i", (label2 = labelNumber++)));
        writeAssembly(string_format("L%d:", label1));
        elseBody->execute();
        writeAssembly(string_format("L%d:", label2));

    } else {
        writeAssembly(string_format("L%d:", label1));
    }
    sym->finishScope();
}

IfStmt::~IfStmt() {
    delete condExpr;
    delete ifBody;
    delete elseBody;
}


