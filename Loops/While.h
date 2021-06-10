#pragma once
#include "../expressions/expressions.h"
#include "../Stmt.h"

class While : public Stmt {
    ExprNode *cond;
    Stmt *stmt;
public:
    While(ExprNode*, Stmt*);
    void execute();
    ~While();
};
