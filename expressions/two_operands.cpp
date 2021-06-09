#include "expressions.h"


TwoOpNode::TwoOpNode(ExprNode* left, ExprNode* right, Operator opr, int line): ExprNode() {
    this->left = left;
    this->right = right;
    this->opr = opr;
    this->line = line;
}

DataType TwoOpNode::getType() {
    this->type = typeConversion(left->getType(), right->getType(), opr);
}

bool TwoOpNode::checkError(bool check_ini, bool check_cons) {
    check_ini = opr != _EQ;
    check_cons = isAssignmentOp(opr);
    bool l_err, r_err;
    
    r_err = right->checkError();

    l_err = left->checkError(check_ini, check_cons);


    return l_err || r_err;
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
            writeAssembly(string_format("\tREM\n"));
            return;
        case _MUL:
            writeAssembly(string_format("\tMUL\n"));
            return;
        case _DIV:
            writeAssembly(string_format("\tDIV\n"));
            return;
        case _SUB:
            writeAssembly(string_format("\tSUB\n"));
            return;
        case _ADD:
            writeAssembly(string_format("\tADD\n"));
            return;

        // assignment operators
        case _MOD_EQ:
            writeAssembly(string_format("\tREM\n"));
            popFromStack(left->getName());
            return;
        case _MULT_EQ:
            writeAssembly(string_format("\tMUL\n"));
            popFromStack(left->getName());
            return;
        case _DIV_EQ:
            writeAssembly(string_format("\tDIV\n"));
            popFromStack(left->getName());
            return;
        case _MINUS_EQ:
            writeAssembly(string_format("\tSUB\n"));
            popFromStack(left->getName());
            return;
        case _PLUS_EQ:
            writeAssembly(string_format("\tADD\n"));
            popFromStack(left->getName());
            return;
        case _EQ:
            popFromStack(left->getName());
            return;

        // comparison operators
        case _LTE:
            writeAssembly(string_format("\tcompLTE\n"));
            return;
        case _GTE:
            writeAssembly(string_format("\tcompGTE\n"));
            return;
        case _LT:
            writeAssembly(string_format("\tcompLT\n"));
            return;
        case _GT:
            writeAssembly(string_format("\tcompGT\n"));
            return;
        case _NOT_EQ:
            writeAssembly(string_format("\tcompNE\n"));
            return;
        case _IS_EQ:
            writeAssembly(string_format("\tcompEQ\n"));
            return;
        
        // bitwise operators
        case _SHL:
            writeAssembly(string_format("\tSHL\n"));
            return;
        case _SHR:
            writeAssembly(string_format("\tSHR\n"));
            return;
        case _BIT_XOR:
            writeAssembly(string_format("\tXOR\n"));
            return;
        case _BIT_OR:
            writeAssembly(string_format("\tOR\n"));
            return;
        case _BIT_AND:
            writeAssembly(string_format("\tAND\n"));
            return;
        
        // logical operators
        case _LOGICAL_AND:
            writeAssembly(string_format("\tlogicAND\n"));
            return;
        case _LOGICAL_OR:
            writeAssembly(string_format("\tlogicOR\n"));
            return;
    }
            
    // printf("\nError occured in TwoOpNode::execute() in two_operand.cpp\n");
}
 

TwoOpNode::~TwoOpNode() {
    if(left)    delete left;
    if(right)   delete right;
}
