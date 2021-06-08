#include "expressions.h"
string oprToString(Operator opr);
string typeToString(DataType type);

LeftOpNode::LeftOpNode(ExprNode* l, Operator o): ExprNode(){
    left = l;
    opr = o;
}

void LeftOpNode::checkError() {
    
    SymbolTable *symbolTable = SymbolTable::GetInstance();
    DataType type;
    string s, o;
    bool con, ini, dec;
    
    dec = symbolTable->lookupId(left->getName(), type, ini, con);
    
    if(!dec)
        printf("\n\nError: undeclared variable %s\n\n", getName().c_str());
    else if(!ini)
        printf("\n\nError: uninitialized variable %s\n\n", left->getName().c_str());
    else if(ini && con)
        printf("\n\nConstant Error: %s is constant\n\n", left->getName().c_str());
    else if(type != _TYPE_INT)
    {
        s = typeToString(type);
        o = oprToString(opr);

        printf("\n\nWarning: Type mismatch, operation %s with %s", \
                o.c_str(), s.c_str());
    }
    
}

void LeftOpNode::execute() {
    this->checkError();

    left->execute();

    switch (opr)
    {
        case _INC_OPR:
            printf("\tPUSH\t1\n");
            left->execute();
            printf("\tADD\n");
            printf("\tPOP\t%s\n", left->getName().c_str());
            return;
        case _DEC_OPR:
            printf("\tPUSH\tx\t1\n");
            left->execute();
            printf("\tSUB\n");
            printf("\tPOP\t%s\n", left->getName().c_str());
            return;
    }
    printf("\n\nError occured in LeftOpNode::execute() in left_operand.cpp\n\n");
}

LeftOpNode::~LeftOpNode() {
    if(left)    delete left;
}