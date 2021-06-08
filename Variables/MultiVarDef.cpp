#include "MultiVarDef.h"

MultiVarDef::MultiVarDef(VarDeclare* s) {
    type = s->getType();
    push(s);
}

void MultiVarDef::push(VarDeclare* s) {
    definitions.push_back(s);
}

void MultiVarDef::setType(TypeNode* t) {
    type = t;
}

TypeNode* MultiVarDef::getType() {
    return type;
}

void MultiVarDef::execute() {
    for (VarDeclare* s : definitions) {
        s->execute();
    }
}

MultiVarDef::~MultiVarDef() {
    for (VarDeclare* s : definitions) {
        delete s;
    }
}
