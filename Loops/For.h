#pragma once
#include "../Node.h"
#include "../Stmt.h"

class For : public Stmt {
    Node *f1, *f2, *f3, *s;
public:
    For(Node* , Node*, Node*, Node*);
    void execute();
};
