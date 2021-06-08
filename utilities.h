#ifndef UTILITIES__H
#define UTILITIES__H


#include <string>
#include "constants.h"
using namespace std;

string oprToString(Operator opr);
string typeToString(DataType type);

DataType typeConversion(DataType left, DataType right, Operator opr);

void pushToStack(string name, DataType type);
void popFromStack(string name);

#endif