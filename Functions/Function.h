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
public:
    vector<VarDeclare *> parameters;

    explicit FunctionParameters(VarDeclare *baseParam);
    FunctionParameters *push(VarDeclare *otherParam);
    void execute() override;
};

class FunctionHeader : public Node
{
    TypeNode *type;
    FunctionParameters *parameter;
    int lineNo;

public:
    FunctionHeader(TypeNode *tnode, IdentifierNode *id, FunctionParameters *param, int line);
    void execute() override;

    IdentifierNode *funcIdentifier;
};

class Function : public Node
{
    FunctionHeader *header;
    StmtList *block;
    int lineNo;

public:
    Function(FunctionHeader *hdr, StmtList *blck, int line);
    void execute() override;
};

class FunctionArguments : public Node
{
public:
    vector<ExprNode *> expressions;

    FunctionArguments(ExprNode *baseExpr);
    FunctionArguments *push(ExprNode *otherExpr);
    void execute() override;
};

class FunctionCall : public ExprNode
{
    IdentifierNode *funcIdentifier;
    FunctionArguments *funcArgs;
    int lineNo;

public:
    FunctionCall(IdentifierNode *fId, FunctionArguments *args, int line);
    string getName() override;
    void execute() override;
};

class FunctionReturn : public Stmt
{
    ExprNode* retExpr;
    int lineNo;

public:
    FunctionReturn(ExprNode *ret, int line);
    void execute() override;
};

#endif //LEX_AND_YACC_FUNCTION_H
