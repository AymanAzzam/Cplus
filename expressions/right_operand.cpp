#include "expressions.h"

RightOpNode::RightOpNode(ExprNode* right, Operator opr, int line): ExprNode(){
    this->right = right;
    this->opr = opr;
    this->line = line;
}

DataType RightOpNode::getType() {
    if(opr == _LOGICAL_NOT && right->getType() != _TYPE_BOOL)
    {
        this->type = _TYPE_BOOL; 
        
        log(string_format("Warning: Type mismatch, converting %s to bool", \
                typeToString(right->getType()).c_str()));
        convtStack(right->getType(), _TYPE_BOOL);
    }
    else
        this->type = right->getType();

    return type;
}

bool RightOpNode::checkError(bool check_ini, bool check_cons) {    
    check_cons = (opr == _INC_OPR || opr == _DEC_OPR);
    bool r_error;

    r_error = right->checkError(true, check_cons);

    return r_error;
}


void RightOpNode::execute() {
    if(this->checkError())
        return;

    right->execute();
    if(getType() != right->getType())
        convtStack(right->getType(), type);

    switch (opr)
    {
        case _BIT_NOT:
            writeAssembly(string_format("\tNOT"));
            return;
        case _LOGICAL_NOT:
            writeAssembly(string_format("\tlogicNOT"));
            return;
        case _INC_OPR:
            pushToStack("1", _TYPE_INT);
            writeAssembly(string_format("\tADD"));
            popFromStack(right->getName(), right->getType());
            writeAssembly(string_format("\tPUSH\t%s", right->getName().c_str()));
            return;
        case _DEC_OPR:
            pushToStack("1", _TYPE_INT);
            writeAssembly(string_format("\tSUB"));
            popFromStack(right->getName(), right->getType());
            pushToStack(right->getName(), right->getType());
            return;
        case _ADD:
            return;
        case _SUB:
            writeAssembly(string_format("\tNEG"));
            return;
    }
}


RightOpNode::~RightOpNode() {
    if(right)   delete right;
}