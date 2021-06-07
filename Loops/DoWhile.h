#pragma once
#include "../Node.h"
#include "../Stmt.h"

class DoWhile : public Stmt {
    Node *stmt, *cond;
public:
    DoWhile(Node*, Node*);
    void execute();
};
