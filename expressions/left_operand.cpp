#include "expressions.h"

LeftOpNode::LeftOpNode(ExprNode* l, Operator o): ExprNode(){
    left = l;
    opr = o;
}

int LeftOpNode::getValue() {
    int l = left->getValue();

    switch (opr)
    {
        case INC_OPR:
            return l++;
        case DEC_OPR:
            return l--;
    }
    return -1;
}

LeftOpNode::~LeftOpNode() {
    if(left)    delete left;
}