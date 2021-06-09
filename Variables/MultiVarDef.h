#pragma once

#include "Declaration.h"
#include "../expressions/expressions.h"

#include <vector>

class MultiVarDef : public Node {
    TypeNode* type;
    std::vector<VarDeclare*> definitions;
public:
    MultiVarDef(VarDeclare* s);
    void push(VarDeclare* s);
    void setType(TypeNode* t);
    TypeNode* getType();
    void execute();
    ~MultiVarDef();
};
