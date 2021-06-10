#include "expressions.h"


TwoOpNode::TwoOpNode(ExprNode* left, ExprNode* right, Operator opr, int line): ExprNode() {
    this->left = left;
    this->right = right;
    this->opr = opr;
    this->line = line;
}

DataType TwoOpNode::getType() {
    
    this->type = typeConversion(left->getType(), right->getType(), opr);
    
    if(isAssignmentOp(opr))
        this->type = left->getType();
    
    return type;
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

    if(this->checkError())
        return;

    this->getType();

    LeftOpNode* right_casted = dynamic_cast<LeftOpNode*>(right);
    if(right_casted != NULL)
        right_casted->setPushTwice(true);

    if(opr != _EQ)
    {
        LeftOpNode* left_casted = dynamic_cast<LeftOpNode*>(left);
        if(left_casted != NULL)
            left_casted->setPushTwice(true);

        left->execute();
        if(type != this->left->getType())
            convtStack(this->left->getType(), type);

        // updateSymbolTable(left->getName(), true, true);
    }
    // else
        // updateSymbolTable(left->getName(), true, false);

    right->execute();
    if(this->type != this->right->getType())
        convtStack(this->right->getType(), type);
    
        
    switch (opr)
    {
        // arithmetic operators
        case _REM:
            writeAssembly(string_format("\tREM"));
            return;
        case _MUL:
            writeAssembly(string_format("\tMUL"));
            return;
        case _DIV:
            writeAssembly(string_format("\tDIV"));
            return;
        case _SUB:
            writeAssembly(string_format("\tSUB"));
            return;
        case _ADD:
            writeAssembly(string_format("\tADD"));
            return;

        // assignment operators
        case _MOD_EQ:
            writeAssembly(string_format("\tREM"));
            popFromStack(left->getName(), left->getType());
            return;
        case _MULT_EQ:
            writeAssembly(string_format("\tMUL"));
            popFromStack(left->getName(), left->getType());
            return;
        case _DIV_EQ:
            writeAssembly(string_format("\tDIV"));
            popFromStack(left->getName(), left->getType());
            return;
        case _MINUS_EQ:
            writeAssembly(string_format("\tSUB"));
            popFromStack(left->getName(), left->getType());
            return;
        case _PLUS_EQ:
            writeAssembly(string_format("\tADD"));
            popFromStack(left->getName(), left->getType());
            return;
        case _EQ:
            popFromStack(left->getName(), left->getType());
            return;

        // comparison operators
        case _LTE:
            writeAssembly(string_format("\tcompLTE"));
            return;
        case _GTE:
            writeAssembly(string_format("\tcompGTE"));
            return;
        case _LT:
            writeAssembly(string_format("\tcompLT"));
            return;
        case _GT:
            writeAssembly(string_format("\tcompGT"));
            return;
        case _NOT_EQ:
            writeAssembly(string_format("\tcompNE"));
            return;
        case _IS_EQ:
            writeAssembly(string_format("\tcompEQ"));
            return;
        
        // bitwise operators
        case _SHL:
            writeAssembly(string_format("\tSHL"));
            return;
        case _SHR:
            writeAssembly(string_format("\tSHR"));
            return;
        case _BIT_XOR:
            writeAssembly(string_format("\tXOR"));
            return;
        case _BIT_OR:
            writeAssembly(string_format("\tOR"));
            return;
        case _BIT_AND:
            writeAssembly(string_format("\tAND"));
            return;
        
        // logical operators
        case _LOGICAL_AND:
            writeAssembly(string_format("\tlogicAND"));
            return;
        case _LOGICAL_OR:
            writeAssembly(string_format("\tlogicOR"));
            return;
    }
            
    // printf("Error occured in TwoOpNode::execute() in two_operand.cpp");
}
 

TwoOpNode::~TwoOpNode() {
    if(left)    delete left;
    if(right)   delete right;
}
