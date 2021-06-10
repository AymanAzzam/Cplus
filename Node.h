#ifndef LEX_AND_YACC_NODE_H
#define LEX_AND_YACC_NODE_H

#include <stack>
using namespace std;

class Node {
public:
    static int labelNumber;
    static stack<int> breakLabel;
    static stack<int> continueLabel;

    virtual void execute() = 0;
    virtual ~Node() = default;
};


#endif //LEX_AND_YACC_NODE_H
