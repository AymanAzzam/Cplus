#include "expressions.h"

TwoOpNode::TwoOpNode(ExprNode* l, ExprNode* r, Operator o): ExprNode() {
    left = l;
    right = r;
    opr = o;
}

/* int TwoOpNode::getValue() {
    int l = left->getValue();
    int r = left->getValue();

    switch (opr)
    {
        // arithmetic operators
        case REM:
            return l % r;
        case MUL:
            return l * r;
        case DIV:
            return l / r;
        case SUB:
            return l - r;
        case ADD:
            return l + r;
        
        // comparison operators
        case LTE:
            return l <= r;
        case GTE:
            return l >= r;
        case LT:
            return l < r;
        case GT:
            return l > r;
        case NOT_EQ:
            return l != r;
        case IS_EQ:
            return l == r;
        
        // bitwise operators
        case SHL:
            return l << r;
        case SHR:
            return l >> r;
        case BIT_XOR:
            return l ^ r;
        case BIT_OR:
            return l | r;
        case BIT_AND:
            return l & r;
        
        // logical operators
        case LOGICAL_AND:
            return l && r;
        case LOGICAL_OR:
            return l || r;
    }

    return -1;
}
 */
TwoOpNode::~TwoOpNode() {
    if(left)    delete left;
    if(right)   delete right;
}
