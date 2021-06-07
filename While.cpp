#include "While.h"
#include <iostream>

While::While(Node* a, Node* z) {
    cond = a;
    s = z;
}

void While::execute() {
    printf("lbl%i:\n", lblno++);
    cond->execute();
    printf("JZ lbl%i\n", lblno);
    s->execute();
    printf("JMP lbl%i\n", lblno-1);
    printf("lbl%i:\n", lblno++);
}
