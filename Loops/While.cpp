#include <iostream>
#include "While.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

While::While(Node* a, Node* s) {
    cond = a;
    stmt = s;
}

void While::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    sym->startScope(LOOP);

    continueLabel.push(labelNumber++);
    breakLabel.push(labelNumber++);

    writeAssembly(string_format("L%i:\n", continueLabel.top()));
    cond->execute();
    writeAssembly(string_format("JZ L%i\n", breakLabel.top()));
    stmt->execute();
    writeAssembly(string_format("JMP L%i\n", continueLabel.top()));
    writeAssembly(string_format("L%i:\n", breakLabel.top()));
    
    continueLabel.pop();
    breakLabel.pop();

    vector<pair<string, int>> unused = sym->finishScope();
    for (auto u: unused) {
        log(string_format("Warning:%i: Variable %s declared but not used.\n", u.second, u.first.c_str()));
    }
}

While::~While() {
    delete cond;
    delete stmt;
}
