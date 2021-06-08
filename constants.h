
#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Operator {
    _MOD_EQ, _MULT_EQ, _DIV_EQ, _MINUS_EQ, _PLUS_EQ, _EQ,         
    
    _ADD, _SUB, _MUL, _DIV, _REM,

    _LTE, _GTE, _LT, _GT, _NOT_EQ, _IS_EQ,
    
    _SHL, _SHR, _BIT_XOR, _BIT_OR, _BIT_AND,
    
    _LOGICAL_AND, _LOGICAL_OR,

    _INC_OPR, _DEC_OPR,

    _BIT_NOT, _LOGICAL_NOT
};


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