#pragma once
#include "../Node.h"
#include "../Stmt.h"

class For : public Stmt {
    Node *f1, *f2, *f3;
    Stmt* stmt;
public:
    For(Node* , Node*, Node*, Stmt*);
    void execute();
    ~For();
};
