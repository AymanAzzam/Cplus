#ifndef LEX_AND_YACC_STMT_H
#define LEX_AND_YACC_STMT_H

#include "Node.h"

class Stmt : public Node {
public:
    void execute() override;
};


#endif //LEX_AND_YACC_STMT_H
