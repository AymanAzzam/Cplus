
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

// int DataType need to be changed
#include <iostream>
#include "../Node.h"
#include "../Stmt.h"
#include "../Symbol Table/SymbolTable.h"

using namespace std;

class ExprNode: public Stmt{
    public:
        string name;
        
        /**
        * @param n: The name of variable
        */
        ExprNode(string n = "-1") {
            name = n;
        }
        
        /**
        * @brief Push the variable name into the stack.
        */
        virtual void execute() {printf("\tPUSH\t%s\n", name.c_str());};
};

class TypeNode: public Node {
    DataType type;

    public:
        /**
        * @param t: The name of data type [_TYPE_INT, _TYPE_FLOAT, ..]
        */
        TypeNode(DataType t) {
            type = t;
        }

        virtual void execute(){};
};

class ValueNode: public ExprNode {
    string value;
    DataType type;

    public:
        /**
        * @param v: The value of node
        * @param t: The name of data type [_TYPE_INT, _TYPE_FLOAT, ..]
        */
        ValueNode(string v, DataType t): ExprNode(v) {
            value = v;
            type = t;
        }

        /**
        * @brief Push the node value into the stack
        */
        virtual void execute(){printf("PUSH %s\n", value.c_str());};
};

class TwoOpNode: public ExprNode {
    ExprNode *left, *right;
    Operator opr;
    public:
        /**
        * @param l: Pointer to the left operand
        * @param r: Pointer to the right operand
        * @param o: The operator [_ADD, _SUB, _MUL, ..]
        */
        TwoOpNode(ExprNode* l, ExprNode* r, Operator o);
        
        /**
        * @brief Check the error of declaration, initialization, constant and Type mismatch
        */
        void checkError();
        
        /**
        * @brief Push the Two variables into the stack then apply the operation
        */
        virtual void execute();

        ~TwoOpNode();
};

class LeftOpNode: public ExprNode {
    ExprNode* left;
    Operator opr;

    public:
        /**
        * @param l: Pointer to the left operand
        * @param o: The operator [_INC_OPR, _DEC_OPR]
        */
        LeftOpNode(ExprNode* l, Operator o);

        /**
        * @brief Check the error of declaration, initialization, constant and Type mismatch
        */
        void checkError();

        /**
        * @brief Push the variable into the stack then apply the operation
        */
        virtual void execute();

        ~LeftOpNode();
};

class RightOpNode: public ExprNode {
    ExprNode* right;
    Operator opr;

    public:
        /**
        * @param r: Pointer to the right operand
        * @param o: The operator [_INC_OPR, _DEC_OPR, _BIT_NOT, _LOGICAL_NOT, _ADD, _SUB]
        */
        RightOpNode(ExprNode* r, Operator o);

        /**
        * @brief Check the error of declaration, initialization, constant and Type mismatch
        */
        void checkError();

        /**
        * @brief Push the variable into the stack then apply the operation
        */
        virtual void execute();

        ~RightOpNode();
};


class IdentifierNode: public ExprNode {
    string name;

    public:
        /**
        * @param n: The name of identifier
        */
        IdentifierNode(string n): ExprNode(n) {
            name = n;
        }

        virtual void execute(){printf("POP %s\n", name.c_str()); printf("PUSH %s\n", name.c_str());};
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