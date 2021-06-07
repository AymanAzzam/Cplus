#pragma once

#include "../Node.h"
#include <string>

typedef enum {
    Int,
    Char,
    Bool,
    Float
} DataType;

class VarDec : Node {
public:
    VarDec(DataType type, std::string name, int lineno);
    void execute();
};
