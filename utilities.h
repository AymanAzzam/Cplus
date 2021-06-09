#ifndef UTILITIES__H
#define UTILITIES__H


#include <string>
#include "constants.h"

using namespace std;


string oprToString(Operator opr);

string typeToString(DataType type);

DataType typeConversion(DataType left, DataType right, Operator opr);

void writeAssembly(const string& s);

void log(const string& s);

template<typename ... Args>
string string_format(const std::string &format, Args ... args);

#endif