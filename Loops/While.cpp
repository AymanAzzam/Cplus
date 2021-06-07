#include <iostream>
#include "While.h"

While::While(Node* a, Node* z) {
    cond = a;
    s = z;
}

void While::execute() {
    printf("lbl%i:\n", labelNumber++);
    cond->execute();
    printf("JZ lbl%i\n", labelNumber);
    s->execute();
    printf("JMP lbl%i\n", labelNumber-1);
    printf("lbl%i:\n", labelNumber++);
}
