#ifndef LEX_AND_YACC_STATEMENT_H
#define LEX_AND_YACC_STATEMENT_H

#include "Node.h"

class Statement : public Node {
public:
    void execute() override;
};


#endif //LEX_AND_YACC_STATEMENT_H
