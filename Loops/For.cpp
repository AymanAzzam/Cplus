#include <iostream>
#include "For.h"

For::For(Node* a, Node* b, Node* c, Node* s) {
    f1 = a;
    f2 = b;
    f3 = c;
    stmt = s;
}

void For::execute() {
    contLabel = labelNumber++;
    breakLabel = labelNumber++;

    contLabels.push_back(contLabel);
    breakLabels.push_back(breakLabel);

    f1->execute();
    printf("lbl%i:\n", contLabel);
    f2->execute();
    printf("JZ lbl%i\n", breakLabel);
    stmt->execute();
    f3->execute();
    printf("JMP lbl%i\n", contLabel);
    printf("lbl%i:\n", breakLabel);

    contLabels.pop_back();
    breakLabels.pop_back();

    contLabels.pop_back();
    breakLabels.pop_back();
}

For::~For() {
    delete f1;
    delete f2;
    delete f3;
    delete stmt;
}
