#include "While.h"
#include <iostream>

While::While(Node* a, Node* z) {
    cond = a;
    s = z;
}

void While::execute() {
    printf("lbl%i:\n", lblno++);
    s->execute();
    cond->execute();
    printf("JZ lbl%i\n", lblno);
}
