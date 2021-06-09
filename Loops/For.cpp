#include <iostream>
#include "For.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

For::For(Node* a, Node* b, Node* c, Stmt* s) {
    f1 = a;
    f2 = b;
    f3 = c;
    stmt = s;
}

void For::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    sym->startScope(LOOP);

    int startLabel = labelNumber++;

    continueLabel.push(labelNumber++);
    breakLabel.push(labelNumber++);

    f1->execute();
    writeAssembly(string_format("L%i:\n", startLabel));
    f2->execute();
    writeAssembly(string_format("JZ L%i\n", breakLabel.top()));
    stmt->execute();
    writeAssembly(string_format("L%i:\n", continueLabel.top()));
    f3->execute();
    writeAssembly(string_format("JMP L%i\n", startLabel));
    writeAssembly(string_format("L%i:\n", breakLabel.top()));

    continueLabel.pop();
    breakLabel.pop();

    vector<pair<string, int>> unused = sym->finishScope();
    for (auto u: unused) {
        log(string_format("Warning:%i: Variable declared but not used: %s.\n", u.second, u.first.c_str()));
    }
}

For::~For() {
    delete f1;
    delete f2;
    delete f3;
    delete stmt;
}
