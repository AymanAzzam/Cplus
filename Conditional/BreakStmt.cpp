#include "BreakStmt.h"
#include <iostream>

void BreakStmt::execute() {
    if (breakLabels.size() < 1) {
        printf("Error: break statement not within loop or switch block.\n");
    }
    else {
        int breakLabel = breakLabels[breakLabels.size() - 1];
        printf("JMP lbl%i\n", breakLabel);
    }
}
