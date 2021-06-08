
#ifndef CONSTANTS_H
#define CONSTANTS_H


enum DataType
{
    _TYPE_INT,
    _TYPE_FLOAT,
    _TYPE_CHAR,
    _TYPE_BOOL,
    _TYPE_VOID
};

enum ScopeType
{
    GLOBAL = 1,
    BLOCK,
    LOOP,
    _SWITCH,
    INT_FUNC,
    FLOAT_FUNC,
    CHAR_FUNC,
    BOOL_FUNC,
    VOID_FUNC
};

#endif