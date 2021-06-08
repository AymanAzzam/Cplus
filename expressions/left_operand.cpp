#include "expressions.h"

LeftOpNode::LeftOpNode(ExprNode* l, Operator o): ExprNode(){
    left = l;
    opr = o;
}

void LeftOpNode::checkError() {
    
    SymbolTable *symbolTable = SymbolTable::GetInstance();
    DataType type;
    string s;
    bool con, ini, success;
    
    success = symbolTable->lookupId(left->name, type, ini, con);
    
    if(!success)
        printf("\n\nError: undeclared variable %s\n\n", name.c_str());
    else if(!ini)
        printf("\n\nError: uninitialized variable %s\n\n", left->name.c_str());
    else if(ini && con)
        printf("\n\nConstant Error: %s is constant\n\n", left->name.c_str());
    
}

void LeftOpNode::execute() {
    this->checkError();

    left->execute();

    switch (opr)
    {
        case _INC_OPR:
            printf("\tPUSH\t1\n");
            left->execute();
            printf("\tADD\n");
            printf("\tPOP\t%s\n", left->name.c_str());
            return;
        case _DEC_OPR:
            printf("\tPUSH\tx\t1\n");
            left->execute();
            printf("\tSUB\n");
            printf("\tPOP\t%s\n", left->name.c_str());
            return;
    }
    printf("\n\nError occured in LeftOpNode::execute() in left_operand.cpp\n\n");
}

LeftOpNode::~LeftOpNode() {
    if(left)    delete left;
}