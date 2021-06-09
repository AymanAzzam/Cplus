#ifndef UTILITIES__H
#define UTILITIES__H


#include <string>
#include "constants.h"
#include <memory>
#include <stdexcept>

using namespace std;


string oprToString(Operator opr);

string typeToString(DataType type);

DataType typeConversion(DataType left, DataType right, Operator opr);

void pushToStack(string name, DataType type);

void popFromStack(string name);

void convtStack(DataType in, DataType out);

void writeAssembly(const string &s);

void log(const string &s);

template<typename ... Args>
string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    auto buf = make_unique<char[]>( size );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

#endif