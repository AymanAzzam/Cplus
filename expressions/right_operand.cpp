#include "expressions.h"

RightOpNode::RightOpNode(ExprNode* r, Operator o): ExprNode(){
    right = r;
    opr = o;
}


void RightOpNode::execute() {
    right->execute();

    switch (opr)
    {
        case _BIT_NOT:
            printf("\tNOT\n");
            return;
        case _LOGICAL_NOT:
            printf("\tlogicNOT\n");
            return;
        case _INC_OPR:
            printf("\tPUSH\t1\n");
            printf("\tADD\n");
            printf("\tPOP\tx\n");
            printf("\tPUSH\tx\n");
            return;
        case _DEC_OPR:
            printf("\tPUSH\t1\n");
            printf("\tSUB\n");
            printf("\tPOP\tx\n");
            printf("\tPUSH\tx\n");
            return;
        case _ADD:
            printf("\tADD\n");
            return;
        case _SUB:
            printf("\tSUB\n");
            return;
    }

    printf("\n\nError occured in RightOpNode::execute() in right_operand.cpp\n\n");
}


RightOpNode::~RightOpNode() {
    if(right)   delete right;
}