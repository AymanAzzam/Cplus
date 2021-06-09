#ifndef LEX_AND_YACC_SWITCHSTMT_H
#define LEX_AND_YACC_SWITCHSTMT_H

#include "../Node.h"
#include "../Stmt.h"
#include "../expressions/expressions.h"
#include "../StmtList.h"
#include <vector>
#include <string>
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
            writeAssembly(string_format("L%d:", caseLabel));

        if (stmtList)
            stmtList->execute();
    }

    void evalExp() {
        if (!validateCaseExpression())
            return;
        expr->execute();
        DataType type = expr->getType();
        if (type == _TYPE_BOOL || type == _TYPE_CHAR) {
            convtStack(type, _TYPE_INT);
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
            pushToStack(string_format("%d_SWITCH", switchVariable), _TYPE_INT);
            writeAssembly(string_format("\tcompEQ"));
            writeAssembly(string_format("\tJNZ L%i", (aCase->hasBody() ? labelNumber++ : labelNumber)));
        }
        writeAssembly(string_format("\tJMP L%i", (defaultLabel != -1 ? defaultLabel : breakLabel.top())));
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
    ExprNode *condExpr;

    bool validateSwitchExpression() {
        DataType type = condExpr->getType();
        if (type == _TYPE_VOID || type == _TYPE_FLOAT) {
            log(string_format("Error: switch expression can't be of type float"));
            return false;
        }
        return true;
    }

public:
    SwitchStmt(ExprNode *condExpr, Cases *cases) : condExpr(condExpr), cases(cases) {
    }

    // empty body switch
    explicit SwitchStmt(ExprNode *condExpr) : condExpr(condExpr), cases(nullptr) {}

    void execute() override {
        SymbolTable *sym = SymbolTable::GetInstance();
        sym->startScope(_SWITCH);
        if (!validateSwitchExpression())
            return;
        condExpr->execute();
        int switchVariable = labelNumber++;
        if (condExpr->getType() != _TYPE_INT)
            convtStack(condExpr->getType(), _TYPE_INT);
        popFromStack(string_format("%d_SWITCH", switchVariable), _TYPE_INT);
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
