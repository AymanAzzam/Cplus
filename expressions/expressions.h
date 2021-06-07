
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

// int DataType need to be changed
#include <string>
#include <iostream>
#include "../Node.h"
using namespace std;

enum Operator {
    _MOD_EQ, _MULT_EQ, _DIV_EQ, _MINUS_EQ, _PLUS_EQ, _EQ,         
    
    _ADD, _SUB, _MUL, _DIV, _REM,

    _LTE, _GTE, _LT, _GT, _NOT_EQ, _IS_EQ,
    
    _SHL, _SHR, _BIT_XOR, _BIT_OR, _BIT_AND,
    
    _LOGICAL_AND, _LOGICAL_OR,

    _INC_OPR, _DEC_OPR,

    _BIT_NOT, _LOGICAL_NOT
};

enum DataType {
    _TYPE_INT, _TYPE_FLOAT, _TYPE_CHAR, _TYPE_BOOL, _TYPE_VOID
};


class ExprNode: public Node{
    
    public:
    /*     virtual int getValue(){
            return Value;
        }
 */
        virtual void execute(){};
};

class TypeNode: public Node {
    DataType type;

    public:
        TypeNode(DataType t) {
            type = t;
        }

        virtual void execute(){};
};

class ValueNode: public ExprNode {
    string value;
    DataType type;

    public:
        ValueNode(string v, DataType t): ExprNode() {
            value = v;
            type = t;
        }

        virtual void execute(){};
};

class TwoOpNode: public ExprNode {
    ExprNode *left, *right;
    Operator opr;
    public:
        TwoOpNode(ExprNode* l, ExprNode* r, Operator o);

/*         virtual int getValue();
 */
        virtual void execute(){};

        ~TwoOpNode();
};

class LeftOpNode: public ExprNode {
    ExprNode* left;
    Operator opr;

    public:
        LeftOpNode(ExprNode* l, Operator o);

/*         virtual int getValue();
 */
        virtual void execute(){};

        ~LeftOpNode();
};

class RightOpNode: public ExprNode {
    ExprNode* right;
    Operator opr;

    public:
        RightOpNode(ExprNode* r, Operator o);

/*         virtual int getValue();
 */
        virtual void execute(){};

        ~RightOpNode();
};


class IdentifierNode: public ExprNode {
    string name;

    public:
        IdentifierNode(string n): ExprNode() {
            name = n;
        }

/*         virtual int getValue(){}
 */
        virtual void execute(){};
};

class Expression: public ExprNode {
    ExprNode* expr;

    public:
        Expression(ExprNode* e): ExprNode() {
            expr = e;
        }

/*         virtual int getValue() {
            return expr->getValue();
        }
 */
        virtual void execute(){};

        ~Expression() {
            if(expr) delete expr;
        }
};

#endif