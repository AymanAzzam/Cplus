#include <iostream>
#include "DoWhile.h"

DoWhile::DoWhile(Node* a, Node* z) {
    stmt = a;
    cond = z;
}

void DoWhile::execute() {
    printf("lbl%i:\n", labelNumber++);
    stmt->execute();
    cond->execute();
    printf("JNZ lbl%i\n", labelNumber-1);
}
