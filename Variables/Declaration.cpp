#include "Declaration.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

VarDeclare::VarDeclare(TypeNode* t, IdentifierNode* n, int l) : ExprNode() {
    type = t;
    name = n;
    lineno = l;
}

void VarDeclare::setType(DataType t) {
    delete type;
    type = new TypeNode(t);
}

DataType VarDeclare::getType() {
    return type->getType();
}

std::string VarDeclare::getName() {
    return name->getName();
}

void VarDeclare::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    if (sym->insertId(name->getName(), lineno, getType(), false, false)) {
        /*no quadruples produced*/;
    }
    else {
        log(string_format("Error:%i: Redeclaration of variable: %s %s\n", lineno, typeToString(getType()).c_str(), name->getName().c_str()));
    }
}

VarDeclare::~VarDeclare() {
    delete type;
    delete name;
}
