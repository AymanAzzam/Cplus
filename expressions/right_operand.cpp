#include "expressions.h"
string oprToString(Operator opr);
string typeToString(DataType type);

RightOpNode::RightOpNode(ExprNode* r, Operator o, int line): ExprNode(){
    right = r;
    opr = o;
    this->line = line;
}

void RightOpNode::checkError() {
    string s, o;
    bool r_con = true, r_ini = true, r_dec = true;
    
    IdentifierNode* casted;

    casted = dynamic_cast<IdentifierNode*>(right);
    if(casted != NULL)
    {
        SymbolTable *symbolTable = SymbolTable::GetInstance();
        r_dec = symbolTable->lookupId(casted->getName(), right->type, r_ini, r_con); 
    }
    
    if(!r_dec)
        printf("\n\nError in line %d: undeclared variable %s\n\n", \
                this->line, getName().c_str());
    else if(!r_ini)
        printf("\n\nError in line %d: uninitialized variable %s\n\n", \
                this->line, right->getName().c_str());
    else if(r_ini && r_con && (opr == _INC_OPR || opr == _DEC_OPR))
        printf("\n\nConstant Error in line %d: %s is constant\n\n", \
                this->line, right->getName().c_str());
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
            printf("\tPOP\t%s\n", right->getName().c_str());
            printf("\tPUSH\t%s\n", right->getName().c_str());
            return;
        case _DEC_OPR:
            printf("\tPUSH\t1\n");
            printf("\tSUB\n");
            printf("\tPOP\t%s\n", right->getName().c_str());
            printf("\tPUSH\t%s\n", right->getName().c_str());
            return;
        case _ADD:
            printf("\tADD\n");
            return;
        case _SUB:
            printf("\tSUB\n");
            return;
    }

    if(opr != _LOGICAL_NOT && right->type != _TYPE_BOOL)
    {
        this->type = _TYPE_BOOL; 
        
        printf("\n\nWarning: Type mismatch, converting %s to bool", \
                typeToString(right->type).c_str());
    }
    else
        this->type = right->type;
    printf("\n\nError occured in RightOpNode::execute() in right_operand.cpp\n\n");
}


RightOpNode::~RightOpNode() {
    if(right)   delete right;
}