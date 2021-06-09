#pragma once

#include "Declaration.h"
#include "../expressions/expressions.h"
#include <string>

class VarInit : public VarDeclare {
protected:
    ExprNode* expr;
public:
    VarInit(TypeNode* t, IdentifierNode* n, ExprNode* e, int l);
    void execute();
    ~VarInit();
};
