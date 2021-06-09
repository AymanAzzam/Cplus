#include "expressions.h"


TwoOpNode::TwoOpNode(ExprNode* left, ExprNode* right, Operator opr, int line): ExprNode() {
    this->left = left;
    this->right = right;
    this->opr = opr;
    this->line = line;

    this->type = typeConversion(left->getType(), right->getType(), opr);
}

bool TwoOpNode::checkError(bool check_ini, bool check_cons) {
    check_ini = opr != _EQ;
    check_cons = isAssignmentOp(opr);
    bool l_err, r_err;
    
    r_err = right->checkError();

    l_err = left->checkError(check_ini, check_cons);


    return l_err || r_err;

    /* printf("left = %s \t right = %s \t me = %s\n", typeToString(left->type).c_str(), \
             typeToString(right->type).c_str(), typeToString(this->type).c_str());
    */
}

void TwoOpNode::execute() {

    this->checkError();

    LeftOpNode* right_casted = dynamic_cast<LeftOpNode*>(right);
    if(right_casted != NULL)
        right_casted->setPushTwice(true);

    right->execute();
    if(this->type != this->right->type)
        convtStack(this->right->type, this->type);
    
    if(opr != _EQ)
    {
        LeftOpNode* left_casted = dynamic_cast<LeftOpNode*>(left);
        if(left_casted != NULL)
            left_casted->setPushTwice(true);

        left->execute();
        if(this->type != this->left->type)
            convtStack(this->left->type, this->type);

        updateSymbolTable(left->getName(), true, true);
    }
    else
        updateSymbolTable(left->getName(), true, false);

        
    switch (opr)
    {
        // arithmetic operators
        case _REM:
            printf("\tREM\n");
            return;
        case _MUL:
            printf("\tMUL\n");
            return;
        case _DIV:
            printf("\tDIV\n");
            return;
        case _SUB:
            printf("\tSUB\n");
            return;
        case _ADD:
            printf("\tADD\n");
            return;

        // assignment operators
        case _MOD_EQ:
            printf("\tREM\n");
            popFromStack(left->getName());
            return;
        case _MULT_EQ:
            printf("\tMUL\n");
            popFromStack(left->getName());
            return;
        case _DIV_EQ:
            printf("\tDIV\n");
            popFromStack(left->getName());
            return;
        case _MINUS_EQ:
            printf("\tSUB\n");
            popFromStack(left->getName());
            return;
        case _PLUS_EQ:
            printf("\tADD\n");
            popFromStack(left->getName());
            return;
        case _EQ:
            popFromStack(left->getName());
            return;

        // comparison operators
        case _LTE:
            printf("\tcompLTE\n");
            return;
        case _GTE:
            printf("\tcompGTE\n");
            return;
        case _LT:
            printf("\tcompLT\n");
            return;
        case _GT:
            printf("\tcompGT\n");
            return;
        case _NOT_EQ:
            printf("\tcompNE\n");
            return;
        case _IS_EQ:
            printf("\tcompEQ\n");
            return;
        
        // bitwise operators
        case _SHL:
            printf("\tSHL\n");
            return;
        case _SHR:
            printf("\tSHR\n");
            return;
        case _BIT_XOR:
            printf("\tXOR\n");
            return;
        case _BIT_OR:
            printf("\tOR\n");
            return;
        case _BIT_AND:
            printf("\tAND\n");
            return;
        
        // logical operators
        case _LOGICAL_AND:
            printf("\tlogicAND\n");
            return;
        case _LOGICAL_OR:
            printf("\tlogicOR\n");
            return;
    }
            
    // printf("\nError occured in TwoOpNode::execute() in two_operand.cpp\n");
}
 

TwoOpNode::~TwoOpNode() {
    if(left)    delete left;
    if(right)   delete right;
}
