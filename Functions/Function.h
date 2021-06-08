//
// Created by knassar on 6/8/21.
//

#ifndef LEX_AND_YACC_FUNCTION_H
#define LEX_AND_YACC_FUNCTION_H

#include "../Node.h"
#include "../expressions/expressions.h"
#include "../StmtList.h"
#include "../Variables/Declaration.h"

class FunctionParameters : public Node
{
    vector<VarDeclare *> parameters;

public:
    explicit FunctionParameters(VarDeclare *baseParam);
    FunctionParameters *push(VarDeclare *otherParam);
    void execute() override;
};

class FunctionHeader : public Node
{
    TypeNode *type;
    IdentifierNode *funcIdentifier;
    FunctionParameters *parameter;

public:
    FunctionHeader(TypeNode *tnode, IdentifierNode *id, FunctionParameters *param);
    void execute() override;
};

class Function : public Node
{
    FunctionHeader *header;
    StmtList *block;

public:
    Function(FunctionHeader *hdr, StmtList *blck);
    void execute() override;
};

class FunctionArguments : public Node
{
    vector<ExprNode *> expressions;

public:
    FunctionArguments(ExprNode *baseExpr);
    FunctionArguments *push(ExprNode *otherExpr);
    void execute() override;
};

class FunctionCall : public ExprNode
{
    IdentifierNode *funcIdentifier;
    FunctionArguments *funcArgs;

public:
    FunctionCall(IdentifierNode *fId, FunctionArguments *args);
    string getName() override;
    void execute() override;
};

class FunctionReturn : public Node
{
public:
    FunctionReturn(ExprNode *ret);
    void execute() override;
};

#endif //LEX_AND_YACC_FUNCTION_H
