//
// Created by knassar on 6/8/21.
//

#include "Function.h"
#include "../utilities.h"

FunctionParameters::FunctionParameters(VarDeclare *baseParam) { parameters.push_back(baseParam); }

FunctionParameters *FunctionParameters::push(VarDeclare *otherParam)
{
    parameters.push_back(otherParam);
    return this;
}

void FunctionParameters::execute()
{
    for (VarDeclare *param : parameters)
    {
        DataType type = param->getType();
        string name = param->getName();
        writeAssembly(string_format("POP %s %s\n", typeToString(type).c_str(), name.c_str()));
    }
}

FunctionHeader::FunctionHeader(TypeNode *tnode, IdentifierNode *id, FunctionParameters *param, int line)
    : type(tnode), funcIdentifier(id), parameter(param), lineNo(line) {}

void FunctionHeader::execute()
{
    writeAssembly(string_format("PROC %s\n", funcIdentifier->getName().c_str()));
    vector<pair<string, DataType>> parameterList;
    if (parameter)
    {
        parameter->execute();
        vector<VarDeclare *> &parameters = parameter->parameters;
        // TODO @KhaledMoataz Check this
        for (auto it= parameters.rbegin(); it != parameters.rend(); it++)
            parameterList.emplace_back((*it)->getName(), (*it)->getType());
    }
    SymbolTable *st = SymbolTable::GetInstance();
    st->insertFunc(funcIdentifier->getName(), lineNo, type->getType(), parameterList);
}

Function::Function(FunctionHeader *hdr, Stmt *blck, int line) : header(hdr), block(blck), lineNo(line) {}

void Function::execute()
{
    header->execute();
    if (block)
        block->execute();

    SymbolTable *st = SymbolTable::GetInstance();
    st->finishScope();
    writeAssembly(string_format("ENDP %s\n", header->funcIdentifier->getName().c_str()));
}

FunctionCall::FunctionCall(IdentifierNode *fId, FunctionArguments *args, int line)
    : funcIdentifier(fId), funcArgs(args), lineNo(line) {}

string FunctionCall::getName()
{
    return funcIdentifier->getName();
}

void FunctionCall::execute()
{
    if (funcArgs)
    {
        funcArgs->execute();
    }
    SymbolTable *st = SymbolTable::GetInstance();
    vector<DataType> parameterList;
    if (st->lookupFunc(funcIdentifier->getName(), parameterList))
    {
        type = parameterList[0];
        if (funcArgs != nullptr && funcArgs->expressions.size() != parameterList.size() - 1)
        {
            log(string_format("Error:%i:  number of parameters mismatch. required: %zu, found: %zu.\n",
                   lineNo, parameterList.size(), funcArgs->expressions.size()));
        }
        else
        {
            for (int i = 0; i < funcArgs->expressions.size(); i++)
            {
                DataType curr = funcArgs->expressions[i]->type, expected = parameterList[i + 1];
                if (curr != expected)
                {
                    log(string_format("Warning:%i: conversion from type %s to %s.\n",
                           lineNo, typeToString(curr).c_str(), typeToString(expected).c_str()));
                    convtStack(curr, expected);
                }
            }
            writeAssembly(string_format("CALL %s\n", funcIdentifier->getName().c_str()));
        }
    }
}

DataType FunctionCall::getType() {
    return type;
}

FunctionArguments::FunctionArguments(ExprNode *baseExpr)
{
    expressions.push_back(baseExpr);
}

FunctionArguments *FunctionArguments::push(ExprNode *otherExpr)
{
    expressions.push_back(otherExpr);
    return this;
}

void FunctionArguments::execute()
{
    for (ExprNode *expr : expressions)
    {
        expr->execute();
    }
}

FunctionReturn::FunctionReturn(ExprNode *ret, int line) : retExpr(ret), lineNo(line) {}

void FunctionReturn::execute()
{
    if (retExpr)
        retExpr->execute();
    SymbolTable *st = SymbolTable::GetInstance();
    DataType expType = retExpr ? retExpr->getType() : _TYPE_VOID;
    if (!st->canReturn(expType))
    {
        if (expType == _TYPE_VOID)
            log(string_format("Error:%i: Can't return void in %s function.\n", lineNo, typeToString(expType).c_str()));
        else if (st->canReturn(_TYPE_VOID))
            log(string_format("Error:%i: Can't return %s expression in void function.\n", lineNo,
                              typeToString(expType).c_str()));
        else
            log(string_format("Warning:%i: Return type mismatch.\n", lineNo));
    }
    writeAssembly(string_format("RET\n"));
}
