#include "expressions.h"
#include "../utilities.h"


TwoOpNode::TwoOpNode(ExprNode* l, ExprNode* r, Operator o): ExprNode() {
    left = l;
    right = r;
    opr = o;
}

void TwoOpNode::checkError() {
    SymbolTable *symbolTable = SymbolTable::GetInstance();
    string left_s, right_s;
    bool l_con = false, l_ini = true, l_dec = true, \
            r_con = false, r_ini = true, r_dec = true;
    IdentifierNode* casted;

    casted = dynamic_cast<IdentifierNode*>(left);
    if(casted != NULL)
        l_con = casted->con, l_ini = casted->ini, l_dec = casted->dec; 
    
    casted = dynamic_cast<IdentifierNode*>(right);
    if(casted != NULL)
        r_con = casted->con, r_ini = casted->ini, r_dec = casted->dec;

    if(!r_dec)
         printf("\n\nError: undeclared variable %s\n\n", right->getName().c_str());
    else if(!l_dec)
         printf("\n\nError: undeclared variable %s\n\n", left->getName().c_str());
    else if(!r_ini)
        printf("\n\nError: uninitialized variable %s\n\n", right->getName().c_str());
    else if(!l_ini && opr != _EQ)
        printf("\n\nError: uninitialized variable %s\n\n", left->getName().c_str());
    else if(l_con && ( opr == _MOD_EQ || opr == _MULT_EQ || opr == _DIV_EQ ||\
            opr == _MINUS_EQ || opr == _PLUS_EQ || opr == _EQ ))
        printf("\n\nConstant Error: %s is constant\n\n", left->getName().c_str());
    else if(left->getType() != right->getType())
    {
        left_s = typeToString(left->getType());
        right_s = typeToString(right->getType());
        
        printf("\n\nWarning: Type mismatch, converting %s to %s", \
                right_s.c_str(), left_s.c_str());
    }
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

    printf("\n\nError occured in TwoOpNode::execute() in two_operand.cpp\n\n");
}
 

TwoOpNode::~TwoOpNode() {
    if(left)    delete left;
    if(right)   delete right;
}
