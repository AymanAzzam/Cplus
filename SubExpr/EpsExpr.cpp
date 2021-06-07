#include <iostream>
#include "EpsExpr.h"

EpsExpr::EpsExpr(Node* rule) { //Expression
    expand = rule;
}

void EpsExpr::execute() {
    //expand->execute();
    printf("-- placeholder for EpsExpr\n");
}
