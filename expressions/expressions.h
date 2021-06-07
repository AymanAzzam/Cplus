
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

// int DataType need to be changed
#include <string>
#include <iostream>
using namespace std;

enum Operator {
    //MOD_EQ, MULT_EQ, DIV_EQ, MINUS_EQ, PLUS_EQ, EQ,         
    
    ADD, SUB, MUL, DIV, REM,

    LTE, GTE, LT, GT, NOT_EQ, IS_EQ,
    
    SHL, SHR, BIT_XOR, BIT_OR, BIT_AND,
    
    LOGICAL_AND, LOGICAL_OR,

    INC_OPR, DEC_OPR,

    BIT_NOT, LOGICAL_NOT
};

struct ExprNode{
    int Value;
    virtual int getValue(){
        return Value;
    }
};

class TwoOpNode: public ExprNode {
    ExprNode *left, *right;
    Operator opr;

    TwoOpNode(ExprNode* l, ExprNode* r, Operator o);

    virtual int getValue();

    ~TwoOpNode();
};

class LeftOpNode: public ExprNode {
    ExprNode* left;
    Operator opr;

    LeftOpNode(ExprNode* l, Operator o);

    virtual int getValue();

    ~LeftOpNode();
};

class RightOpNode: public ExprNode {
    ExprNode* right;
    Operator opr;

    RightOpNode(ExprNode* r, Operator o);

    virtual int getValue();

    ~RightOpNode();
};


class IdentifierNode: public ExprNode {
    string name;

    IdentifierNode(string n): ExprNode() {
        name = n;
    }

    virtual int getValue() {

    }
};

class Expression: public ExprNode {
    ExprNode* expr;

    Expression(ExprNode* e): ExprNode() {
        expr = e;
    }

    virtual int getValue() {
        return expr->getValue();
    }

    ~Expression() {
        if(expr) delete expr;
    }
};

#endif