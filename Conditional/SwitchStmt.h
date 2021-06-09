#ifndef LEX_AND_YACC_SWITCHSTMT_H
#define LEX_AND_YACC_SWITCHSTMT_H

#include "../Node.h"
#include "../Stmt.h"
#include "../expressions/expressions.h"
#include "../StmtList.h"
#include "../SubExpr/CondExpr.h"
#include <vector>
#include <iostream>
#include "../utilities.h"

// TODO check switch expression type
// TODO check case expression type
// TODO make sure it is a constant expression


using namespace std;

class Case : public Node {
private:
    int caseLabel = -1;
    ExprNode *expr;
    StmtList *stmtList;
public:
    Case(ExprNode *expr, StmtList *stmtList)
            : expr(expr), stmtList(stmtList) {}

    explicit Case(ExprNode *expr)
            : expr(expr), stmtList(nullptr) {}

    explicit Case(StmtList *stmtList)
            : expr(nullptr), stmtList(stmtList) {}

    Case() : expr(nullptr), stmtList(nullptr) {}

    void setCaseLabel(int label) {
        caseLabel = label;
    }

    void execute() override {
        cout << "ex case" << endl;
        if (caseLabel != -1)
            cout << "L" << caseLabel << ":" << endl;
        if (stmtList)
            stmtList->execute();
    }

    void evalExp() {
        expr->execute();
    }

    bool isDefault() {
        return expr == nullptr;
    }

    bool hasBody() {
        return stmtList != nullptr;
    }

    ~Case() {
        delete expr;
        delete stmtList;
    }

};

class Cases : public Node {
private:
    vector<Case *> cases;
    vector<int> caseLabels;
public:
    int switchVariable;

    Cases *push(Case *aCase) {
        cases.push_back(aCase);
        return this;
    }

    Cases *push(Cases *otherCases) {
        cases.insert(cases.end(), otherCases->cases.begin(), otherCases->cases.end());
        return this;
    }

    void execute() override {
        cout << "ex cases" << endl;
        int startLabelNumber = labelNumber;
        int defaultLabel = -1;
        for (Case *aCase : cases) {
            if (aCase->isDefault()) {
                defaultLabel = (aCase->hasBody() ? labelNumber++ : labelNumber);
                continue;
            }
            aCase->evalExp();
            // TODO push_datatype
            writeAssembly(string_format("PUSH %d_SWITCH", switchVariable));
            writeAssembly(string_format("JNZ L%d", (aCase->hasBody() ? labelNumber++ : labelNumber)));
        }
        writeAssembly(string_format("JMP L%d", (defaultLabel != -1 ? defaultLabel : breakLabel.top())));
        for (Case *aCase:cases) {
            if (!aCase->hasBody()) continue;
            aCase->setCaseLabel(startLabelNumber++);
            aCase->execute();
        }
    }

    ~Cases() {
        for (Case *aCase:cases)
            delete aCase;
    }
};

class SwitchStmt : public Stmt {
private:
    Cases *cases;
    CondExpr *condExpr;

    bool validateSwitchExpression() {
        return true;
    }

public:
    SwitchStmt(CondExpr *condExpr, Cases *cases) : condExpr(condExpr), cases(cases) {
    }

    // empty body switch
    explicit SwitchStmt(CondExpr *condExpr) : condExpr(condExpr), cases(nullptr) {}

    void execute() override {
        SymbolTable *sym = SymbolTable::GetInstance();
        sym->startScope(_SWITCH);
        validateSwitchExpression();
        condExpr->execute();
        int switchVariable = labelNumber++;
        // TODO pop_datatype
        writeAssembly(string_format("POP %d_SWITCH", switchVariable));
        cases->switchVariable = switchVariable;
        int switchBreakLabel = labelNumber++;
        breakLabel.push(switchBreakLabel);
        cases->execute();
        writeAssembly(string_format("L%d:", switchBreakLabel));
        breakLabel.pop();
        sym->finishScope();
    }

    ~SwitchStmt() {
        delete cases;
    }
};

#endif //LEX_AND_YACC_SWITCHSTMT_H
