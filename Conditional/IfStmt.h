#ifndef LEX_AND_YACC_IFSTMT_H
#define LEX_AND_YACC_IFSTMT_H


#include "../Stmt.h"
// #include "../SubExpr/CondExpr.h"

class IfStmt : public Stmt {
public:
    Node *condExpr;
    Stmt *ifBody;
    Stmt *elseBody;

    IfStmt(Node *condExpr, Stmt *ifBody, Stmt *elseBody = nullptr);
    void execute() override;
    ~IfStmt();
};


#endif //LEX_AND_YACC_IFSTMT_H
