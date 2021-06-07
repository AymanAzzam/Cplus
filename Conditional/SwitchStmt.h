#ifndef LEX_AND_YACC_SWITCHSTMT_H
#define LEX_AND_YACC_SWITCHSTMT_H

#include "../Node.h"
#include "../Stmt.h"
#include "../Expr.h"
#include "../StmtList.h"
#include <vector>
#include <iostream>

using namespace std;

class Case : public Node {
private:
    int caseLabel = -1;
    Expr *expr;
    StmtList *stmtList;
public:
//    TODO make sure it is a constant expression
    Case(Expr *expr, StmtList *stmtList)
            : expr(expr), stmtList(stmtList) {}

    explicit Case(Expr *expr)
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
            cout << "L" << caseLabel << ":";
        if (stmtList)
            stmtList->execute();
    }

    ~Case() {
        delete expr;
        delete stmtList;
    }
};

class Cases : public Node {
private:
    vector<Case *> cases;
public:
    int defaultCaseIndex = -1;

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
        for (Case* aCase:cases)
            aCase->execute();
    }

    ~Cases() {
        for (Case *aCase:cases)
            delete aCase;
    }
};

class SwitchStmt : public Stmt {
private:
    Cases *cases;
public:
    explicit SwitchStmt(Cases *cases) : cases(cases) {
    }

    // empty body switch
    SwitchStmt() : cases(nullptr) {}

    void execute() override {
        cout << "ex switch" << endl;
        int switchBreakLabel = labelNumber++;
        breakLabel.push(switchBreakLabel);
        cases->execute();
        cout << "L" << switchBreakLabel << ":" << endl;
        breakLabel.pop();
    }

    ~SwitchStmt() {
        delete cases;
    }
};

#endif //LEX_AND_YACC_SWITCHSTMT_H
