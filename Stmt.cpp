#include "Stmt.h"
#include <iostream>
using namespace std;

Stmt::Stmt(Node* s) {
    stmt = s;
}

void Stmt::execute() {
    if (stmt) stmt->execute();
}

Stmt::~Stmt() {
    delete stmt;
}
