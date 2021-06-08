
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

// int DataType need to be changed
#include <iostream>
#include "../Node.h"
#include "../Stmt.h"
#include "../Symbol Table/SymbolTable.h"

using namespace std;

class ExprNode: public Node{
    public:
        DataType type;

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
        * @param t: The name of data type [_TYPE_INT, _TYPE_FLOAT, ..]
        */
        TypeNode(DataType t) {
            type = t;
        }

        virtual void execute(){};
};

class ValueNode: public ExprNode {
    string value;
   
    public:
        /**
        * @param v: The value of node
        * @param t: The name of data type [_TYPE_INT, _TYPE_FLOAT, ..]
        */
        ValueNode(string v, DataType t): ExprNode(t) {
            value = v;
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
        virtual void execute(){printf("PUSH %s\n", value.c_str());};
};


class IdentifierNode: public ExprNode {
    string name;
    public:
        bool ini, dec, con;
        /**
        * @param n: The name of identifier
        */
        IdentifierNode(string n): ExprNode() {
            SymbolTable *symbolTable = SymbolTable::GetInstance();
            
            name = n;
            
            dec = symbolTable->lookupId(name, type, ini, con);
    
        }

        /**
        * @brief return the value
        */
        virtual string getName() {
            return name;
        }

        virtual void execute(){printf("POP %s\n", name.c_str()); printf("PUSH %s\n", name.c_str());};
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

    public:
        /**
        * @param l: Pointer to the left operand
        * @param o: The operator [_INC_OPR, _DEC_OPR]
        */
        LeftOpNode(ExprNode* l, Operator o);

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

    public:
        /**
        * @param r: Pointer to the right operand
        * @param o: The operator [_INC_OPR, _DEC_OPR, _BIT_NOT, _LOGICAL_NOT, _ADD, _SUB]
        */
        RightOpNode(ExprNode* r, Operator o);

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