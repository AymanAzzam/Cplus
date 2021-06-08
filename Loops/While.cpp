#include <iostream>
#include "While.h"

While::While(Node* a, Node* s) {
    cond = a;
    stmt = s;
}

void While::execute() {
    continueLabel.push(labelNumber++);
    breakLabel.push(labelNumber++);

    printf("L%i:\n", continueLabel.top());
    cond->execute();
    printf("JZ L%i\n", breakLabel.top());
    stmt->execute();
    printf("JMP L%i\n", continueLabel.top());
    printf("L%i:\n", breakLabel.top());
    
    continueLabel.pop();
    breakLabel.pop();
}

While::~While() {
    delete cond;
    delete stmt;
}
