
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
        
        ExprNode(string n = "-1") {
            name = n;
        }
        
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

        virtual void execute(){printf("PUSH %s\n", value.c_str());};
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

        void checkError();

        virtual void execute();

        ~LeftOpNode();
};

class RightOpNode: public ExprNode {
    ExprNode* right;
    Operator opr;

    public:
        RightOpNode(ExprNode* r, Operator o);

        void checkError();

        virtual void execute();

        ~RightOpNode();
};


class IdentifierNode: public ExprNode {
    string name;

    public:
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