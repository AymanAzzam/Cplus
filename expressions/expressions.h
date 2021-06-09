
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

// int DataType need to be changed
#include <iostream>
#include "../utilities.h"
#include "../Node.h"
#include "../Stmt.h"
#include "../SymbolTable/SymbolTable.h"

using namespace std;

class ExprNode: public Node{
    public:
        DataType type;

        /**
        * @param type: The name of data type
        */
        ExprNode(DataType type = _TYPE_VOID) {
            this->type = type; 
        }

        virtual DataType getType() {
            return type;
        }

        virtual string getName() = 0;
        
        virtual void execute() = 0;
};

class TypeNode: public Node {
    DataType type;

    public:
        /**
        * @param type: The name of data type [_TYPE_INT, _TYPE_FLOAT, ..]
        */
        TypeNode(DataType type) {
            this->type = type;
        }

        DataType getType() {
            return type;
        }

        virtual void execute(){};
};

class ValueNode: public ExprNode {
    string value;
   
    public:
        /**
        * @param value: The value of node
        * @param type: The name of data type [_TYPE_INT, _TYPE_FLOAT, ..]
        */
        ValueNode(string value, DataType type): ExprNode(type) {
            this->value = value;
        }

        /**
        * @brief return the value
        */
        virtual string getName() {
            return value;
        }

        /**
        * @brief Push the node value into the stack
        */
        virtual void execute(){pushToStack(value, type);}
};


class IdentifierNode: public ExprNode {
    string name;
    public:
        /**
        * @param name: The name of identifier
        */
        IdentifierNode(string name): ExprNode() {
            this->name = name;
        }

        /**
        * @brief return the value
        */
        virtual string getName() {
            return name;
        }

        virtual void execute(){pushToStack(name, type);}
};


class TwoOpNode: public ExprNode {
    ExprNode *left, *right;
    Operator opr;
    int line;
    
    public:
        /**
        * @param left: Pointer to the left operand
        * @param right: Pointer to the right operand
        * @param opr: The operator [_ADD, _SUB, _MUL, ..]
        * @param line: The line number that contains the expression
        */
        TwoOpNode(ExprNode* left, ExprNode* right, Operator opr, int line);
        
        virtual string getName() {};
        
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
    int line;

    public:
        /**
        * @param left: Pointer to the left operand
        * @param opr: The operator [_INC_OPR, _DEC_OPR]
        * @param line: The line number that contains the expression
        */
        LeftOpNode(ExprNode* left, Operator opr, int line);

        virtual string getName() {};

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
    int line;

    public:
        /**
        * @param right: Pointer to the right operand
        * @param opr: The operator [_INC_OPR, _DEC_OPR, _BIT_NOT, _LOGICAL_NOT, _ADD, _SUB]
        * @param line: The line number that contains the expression
        */
        RightOpNode(ExprNode* right, Operator opr, int line);

        virtual string getName() {};        

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

#endif