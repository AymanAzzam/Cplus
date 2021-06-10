#ifndef LEX_AND_YACC_STMTLIST_H
#define LEX_AND_YACC_STMTLIST_H

#include <vector>
#include "Stmt.h"

using namespace std;

class StmtList : public Stmt {
private:
    vector<Stmt *> statements;
    bool shouldOpenScope = false;
public:
    StmtList() = default;

    explicit StmtList(Stmt *firstStmt);

    ~StmtList();

    void execute() override;

    void push(Stmt *stmt);

    void setShouldOpenScope(bool value);


};


#endif //LEX_AND_YACC_STMTLIST_H
