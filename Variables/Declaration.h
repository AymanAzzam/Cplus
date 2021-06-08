#pragma once

#include "../Stmt.h"
#include "../expressions/expressions.h"
#include <string>

class VarDeclare : public Stmt {
protected:
    TypeNode* type;
    IdentifierNode* name;
    int lineno;
public:
    VarDeclare(TypeNode* t, IdentifierNode* n, int l);
    virtual void setType(TypeNode* t);
    virtual TypeNode* getType();
    virtual IdentifierNode* getName();
    void execute();
    ~VarDeclare();
};
