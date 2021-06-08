#pragma once

#include "../Node.h"
#include "../expressions/expressions.h"
#include <string>

class VarDeclare : Node {
    TypeNode* type;
    IdentifierNode* name;
public:
    VarDeclare(TypeNode* t, IdentifierNode* n);
    void execute();
    ~VarDeclare();
};
