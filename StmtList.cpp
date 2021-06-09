#include "StmtList.h"
#include "SymbolTable/SymbolTable.h"

StmtList::~StmtList() {
    for (Stmt *stmt:statements)
        delete stmt;
}

void StmtList::execute() {
    SymbolTable *sym = SymbolTable::GetInstance();
    if (shouldOpenScope)
        sym->startScope(BLOCK);
    for (Stmt *stmt:statements)
        if (stmt) stmt->execute();
    if (shouldOpenScope)
        sym->finishScope();
}

void StmtList::push(Stmt *stmt) {
    statements.push_back(stmt);
}

StmtList::StmtList(Stmt *firstStmt) {
    push(firstStmt);
}

void StmtList::setShouldOpenScope(bool value) {
    shouldOpenScope = value;
}
