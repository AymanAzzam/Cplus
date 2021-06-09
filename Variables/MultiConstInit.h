#pragma once

#include "ConstDef.h"
#include "../expressions/expressions.h"

#include <vector>

class MultiConstInit : public Node {
    DataType type;
    std::vector<ConstDef*> definitions;
public:
    MultiConstInit(ConstDef* s);
    void push(ConstDef* s);
    void setType(DataType t);
    DataType getType();
    void execute();
    ~MultiConstInit();
};
