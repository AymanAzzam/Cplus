#include "expressions.h"

LeftOpNode::LeftOpNode(ExprNode* l, Operator o): ExprNode(){
    left = l;
    opr = o;
}

void LeftOpNode::execute() {
    left->execute();

    switch (opr)
    {
        case _INC_OPR:
            printf("\tPUSH\tx\t1\n");
            left->execute();
            printf("\tADD\n");
            printf("\tPOP x\n");
            return;
        case _DEC_OPR:
            printf("\tPUSH\tx\t1\n");
            left->execute();
            printf("\tSUB\n");
            return;
    }
    printf("\n\nError occured in LeftOpNode::execute() in left_operand.cpp\n\n");
}

LeftOpNode::~LeftOpNode() {
    if(left)    delete left;
}