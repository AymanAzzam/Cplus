#ifndef UTILITIES__H
#define UTILITIES__H


#include <string>
#include "constants.h"
using namespace std;

string typeToString(DataType type) {
    string out;

    switch (type)
    {
        case _TYPE_CHAR:
            out = "char";
            break;
        case _TYPE_FLOAT:
            out = "float";
            break;
        case _TYPE_INT:
            out = "int";
            break;
        case _TYPE_BOOL:
            out = "bool";
            break;
        case _TYPE_VOID:
            out = "void";
            break;
    }

    return out;
};

#endif