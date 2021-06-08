//
// Created by knassar on 6/8/21.
//

#include "Function.h"
#include "../utilities.h"

FunctionParameters::FunctionParameters(VarDeclare* baseParam){ parameters.push_back(baseParam); }

FunctionParameters *FunctionParameters::push(VarDeclare *otherParam) {
    parameters.push_back(otherParam);
    return this;
}

void FunctionParameters::execute() {
    for (VarDeclare* param: parameters){
        DataType type = param->getType()->getType();
        string name = param->getName()->getName();
        printf("push %s %s\n", typeToString(type).c_str(), name.c_str());
    }
}

FunctionHeader::FunctionHeader(TypeNode *tnode, IdentifierNode *id, FunctionParameters *param)
        :type(tnode), funcIdentifier(id), parameter(param){}

void FunctionHeader::execute() {

}

Function::Function(FunctionHeader *hdr, StmtList *blck) :header(hdr), block(blck){}

void Function::execute() {

}

FunctionCall::FunctionCall(IdentifierNode *fId, FunctionArguments *args) :funcIdentifier(fId), funcArgs(args){}

string FunctionCall::getName() {
    return std::__cxx11::string();
}

void FunctionCall::execute() {

}

FunctionArguments::FunctionArguments(ExprNode *baseExpr) {
    expressions.push_back(baseExpr);
}

FunctionArguments *FunctionArguments::push(ExprNode *otherExpr) {
    expressions.push_back(otherExpr);
    return this;
}

void FunctionArguments::execute() {

}

FunctionReturn::FunctionReturn(ExprNode* ret){
    // Check if valid ret type, ow: error!
}

void FunctionReturn::execute() {

}
