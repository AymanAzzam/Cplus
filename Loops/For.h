#pragma once
#include "../expressions/expressions.h"
#include "../Stmt.h"

class For : public Stmt {
    ExprNode *pre, *cond, *post;
    Stmt* stmt;
public:
    For(ExprNode*, ExprNode*, ExprNode*, Stmt*);
    void execute();
    ~For();
};
