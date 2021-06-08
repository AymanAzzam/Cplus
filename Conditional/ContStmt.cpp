#include "contStmt.h"
#include <iostream>

void ContStmt::execute() {
    if (contLabels.size() < 1) {
        printf("Error: continue statement not within a loop.\n");
    }
    else {
        int contLabel = contLabels[contLabels.size() - 1];
        printf("JMP lbl%i\n", contLabel);
    }
}
