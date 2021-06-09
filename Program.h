#pragma once

#include "Node.h"
#include <vector>

class Program : public Node {
    std::vector<Node*> global;
public:
    Program(Node* g = nullptr);
    void push(Node* g);
    void execute();
    // ~Program();
};
