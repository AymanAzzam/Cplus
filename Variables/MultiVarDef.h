#pragma once

#include "Declaration.h"
#include "../expressions/expressions.h"

#include <vector>

class MultiVarDef : public Node {
    DataType type;
    std::vector<VarDeclare*> definitions;
public:
    MultiVarDef(VarDeclare* s);
    void push(VarDeclare* s);
    void setType(DataType t);
    DataType getType();
    void execute();
    ~MultiVarDef();
};
