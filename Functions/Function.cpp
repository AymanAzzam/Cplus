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
        printf("POP %s %s\n", typeToString(type).c_str(), name.c_str());
    }
}

FunctionHeader::FunctionHeader(TypeNode *tnode, IdentifierNode *id, FunctionParameters *param, int line)
        :type(tnode), funcIdentifier(id), parameter(param), lineNo(line){}

void FunctionHeader::execute() {
    parameter->execute();
    SymbolTable* st = SymbolTable::GetInstance();
    vector<pair<string, DataType>> parameterList;
    for (VarDeclare* var: parameter->parameters){
        parameterList.emplace_back(var->getName()->getName(), var->getType()->getType());
    }
    st->insertFunc(funcIdentifier->getName(), lineNo, type->getType(), parameterList);
    printf("PROC %s\n", funcIdentifier->getName().c_str());
}

Function::Function(FunctionHeader *hdr, StmtList *blck, int line) :header(hdr), block(blck), lineNo(line){}

void Function::execute() {
    header->execute();
    block->execute();

    SymbolTable* st = SymbolTable::GetInstance();
    st->finishScope();
    printf("ENDP %s\n", header->funcIdentifier->getName().c_str());
}

FunctionCall::FunctionCall(IdentifierNode *fId, FunctionArguments *args, int line)
        :funcIdentifier(fId), funcArgs(args), lineNo(line){}

string FunctionCall::getName() {
    return funcIdentifier->getName();
}

void FunctionCall::execute() {
    funcArgs->execute();
    SymbolTable* st = SymbolTable::GetInstance();
    vector<DataType>parameterList;
    if(st->lookupFunc(funcIdentifier->getName(), parameterList)) {
        if (funcArgs->expressions.size() != parameterList.size()){
            printf("Error:%i:  number of parameters mismatch. required: %zu, found: %zu.\n",
                   lineNo, parameterList.size(), funcArgs->expressions.size());

        }else {
            for (int i = 0; i < funcArgs->expressions.size(); i++) {
                DataType curr = funcArgs->expressions[i]->type, expected = parameterList[i];
                if (curr != expected) {
                    printf("Warning:%i: conversion from type %s to %s.\n",
                           lineNo, typeToString(curr).c_str(), typeToString(expected).c_str());
                }
            }
            printf("CALL %s\n", funcIdentifier->getName().c_str());
        }
    }
}

FunctionArguments::FunctionArguments(ExprNode *baseExpr) {
    expressions.push_back(baseExpr);
}

FunctionArguments *FunctionArguments::push(ExprNode *otherExpr) {
    expressions.push_back(otherExpr);
    return this;
}

void FunctionArguments::execute() {
    for (ExprNode* expr: expressions){
        expr->execute();
    }
}

FunctionReturn::FunctionReturn(ExprNode* ret, int line):retExpr(ret), lineNo(line){}

void FunctionReturn::execute() {
    retExpr->execute();
    SymbolTable* st = SymbolTable::GetInstance();
    if (!st->canReturn(retExpr->getType())){
        printf("Warning:%i: Return type mismatch.\n", lineNo);
    }
    printf("RET\n");
}
