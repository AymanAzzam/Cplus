#ifndef LEX_AND_YACC_NODE_H
#define LEX_AND_YACC_NODE_H


class Node {
public:
    static int labelNumber;
    virtual void execute() = 0;
};


#endif //LEX_AND_YACC_NODE_H
