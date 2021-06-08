#include "expressions.h"
#include "../utilities.h"


TwoOpNode::TwoOpNode(ExprNode* l, ExprNode* r, Operator o, int line): ExprNode() {
    left = l;
    right = r;
    opr = o;
    this->line = line;
}

void TwoOpNode::checkError() {
    string left_s, right_s;
    bool l_con = true, l_ini = true, l_dec = true, \
            r_con = true, r_ini = true, r_dec = true;
    IdentifierNode* casted;

    casted = dynamic_cast<IdentifierNode*>(left);
    if(casted != NULL)
    {
        SymbolTable *symbolTable = SymbolTable::GetInstance();
        l_dec = symbolTable->lookupId(casted->getName(), left->type, l_ini, l_con); 
    }
    casted = dynamic_cast<IdentifierNode*>(right);
    if(casted != NULL)
    {
        SymbolTable *symbolTable = SymbolTable::GetInstance();
        r_dec = symbolTable->lookupId(casted->getName(), right->type, r_ini, r_con); 
    }
    if(!r_dec)
         printf("\n\nError in line %d: undeclared variable %s\n\n", \
                this->line, right->getName().c_str());
    else if(!l_dec)
         printf("\n\nError in line %d: undeclared variable %s\n\n", \
                this->line, left->getName().c_str());
    else if(!r_ini)
        printf("\n\nErrorin line %d: uninitialized variable %s\n\n", \
                this->line, right->getName().c_str());
    else if(!l_ini && opr != _EQ)
        printf("\n\nError in line %d: uninitialized variable %s\n\n", \
                this->line, left->getName().c_str());
    else if(l_con && ( opr == _MOD_EQ || opr == _MULT_EQ || opr == _DIV_EQ ||\
            opr == _MINUS_EQ || opr == _PLUS_EQ || opr == _EQ ))
        printf("\n\nConstant Error in line %d: %s is constant\n\n", \
                this->line, left->getName().c_str());
}

void TwoOpNode::execute() {

    this->checkError();

    left->execute();
    right->execute();

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
            printf("\tPOP\t%s\n", left->getName().c_str());
            return;
        case _MULT_EQ:
            printf("\tMUL\n");
            printf("\tPOP\t%s\n", left->getName().c_str());
            return;
        case _DIV_EQ:
            printf("\tDIV\n");
            printf("\tPOP\t%s\n", left->getName().c_str());
            return;
        case _MINUS_EQ:
            printf("\tSUB\n");
            printf("\tPOP\t%s\n", left->getName().c_str());
            return;
        case _PLUS_EQ:
            printf("\tADD\n");
            printf("\tPOP\t%s\n", left->getName().c_str());
            return;
        case _EQ:
            printf("\tPOP\t%s\n", left->getName().c_str());
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

    this->type = typeConversion(left->type, right->type, opr);
    
    printf("\n\nError occured in TwoOpNode::execute() in two_operand.cpp\n\n");
}
 

TwoOpNode::~TwoOpNode() {
    if(left)    delete left;
    if(right)   delete right;
}
