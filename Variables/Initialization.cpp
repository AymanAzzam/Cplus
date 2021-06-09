#include "Initialization.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

VarInit::VarInit(TypeNode* t, IdentifierNode* n, ExprNode* e, int l) : VarDeclare(t, n, l) {
    expr = e;
}

void VarInit::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    if (sym->insertId(name->getName(), lineno, getType(), true, false)) {
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
        log(string_format("Error:%i: Redeclaration of variable: %s %s\n",
                            lineno, typeToString(getType()).c_str(), name->getName().c_str()));
    }
}

VarInit::~VarInit() {
    delete expr;
}
