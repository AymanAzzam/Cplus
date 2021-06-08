#include "Declaration.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

VarDeclare::VarDeclare(TypeNode* t, IdentifierNode* n, int l) {
    type = t;
    name = n;
    lineno = l;
}

void VarDeclare::setType(TypeNode* t) {
    type = t;
}

TypeNode* VarDeclare::getType() {
    return type;
}

void VarDeclare::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();
    
    if (sym->insertId(name->getName(), 1, type->getType(), false, false)) {
        /*no quadruples produced*/;
    }
    else {
        printf("Error:%i: Redeclaration of variable: %s %s\n", lineno, typeToString(type->getType()).c_str(), name->getName().c_str());
    }
}

VarDeclare::~VarDeclare() {
    delete type;
    delete name;
}
