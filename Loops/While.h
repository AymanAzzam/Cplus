#pragma once
#include "../Node.h"
#include "../Stmt.h"

class While : public Stmt {
    Node *cond, *s;
public:
    While(Node*, Node*);
    void execute();
};
