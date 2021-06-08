#ifndef LEX_AND_YACC_STMTLIST_H
#define LEX_AND_YACC_STMTLIST_H

#include <vector>
#include "Stmt.h"

using namespace std;

class StmtList : public Stmt {
public:
    StmtList() = default;

    explicit StmtList(Stmt *firstStmt);

    ~StmtList();

    void execute() override;

    void push(Stmt *stmt);

    void test();

private:
    vector<Stmt *> statements;
};


#endif //LEX_AND_YACC_STMTLIST_H
