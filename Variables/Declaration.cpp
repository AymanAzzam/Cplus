#include "Declaration.h"

VarDeclare::VarDeclare(TypeNode* t, IdentifierNode* n) {
    type = t;
    name = n;
    // addSymbol - uninitialized
}

void VarDeclare::execute() {
    /*do nothing*/;
}

VarDeclare::~VarDeclare() {
    delete type;
    delete name;
}
