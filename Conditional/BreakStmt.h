#pragma once

#include "../Stmt.h"

class BreakStmt : public Stmt {
public:
    void execute();
};
