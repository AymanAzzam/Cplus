#include "expressions.h"

LeftOpNode::LeftOpNode(ExprNode* left, Operator opr, int line): ExprNode(){
    this->left = left;
    this->opr = opr;
    this-> line = line;
}

DataType LeftOpNode::getType() {
    this->type = left->getType();

    return type;
}

bool LeftOpNode::checkError(bool check_ini, bool check_cons) {   
    bool l_err;

    l_err = left->checkError(true, true);

    return l_err;
}


void LeftOpNode::execute() {
    if(this->checkError())
        return;

    left->execute();
    if(getType() != left->getType())
        convtStack(left->getType(), getType());
    
    updateSymbolTable(left->getName(), true, true);

    pushToStack("1", _TYPE_INT);
    
    if(this->pushTwice)
        left->execute();
            
    switch (opr)
    {
        case _INC_OPR:
            writeAssembly(string_format("\tADD\n"));
            popFromStack(left->getName(), left->getType());
            return;
        case _DEC_OPR:
            writeAssembly(string_format("\tSUB\n"));
            popFromStack(left->getName(), left->getType());
            return;
    }

    // printf("\nError occured in LeftOpNode::execute() in left_operand.cpp\n");
}

LeftOpNode::~LeftOpNode() {
    if(left)    delete left;
}