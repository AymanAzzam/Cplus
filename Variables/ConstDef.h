#pragma once

#include "../Stmt.h"
#include "../expressions/expressions.h"

class ConstDef : public Stmt {
    TypeNode* type;
    IdentifierNode* name;
    ExprNode* expr;
    int lineno;
public:
    ConstDef(TypeNode* t, IdentifierNode* n, ExprNode* e, int l);
    void setType(TypeNode* t);
    TypeNode* getType();
    void execute();
    ~ConstDef();
};