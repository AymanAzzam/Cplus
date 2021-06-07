#pragma once

#include "../Node.h"
//#includde "Expression"

class EpsExpr : public Node { //Expression
    Node* expand;
public:
    EpsExpr(Node* = nullptr); //Expression*
    void execute();
};
