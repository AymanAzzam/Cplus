#include <iostream>
#include "DoWhile.h"
#include "../SymbolTable/SymbolTable.h"

DoWhile::DoWhile(Node* a, Node* z) {
    stmt = a;
    cond = z;
}

void DoWhile::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    sym->startScope(LOOP);

    continueLabel.push(labelNumber++);
    breakLabel.push(labelNumber++);

    printf("L%i:\n", continueLabel.top());
    stmt->execute();
    cond->execute();
    printf("JNZ L%i\n", continueLabel.top());
    printf("L%i:\n", breakLabel.top());

    continueLabel.pop();
    breakLabel.pop();

    vector<pair<string, int>> unused = sym->finishScope();
    for (auto u: unused) {
        printf("Warning:%i: Variable %s declared but not used.\n", u.second, u.first.c_str());
    }
}

DoWhile::~DoWhile() {
    delete stmt;
    delete cond;
}
