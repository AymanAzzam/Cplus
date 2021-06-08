#include <iostream>
#include "DoWhile.h"

DoWhile::DoWhile(Node* a, Node* z) {
    stmt = a;
    cond = z;
}

void DoWhile::execute() {
    contLabel = labelNumber++;
    breakLabel = labelNumber++;

    contLabels.push_back(contLabel);
    breakLabels.push_back(breakLabel);

    printf("lbl%i:\n", contLabel);
    stmt->execute();
    cond->execute();
    printf("JNZ lbl%i\n", contLabel);
    printf("lbl%i:\n", breakLabel);

    contLabels.pop_back();
    breakLabels.pop_back();
}

DoWhile::~DoWhile() {
    delete stmt;
    delete cond;
}
