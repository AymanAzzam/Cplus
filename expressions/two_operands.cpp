#include "expressions.h"
#include "../utilities.h"


TwoOpNode::TwoOpNode(ExprNode* l, ExprNode* r, Operator o): ExprNode() {
    left = l;
    right = r;
    opr = o;
}

void TwoOpNode::checkError() {
    
    SymbolTable *symbolTable = SymbolTable::GetInstance();
    DataType left_type, right_type;
    string left_s, right_s;
    bool l_con, l_ini, l_error, r_con, r_ini, r_error;
    l_error = symbolTable->lookupId(left->name, left_type, l_ini, l_con);
    r_error = symbolTable->lookupId(left->name, right_type, r_ini, r_con);
    
    if(!l_error || !r_error)
        return;
    if(!r_ini)
    {
        printf("\n\nError: uninitialized variable %s\n\n", left->name.c_str());
        return;
    }
    else if((left_type == _TYPE_CHAR && right_type != _TYPE_CHAR) || \
            (left_type != _TYPE_CHAR && right_type == _TYPE_CHAR))
    {
        left_s = typeToString(left_type);
        right_s = typeToString(right_type);
        
        printf("\n\nType Error: %s type is %s can't be %s", \
                left->name.c_str(), left_s.c_str(), right_s.c_str());
        return;
    }
}

void TwoOpNode::execute() {

    left->checkError();
    right->checkError();
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
            printf("\tPOP\t%s\n", left->name.c_str());
            return;
        case _MULT_EQ:
            printf("\tMUL\n");
            printf("\tPOP\t%s\n", left->name.c_str());
            return;
        case _DIV_EQ:
            printf("\tDIV\n");
            printf("\tPOP\t%s\n", left->name.c_str());
            return;
        case _MINUS_EQ:
            printf("\tSUB\n");
            printf("\tPOP\t%s\n", left->name.c_str());
            return;
        case _PLUS_EQ:
            printf("\tADD\n");
            printf("\tPOP\t%s\n", left->name.c_str());
            return;
        case _EQ:
            printf("\tPOP\t%s\n", left->name.c_str());
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
