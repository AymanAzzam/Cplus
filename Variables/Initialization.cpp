#include "Initialization.h"

VarInit::VarInit(DataType type, std::string name, std::string v, int lineno) {
    value = v;
    // addSymbol - uninitialized
}

void VarInit::execute() {
    printf("push %s\n", value);
    printf("pop %s\n", name);
}
