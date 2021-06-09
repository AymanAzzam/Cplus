#pragma once

#include "ConstDef.h"
#include "../expressions/expressions.h"

#include <vector>

class MultiConstInit : public Node {
    TypeNode* type;
    std::vector<ConstDef*> definitions;
public:
    MultiConstInit(ConstDef* s);
    void push(ConstDef* s);
    void setType(TypeNode* t);
    TypeNode* getType();
    void execute();
    ~MultiConstInit();
};
