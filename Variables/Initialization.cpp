#include "Initialization.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

VarInit::VarInit(TypeNode* t, IdentifierNode* n, ExprNode* e, int l) : VarDeclare(t, n, l) {
    type = t;
    name = n;
    expr = e;
    lineno = l;
}

void VarInit::setType(TypeNode* t) {
    type = t;
}

TypeNode* VarInit::getType() {
    return type;
}

void VarInit::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    if (sym->insertId(name->getName(), lineno, type->getType(), true, false)) {
        expr->execute();
        // printf("push %s\n", expr);
        name->execute();
        // printf("pop %s\n", name);
    }
    else {
        printf("Error:%i: Redeclaration of variable: %s %s\n", lineno, typeToString(type->getType()).c_str(), name->getName().c_str());
    }
}

VarInit::~VarInit() {
    delete type;
    delete name;
    delete expr;
}
