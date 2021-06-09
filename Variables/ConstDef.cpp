#include "ConstDef.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

ConstDef::ConstDef(TypeNode* t, IdentifierNode* n, ExprNode* e, int l) : VarInit(t, n, e, l) {
}

void ConstDef::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    if (sym->insertId(name->getName(), lineno, getType(), true, true)) {
        expr->execute();
        
        if (expr->getType() != getType()) {
            std::string exprType = typeToString(expr->getType()),
                        initType = typeToString(getType());
            log(string_format("Warning:%i: Type mismatch, converting %s to %s.\n",
                                lineno, exprType.c_str(), initType.c_str()));
            writeAssembly(string_format("CVT %s %s", exprType.c_str(), initType.c_str()));
        }
        
        writeAssembly(string_format("POP %s %s\n", typeToString(getType()).c_str(), name->getName().c_str()));
    }
    else {
        log(string_format("Error:%i: Redeclaration of variable: const %s %s\n",
                            lineno, typeToString(getType()).c_str(), name->getName().c_str()));
    }
}

ConstDef::~ConstDef() {
}
