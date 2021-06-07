#ifndef LEX_AND_YACC_STMTLIST_H
#define LEX_AND_YACC_STMTLIST_H

#include <vector>
#include "Stmt.h"
#include "Node.h"

using namespace std;

class StmtList : public Node {
public:
    explicit StmtList(Stmt* firstStmt);
    ~StmtList();

    void execute() override;

    void push(Stmt *stmt);

private:
    vector<Stmt *> statements;
};


#endif //LEX_AND_YACC_STMTLIST_H
