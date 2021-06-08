//
// Created by knassar on 6/8/21.
//

#include "Function.h"

FunctionParameters::FunctionParameters(ExprNode* baseParam){ parameters.push_back(baseParam); }

FunctionParameters *FunctionParameters::push(ExprNode *otherParam) {
    parameters.push_back(otherParam);
    return this;
}

FunctionHeader::FunctionHeader(TypeNode *tnode, IdentifierNode *id, FunctionParameters *param)
        :type(tnode), funcIdentifier(id), parameter(param){}

Function::Function(FunctionHeader *hdr, StmtList *blck) :header(hdr), block(blck){}

FunctionCall::FunctionCall(IdentifierNode *fId, FunctionArguments *args) :funcIdentifier(fId), funcArgs(args){}

FunctionArguments::FunctionArguments(ExprNode *baseExpr) {
    expressions.push_back(baseExpr);
}

FunctionArguments *FunctionArguments::push(ExprNode *otherExpr) {
    expressions.push_back(otherExpr);
    return this;
}

FunctionReturn::FunctionReturn(ExprNode* ret){
    // Check if valid ret type, ow: error!
}
