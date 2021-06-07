#include "expressions.h"

RightOpNode::RightOpNode(ExprNode* r, Operator o): ExprNode(){
    right = r;
    opr = o;
}


int RightOpNode::getValue() {
    int r = right->getValue();

    switch (opr)
    {
        case BIT_NOT:
            return ~r;
        case LOGICAL_NOT:
            return !r;
        case INC_OPR:
            return ++r;
        case DEC_OPR:
            return --r;
    }
    return -1;
}


RightOpNode::~RightOpNode() {
    if(right)   delete right;
}