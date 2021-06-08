#pragma once
#include "../Node.h"
#include "../Stmt.h"

class While : public Stmt {
    Node *cond, *stmt;
public:
    While(Node*, Node*);
    void execute();
    ~While();
};
