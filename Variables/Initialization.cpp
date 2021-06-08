#include "Initialization.h"

VarInit::VarInit(TypeNode* t, IdentifierNode* n, ExprNode* e) {
    type = t;
    name = n;
    expr = e;
    // addSymbol - initialized
}

void VarInit::execute() {
    expr->execute();
    // printf("push %s\n", expr);
    name->execute();
    // printf("pop %s\n", name);
}

VarInit::~VarInit() {
    delete type;
    delete name;
    delete expr;
}
