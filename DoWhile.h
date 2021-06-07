#pragma once
#include "Node.h"
#include "Statement.h"

class While_node : public Statement {
    Node *cond, *s;
public:
    While_node(Node*, Node*);
    void execute();
};
