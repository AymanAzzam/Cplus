#pragma once
#include "Node.h"
#include "Statement.h"

class While : public Statement {
    Node *cond, *s;
public:
    While(Node*, Node*);
    void execute();
};
