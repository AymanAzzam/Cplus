#pragma once

#include "../Node.h"
#include "../expressions/expressions.h"
#include <string>

class VarInit : Node {
    TypeNode* type;
    IdentifierNode* name;
    ExprNode* expr;
public:
    VarInit(TypeNode* t, IdentifierNode* n, ExprNode* e);
    void execute();
    ~VarInit();
};
