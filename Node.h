#ifndef LEX_AND_YACC_NODE_H
#define LEX_AND_YACC_NODE_H

#include <vector>


class Node {
public:
    static int labelNumber;
    static std::vector<int> contLabels;
    static std::vector<int> breakLabels;
    virtual void execute() = 0;
};


#endif //LEX_AND_YACC_NODE_H
