#ifndef LEX_AND_YACC_JMPSTMT_H
#define LEX_AND_YACC_JMPSTMT_H

#include "Stmt.h"
#include "utilities.h"
#include "SymbolTable/SymbolTable.h"

using namespace std;

class BreakStmt : public Stmt {
public:

    void execute() override {
        SymbolTable* sym = SymbolTable::GetInstance();
        if (sym->canBreak()) {
            writeAssembly(string_format("\tJMP L%i", breakLabel.top()));
        } else {
            log("Error: break statement must be inside while or switch");
        }
    }
};

class ContinueStmt : public Stmt {
public:

    void execute() override {
        SymbolTable* sym = SymbolTable::GetInstance();
        if (sym->canContinue()) {
            writeAssembly(string_format("\tJMP L%i", continueLabel.top()));
        } else {
            log("Error: continue statement must be inside while or switch");
        }
    }
};

#endif //LEX_AND_YACC_JMPSTMT_H