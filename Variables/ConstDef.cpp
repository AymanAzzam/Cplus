#include "ConstDef.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

ConstDef::ConstDef(TypeNode* t, IdentifierNode* n, ExprNode* e, int l) {
    type = t;
    name = n;
    expr = e;
    lineno = l;
}

void ConstDef::setType(TypeNode* t) {
    type = t;
}

TypeNode* ConstDef::getType() {
    return type;
}

void ConstDef::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    if (sym->insertId(name->getName(), lineno, type->getType(), true, true)) {
        expr->execute();
        // printf("push %s\n", expr);
        name->execute();
        // printf("pop %s\n", name);
    }
    else {
        printf("Error:%i: Redeclaration of variable: const %s %s\n", lineno, typeToString(type->getType()).c_str(), name->getName().c_str());
    }
}

ConstDef::~ConstDef() {
    delete type;
    delete name;
    delete expr;
}
