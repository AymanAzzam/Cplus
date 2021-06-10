#include <iostream>
#include "For.h"
#include "../utilities.h"
#include "../SymbolTable/SymbolTable.h"

For::For(ExprNode* a, ExprNode* b, ExprNode* c, Stmt* s) {
    pre = a;
    cond = b;
    post = c;
    stmt = s;
}

void For::execute() {
    SymbolTable* sym = SymbolTable::GetInstance();

    sym->startScope(LOOP);

    int startLabel = labelNumber++;

    continueLabel.push(labelNumber++);
    breakLabel.push(labelNumber++);

    if (pre) pre->execute();
    writeAssembly(string_format("L%i:", startLabel));
    if (cond) cond->execute();
    writeAssembly(string_format("JZ L%i", breakLabel.top()));
    stmt->execute();
    writeAssembly(string_format("L%i:", continueLabel.top()));
    if (post) post->execute();
    writeAssembly(string_format("JMP L%i", startLabel));
    writeAssembly(string_format("L%i:", breakLabel.top()));

    continueLabel.pop();
    breakLabel.pop();

    vector<pair<string, int>> unused = sym->finishScope();
    for (auto u: unused) {
        log(string_format("Warning:%i: Variable declared but not used: %s.", u.second, u.first.c_str()));
    }
}

For::~For() {
    delete pre;
    delete cond;
    delete post;
    delete stmt;
}
