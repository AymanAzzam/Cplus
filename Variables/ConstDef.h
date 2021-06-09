#pragma once

#include "Initialization.h"
#include "../expressions/expressions.h"

class ConstDef : public VarInit {
public:
    ConstDef(TypeNode* t, IdentifierNode* n, ExprNode* e, int l);
    void execute();
    ~ConstDef();
};
