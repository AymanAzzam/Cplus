#include "MultiVarDef.h"

MultiVarDef::MultiVarDef(VarDeclare* s) {
    type = s->getType();
    push(s);
}

void MultiVarDef::push(VarDeclare* s) {
    definitions.push_back(s);
}

void MultiVarDef::setType(DataType t) {
    type = t;
}

DataType MultiVarDef::getType() {
    return type;
}

void MultiVarDef::execute() {
    for (VarDeclare* s : definitions) {
        printf("~~~ %s ~~~\n", typeToString(getType()).c_str());
        s->execute();
    }
}

MultiVarDef::~MultiVarDef() {
    for (VarDeclare* s : definitions) {
        delete s;
    }
}
