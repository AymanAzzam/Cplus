#pragma once
#include "../expressions/expressions.h"
#include "../Stmt.h"

class DoWhile : public Stmt {
    Stmt *stmt;
    ExprNode *cond;
public:
    DoWhile(Stmt*, ExprNode*);
    void execute();
    ~DoWhile();
};
