#include <iostream>
#include "While.h"

While::While(Node* a, Node* s) {
    cond = a;
    stmt = s;
}

void While::execute() {
    contLabel = labelNumber++;
    breakLabel = labelNumber++;

    contLabels.push_back(contLabel);
    breakLabels.push_back(breakLabel);

    printf("lbl%i:\n", contLabel);
    cond->execute();
    printf("JZ lbl%i\n", breakLabel);
    stmt->execute();
    printf("JMP lbl%i\n", contLabel);
    printf("lbl%i:\n", breakLabel);
    
    contLabels.pop_back();
    breakLabels.pop_back();
}

While::~While() {
    delete cond;
    delete stmt;
}
