#pragma once
#include "../Node.h"
#include "../Stmt.h"

class While : public Stmt {
    Node *cond, *stmt;
    int breakLabel, contLabel;
public:
    While(Node*, Node*);
    void execute();
    ~While();
};
