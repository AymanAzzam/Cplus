
#ifndef LEX_AND_YACC_CONDEXPR_H
#define LEX_AND_YACC_CONDEXPR_H


#include "Node.h"

class CondExpr : public Node {
public:
    void execute() override;
};


#endif //LEX_AND_YACC_CONDEXPR_H
