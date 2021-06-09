#pragma once

#include "../SubExpr/CondExpr.h"
#include "../expressions/expressions.h"
#include <string>

class VarDeclare : public ExprNode {
protected:
    TypeNode* type;
    IdentifierNode* name;
    int lineno;
public:
    VarDeclare(TypeNode* t, IdentifierNode* n, int l);
    virtual void setType(DataType t);
    virtual DataType getType() override;
    virtual std::string getName();
    void execute();
    ~VarDeclare();
};
