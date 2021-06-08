#include "expressions.h"

RightOpNode::RightOpNode(ExprNode* r, Operator o): ExprNode(){
    right = r;
    opr = o;
}

void RightOpNode::checkError() {
    SymbolTable *symbolTable = SymbolTable::GetInstance();
    DataType type;
    string s;
    bool con, ini, success;
    
    success = symbolTable->lookupId(right->name, type, ini, con);
    
    if(!success)
        printf("\n\nError: undeclared variable %s\n\n", name.c_str());
    else if(!ini)
        printf("\n\nError: uninitialized variable %s\n\n", right->name.c_str());
    else if(ini && con && (opr == _INC_OPR || opr == _DEC_OPR))
        printf("\n\nConstant Error: %s is constant\n\n", right->name.c_str());
    
}

void RightOpNode::execute() {
    this->checkError();

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
            printf("\tPOP\t%s\n", right->name.c_str());
            printf("\tPUSH\t%s\n", right->name.c_str());
            return;
        case _DEC_OPR:
            printf("\tPUSH\t1\n");
            printf("\tSUB\n");
            printf("\tPOP\t%s\n", right->name.c_str());
            printf("\tPUSH\t%s\n", right->name.c_str());
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