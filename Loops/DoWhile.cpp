#include <iostream>
#include "DoWhile.h"

DoWhile::DoWhile(Node* a, Node* z) {
    stmt = a;
    cond = z;
}

void DoWhile::execute() {
    continueLabel.push(labelNumber++);
    breakLabel.push(labelNumber++);

    printf("L%i:\n", continueLabel.top());
    stmt->execute();
    cond->execute();
    printf("JNZ L%i\n", continueLabel.top());
    printf("L%i:\n", breakLabel.top());

    continueLabel.pop();
    breakLabel.pop();
}

DoWhile::~DoWhile() {
    delete stmt;
    delete cond;
}
