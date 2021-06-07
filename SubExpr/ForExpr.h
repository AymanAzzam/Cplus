#pragma once

#include "../Node.h"
//#includde "Expression"

class ForExpr : public Node { //Expression
    Node* expand;
public:
    ForExpr(Node*); //Expression*
    void execute();
};
