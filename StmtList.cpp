#include "StmtList.h"
    #include <iostream>

StmtList::~StmtList() {
    for (Stmt *stmt:statements)
        delete stmt;
}

void StmtList::execute() {
    for (Stmt *stmt:statements)
        stmt->execute();
}

void StmtList::push(Stmt *stmt) {
    statements.push_back(stmt);
}

StmtList::StmtList(Stmt *firstStmt) {
    push(firstStmt);
}
