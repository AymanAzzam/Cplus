#include "Program.h"

Program::Program(Node* g) {
    push(g);
}

void Program::push(Node* g) {
    global.push_back(g);
}

void Program::execute() {
    for (Node* g : global) {
        g->execute();
    }
}

// Program::~Program() {
//     for (Node* g : global) {
//         delete g;
//     }
// }
