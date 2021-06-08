#include "StmtList.h"
    #include <iostream>

StmtList::~StmtList() {
    for (Stmt *stmt:statements)
        delete stmt;
}

void StmtList::execute() {
    test();
    for (Stmt *stmt:statements)
        stmt->execute();
}

void StmtList::push(Stmt *stmt) {
    statements.push_back(stmt);
}

StmtList::StmtList(Stmt *firstStmt) {
    push(firstStmt);
}

void StmtList::test() {
    printf("num: %i\n", statements.size());
    for (Stmt* stmt: statements) {
        printf("Stmt found\n");
    }
}
