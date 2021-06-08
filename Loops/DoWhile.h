#pragma once
#include "../Node.h"
#include "../Stmt.h"

class DoWhile : public Stmt {
    Node *stmt, *cond;
    int contLabel, breakLabel;
public:
    DoWhile(Node*, Node*);
    void execute();
    ~DoWhile();
};
