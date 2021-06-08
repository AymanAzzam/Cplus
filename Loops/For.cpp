#include <iostream>
#include "For.h"
#include "../SymbolTable/SymbolTable.h"

For::For(Node* a, Node* b, Node* c, Node* s) {
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
    printf("L%i:\n", startLabel);
    f2->execute();
    printf("JZ L%i\n", breakLabel.top());
    stmt->execute();
    printf("L%i:\n", continueLabel.top());
    f3->execute();
    printf("JMP L%i\n", startLabel);
    printf("L%i:\n", breakLabel.top());

    continueLabel.pop();
    breakLabel.pop();

    vector<pair<string, int>> unused = sym->finishScope();
    for (auto u: unused) {
        printf("Warning:%i: Variable %s declared but not used.\n", u.second, u.first.c_str());
    }
}

For::~For() {
    delete f1;
    delete f2;
    delete f3;
    delete stmt;
}
