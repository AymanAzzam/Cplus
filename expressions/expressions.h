
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

// int DataType need to be changed
#include <iostream>
#include "../Node.h"
#include "../Symbol Table/SymbolTable.h"

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

class ExprNode: public Node{
    public:
        string name;
        
        ExprNode(string n = "-1") {
            name = n;
        }

        void checkError() {
            SymbolTable *symbolTable = SymbolTable::GetInstance();

            DataType type;
            bool con, ini, error;
            error = symbolTable->lookupId(name, type, ini, con);

            if(!error)
                printf("\n\nError: undeclared variable %s\n\n", name.c_str());
        };
        
        virtual void execute() {
            printf("\tPUSH\t%s\n", name.c_str());
        };
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
        ValueNode(string v, DataType t): ExprNode(v) {
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

        void checkError();

        virtual void execute();

        ~TwoOpNode();
};

class LeftOpNode: public ExprNode {
    ExprNode* left;
    Operator opr;

    public:
        LeftOpNode(ExprNode* l, Operator o);

        void checkError() {

        };

        virtual void execute();

        ~LeftOpNode();
};

class RightOpNode: public ExprNode {
    ExprNode* right;
    Operator opr;

    public:
        RightOpNode(ExprNode* r, Operator o);

        void checkError() {

        };

        virtual void execute();

        ~RightOpNode();
};


class IdentifierNode: public ExprNode {
    string name;

    public:
        IdentifierNode(string n): ExprNode(n) {
            name = n;
        }

        virtual void execute(){};
};

class Expression: public ExprNode {
    ExprNode* expr;

    public:
        Expression(ExprNode* e): ExprNode() {
            expr = e;
        }

        virtual void execute(){};

        ~Expression() {
            if(expr) delete expr;
        }
};

#endif