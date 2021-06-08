//
// Created by knassar on 6/8/21.
//

#ifndef LEX_AND_YACC_FUNCTION_H
#define LEX_AND_YACC_FUNCTION_H

#include "../Node.h"
#include "../expressions/expressions.h"
#include "../StmtList.h"

class FunctionParameters: public Node{
    vector<ExprNode*> parameters;

public:
    FunctionParameters(ExprNode* baseParam);
    FunctionParameters *push(ExprNode *otherParam);
};

class FunctionHeader: public Node{
    TypeNode* type;
    IdentifierNode* funcIdentifier;
    FunctionParameters* parameter;

public:
    FunctionHeader(TypeNode* tnode, IdentifierNode* id, FunctionParameters* param);
};

class Function: public Node {
    FunctionHeader* header;
    StmtList* block;

public:
    Function(FunctionHeader* hdr, StmtList* blck);
};

class FunctionArguments: public Node{
    vector<ExprNode*> expressions;

public:
    FunctionArguments(ExprNode* baseExpr);
    FunctionArguments *push(ExprNode *otherExpr);
};

class FunctionCall: public ExprNode{
    IdentifierNode* funcIdentifier;
    FunctionArguments* funcArgs;

public:
    FunctionCall(IdentifierNode* fId, FunctionArguments* args);
};

class FunctionReturn: public Node{
public:
    FunctionReturn(ExprNode* ret);
};

#endif //LEX_AND_YACC_FUNCTION_H
