#include <iostream>
#include "For.h"

For::For(Node* a, Node* b, Node* c, Node* s) {
    f1 = a;
    f2 = b;
    f3 = c;
    stmt = s;
}

void For::execute() {
    continueLabel.push(labelNumber++);
    breakLabel.push(labelNumber++);

    f1->execute();
    printf("L%i:\n", continueLabel.top());
    f2->execute();
    printf("JZ L%i\n", breakLabel.top());
    stmt->execute();
    f3->execute();
    printf("JMP L%i\n", continueLabel.top());
    printf("L%i:\n", breakLabel.top());

    continueLabel.pop();
    breakLabel.pop();
}

For::~For() {
    delete f1;
    delete f2;
    delete f3;
    delete stmt;
}
