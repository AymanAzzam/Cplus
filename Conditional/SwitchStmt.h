#ifndef LEX_AND_YACC_SWITCHSTMT_H
#define LEX_AND_YACC_SWITCHSTMT_H

#include "../Node.h"
#include "../Stmt.h"
#include "../expressions/expressions.h"
#include "../StmtList.h"
// #include "../SubExpr/CondExpr.h"
#include <vector>
#include <iostream>
#include "../utilities.h"
#include "../constants.h"

// TODO check switch expression type


using namespace std;

class Case : public Node {
private:
    int caseLabel = -1;
    ExprNode *expr;
    StmtList *stmtList;
    int line;
public:
    Case(ExprNode *expr, StmtList *stmtList, int line)
            : expr(expr), stmtList(stmtList), line(line) {}

    Case(ExprNode *expr, int line)
            : expr(expr), stmtList(nullptr), line(line) {}

    Case(StmtList *stmtList, int line)
            : expr(nullptr), stmtList(stmtList), line(line) {}

    Case(int line) : expr(nullptr), stmtList(nullptr), line(line) {}

    void setCaseLabel(int label) {
        caseLabel = label;
    }

    bool validateCaseExpression() {
        DataType type = expr->getType();
        if (type == _TYPE_FLOAT || type == _TYPE_VOID) {
            log(string_format("Error in line %d: case expression must be integer", line));
            return false;
        }
//        TODO is Expression constant
        return true;
    }

    void execute() override {
        if (caseLabel != -1)
            cout << "L" << caseLabel << ":" << endl;
        if (stmtList)
            stmtList->execute();
    }

    void evalExp() {
        validateCaseExpression();
        expr->execute();
        DataType type = expr->getType();
        if (type == _TYPE_BOOL || type == _TYPE_CHAR) {
            writeAssembly("CONVERT_TO_INT");
        }
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
        int startLabelNumber = labelNumber;
        int defaultLabel = -1;
        for (Case *aCase : cases) {
            if (aCase->isDefault()) {
                defaultLabel = (aCase->hasBody() ? labelNumber++ : labelNumber);
                continue;
            }
            aCase->evalExp();
            cout << "push " << switchVariable << "_switch" << endl;
            cout << "jnz " << "L" << (aCase->hasBody() ? labelNumber++ : labelNumber) << endl;
        }
        cout << "jmp L" << (defaultLabel != -1 ? defaultLabel : breakLabel.top()) << endl;
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
    Node *condExpr;

    // CondExpr *condExpr;
    bool validateSwitchExpression() {
        return true;
    }

public:
    SwitchStmt(Node *condExpr, Cases *cases) : condExpr(condExpr), cases(cases) {
    }

    // empty body switch
    explicit SwitchStmt(Node *condExpr) : condExpr(condExpr), cases(nullptr) {}

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
