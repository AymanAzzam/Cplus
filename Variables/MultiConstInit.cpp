#include "MultiConstInit.h"

MultiConstInit::MultiConstInit(ConstDef* c) {
    type = c->getType();
    push(c);
}

void MultiConstInit::push(ConstDef* c) {
    definitions.push_back(c);
}

void MultiConstInit::setType(DataType t) {
    type = t;
}

DataType MultiConstInit::getType() {
    return type;
}

void MultiConstInit::execute() {
    for (ConstDef* c : definitions) {
        c->execute();
    }
}

MultiConstInit::~MultiConstInit() {
    for (ConstDef* c : definitions) {
        delete c;
    }
}
