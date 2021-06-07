#pragma once

#include "../Node.h"
#include <string>

typedef enum {
    Int,
    Char,
    Bool,
    Float
} DataType;

class VarInit : Node {
    std::string name;
    std::string value;
public:
    VarInit(DataType type, std::string inName, std::string invalue, int lineno);
    void execute();
};
