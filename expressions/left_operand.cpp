#include "expressions.h"
string oprToString(Operator opr);
string typeToString(DataType type);

LeftOpNode::LeftOpNode(ExprNode* left, Operator opr, int line): ExprNode(){
    this->left = left;
    this->opr = opr;
    this-> line = line;
}

void LeftOpNode::checkError() {
    
    string s, o;
    bool l_con = true, l_ini = true, l_dec = true;
    IdentifierNode* casted;

    casted = dynamic_cast<IdentifierNode*>(left);
    if(casted != NULL)
    {
        SymbolTable *symbolTable = SymbolTable::GetInstance();
        l_dec = symbolTable->lookupId(casted->getName(), left->type, l_ini, l_con); 
    }
    
    if(!dec)
        printf("\n\nError in line %d: undeclared variable %s\n\n", \
                this->line, getName().c_str());
    else if(!l_ini)
        printf("\n\nError in line %d: uninitialized variable %s\n\n", \
                this->line, left->getName().c_str());
    else if(l_ini && l_con)
        printf("\n\nConstant Error in line %d: %s is constant\n\n", \
                this->line, left->getName().c_str());
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

    this->type = left->type;

    printf("\n\nError occured in LeftOpNode::execute() in left_operand.cpp\n\n");
}

LeftOpNode::~LeftOpNode() {
    if(left)    delete left;
}