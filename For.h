#pragma once
#include "Node.h"
#include "Statement.h"

class For : public Statement {
    Node *f1, *f2, *f3, *s;
public:
    For(Node* , Node*, Node*, Node*);
    void execute();
};
