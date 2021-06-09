#include "expressions.h"

RightOpNode::RightOpNode(ExprNode* right, Operator opr, int line): ExprNode(){
    this->right = right;
    this->opr = opr;
    this->line = line;

    if(opr == _LOGICAL_NOT && right->getType() != _TYPE_BOOL)
    {
        this->type = _TYPE_BOOL; 
        
        log(string_format("\nWarning: Type mismatch, converting %s to bool\n", \
                typeToString(right->getType()).c_str()));
    }
    else
        this->type = right->getType();
}

bool RightOpNode::checkError(bool check_ini, bool check_cons) {    
    check_cons = (opr == _INC_OPR || opr == _DEC_OPR);
    bool r_error;

    r_error = right->checkError(true, check_cons);

    return r_error;
}


void RightOpNode::execute() {
    this->checkError();

    right->execute();
    if(getType() != right->getType())
        convtStack(right->getType(), getType());

    updateSymbolTable(right->getName(), true, true);

    switch (opr)
    {
        case _BIT_NOT:
            writeAssembly(string_format("\tNOT\n"));
            return;
        case _LOGICAL_NOT:
            writeAssembly(string_format("\tlogicNOT\n"));
            return;
        case _INC_OPR:
            pushToStack("1", _TYPE_INT);
            writeAssembly(string_format("\tADD\n"));
            popFromStack(right->getName());
            writeAssembly(string_format("\tPUSH\t%s\n", right->getName().c_str()));
            return;
        case _DEC_OPR:
            pushToStack("1", _TYPE_INT);
            writeAssembly(string_format("\tSUB\n"));
            popFromStack(right->getName());
            pushToStack(right->getName(), right->getType());
            return;
        case _ADD:
            writeAssembly(string_format("\tADD\n"));
            return;
        case _SUB:
            writeAssembly(string_format("\tSUB\n"));
            return;
    }

    // printf("\nError occured in RightOpNode::execute() in right_operand.cpp\n");
}


RightOpNode::~RightOpNode() {
    if(right)   delete right;
}