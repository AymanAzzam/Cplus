#include "utilities.h"
#include <memory>
#include <stdexcept>
#include <iostream>

string oprToString(Operator opr) {
    string out;

    switch (opr)
    {
        // arithmetic operators
        case _REM:
            out = "%";
            break;
        case _MUL:
            out = "*";
            break;
        case _DIV:
            out = "/";
            break;
        case _SUB:
            out = "-";
            break;
        case _ADD:
            out = "+";
            break;
        case _INC_OPR:
            out = "++";
            break;
        case _DEC_OPR:
            out = "--";
            break;

        // assignment operators
        case _MOD_EQ:
            out = "%=";
            break;
        case _MULT_EQ:
            out = "%=";
            break;
        case _DIV_EQ:
            out = "/=";
            break;
        case _MINUS_EQ:
            out = "-=";
            break;
        case _PLUS_EQ:
            out = "+=";
            break;
        case _EQ:
            out = "=";
            break;

        // comparison operators
        case _LTE:
            out = "<=";
            break;
        case _GTE:
            out = ">=";
            break;
        case _LT:
            out = "<";
            break;
        case _GT:
            out = ">";
            break;
        case _NOT_EQ:
            out = "!=";
            break;
        case _IS_EQ:
            out = "==";
            break;
        
        // bitwise operators
        case _SHL:
            out = "<<";
            break;
        case _SHR:
            out = ">>";
            break;
        case _BIT_XOR:
            out = "^";
            break;
        case _BIT_OR:
            out = "|";
            break;
        case _BIT_AND:
            out = "&";
            break;
        case _BIT_NOT:
            out = "~";
            break;
        
        // logical operators
        case _LOGICAL_AND:
            out = "&&";
            break;
        case _LOGICAL_OR:
            out = "||";
            break;
        case _LOGICAL_NOT:
            out = "!";
            break;
    }

    return out;
};

string typeToString(DataType type) {
    string out;

    switch (type)
    {
        case _TYPE_CHAR:
            out = "char";
            break;
        case _TYPE_FLOAT:
            out = "float";
            break;
        case _TYPE_INT:
            out = "int";
            break;
        case _TYPE_BOOL:
            out = "bool";
            break;
        case _TYPE_VOID:
            out = "void";
            break;
    }

    return out;
};


bool isLogicalOpr(Operator opr){
    switch (opr)
    {
        case _LOGICAL_OR:
            return true;
        case _LOGICAL_AND:
            return true;
        case _LOGICAL_NOT:
            return true;
    }

    return false;
}

DataType typeConversion(DataType left, DataType right, Operator opr) {
    DataType out = left;
    string left_s, right_s;

    left_s = typeToString(left);
    right_s = typeToString(right);

    if(isLogicalOpr(opr))
    {
        if(left != _TYPE_BOOL)
            printf("\n\nWarning: Type mismatch, converting %s to bool", \
                left_s.c_str());
        
        if(right != _TYPE_BOOL)
            printf("\n\nWarning: Type mismatch, converting %s to bool", \
                right_s.c_str());
                
        return _TYPE_BOOL;
    }

    if(right == _TYPE_FLOAT || \
      (right == _TYPE_INT && (left == _TYPE_CHAR || left == _TYPE_BOOL)) || \
        (right == _TYPE_CHAR && left == _TYPE_BOOL))
            out = right;

    if(out == right && right != left)
        printf("\n\nWarning: Type mismatch, converting %s to %s", \
                left_s.c_str(), right_s.c_str());

    if(out == left && right != left)
        printf("\n\nWarning: Type mismatch, converting %s to %s", \
                right_s.c_str(), left_s.c_str());

    return out;
};

void pushToStack(string name, DataType type) {
    string t = typeToString(type);

    printf("\tPUSH\t%s\t%s\n", t.c_str(), name.c_str());
}


void popFromStack(string name) {
    printf("\tPOP\t%s\n", name.c_str());
}


void convtStack(DataType in, DataType out) {
    string s_in = typeToString(in);
    string s_out = typeToString(out);

    printf("\tCONVT\t%s\t%s", s_in.c_str(), s_out.c_str());
}

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

void log(const string& s) {
    cout << s << endl;
}

void writeAssembly(const string& s) {
    cout << s << endl;
}