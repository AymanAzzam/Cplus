#pragma once

#include "Declaration.h"
#include "../expressions/expressions.h"
#include <string>

class VarInit : public VarDeclare {
    // TypeNode* type;
    // IdentifierNode* name;
    ExprNode* expr;
    int lineno;
public:
    VarInit(TypeNode* t, IdentifierNode* n, ExprNode* e, int l);
    void setType(TypeNode* t);
    TypeNode* getType();
    void execute();
    ~VarInit();
};
