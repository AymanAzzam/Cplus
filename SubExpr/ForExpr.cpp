#include <iostream>
#include "ForExpr.h"

ForExpr::ForExpr(Node* rule) { //Expression
    expand = rule;
}

void ForExpr::execute() {
    //expand->execute();
    printf("-- placeholder for ForExpr\n");
}
