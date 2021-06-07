#include <iostream>
#include "For.h"

For::For(Node* a, Node* b, Node* c, Node* z) {
    f1 = a;
    f2 = b;
    f3 = c;
    s = z;
}

void For::execute() {
    f1->execute();
    printf("lbl%i:\n", labelNumber++);
    f2->execute();
    printf("JZ lbl%i\n", labelNumber);
    s->execute();
    f3->execute();
    printf("JMP lbl%i\n", labelNumber-1);
    printf("lbl%i:\n", labelNumber++);
}
