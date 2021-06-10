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

    if (f1) f1->execute();
    writeAssembly(string_format("L%i:", startLabel));
    if (f2) f2->execute();
    writeAssembly(string_format("JZ L%i", breakLabel.top()));
    stmt->execute();
    writeAssembly(string_format("L%i:", continueLabel.top()));
    if (f3) f3->execute();
    writeAssembly(string_format("JMP L%i", startLabel));
    writeAssembly(string_format("L%i:", breakLabel.top()));

    continueLabel.pop();
    breakLabel.pop();

    vector<pair<string, int>> unused = sym->finishScope();
    for (auto u: unused) {
        log(string_format("Warning:%i: Variable declared but not used: %s.", u.second, u.first.c_str()));
    }
}

For::~For() {
    delete f1;
    delete f2;
    delete f3;
    delete stmt;
}
