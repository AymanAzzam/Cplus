#ifndef LEX_AND_YACC_STMT_H
#define LEX_AND_YACC_STMT_H

#include "Node.h"

class Stmt : public Node {
    Node* stmt;
public:
    Stmt(Node* s = nullptr);
    virtual void execute() override;
    ~Stmt();
};


#endif //LEX_AND_YACC_STMT_H
