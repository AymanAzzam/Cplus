#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

enum DataType
{
    INTEGER,
    FLOAT,
    CHAR,
    BOOL,
    VOID
};

struct Identifier
{
    DataType type;
    bool initialized;
    bool used;
    int line;

    Identifier(int l, DataType t = INTEGER, bool init = false, bool use = false)
    {
        line = l;
        type = t;
        initialized = init;
        used = use;
    }
};

class SymbolTable
{
private:
    unordered_map<string, vector<Identifier>> idTable;
    unordered_map<string, vector<DataType>> funcTable;
    vector<vector<string>> scope;
    int removeId(string name); // -1: undeclared, 0: used, ow: line of declaration
    string enumToString(DataType t);

public:
    SymbolTable();
    void startScope();
    bool insertId(string name, int line, DataType type, bool init);
    bool modifyId(string name, bool init = false, bool use = false);
    int lookupId(string name, DataType &type); // -1: undeclared, 0: uninit, 1: init
    vector<pair<string, int>> finishScope();

    bool insertFunc(string name, int line, DataType returnType, vector<pair<string, DataType>> parameterList);
    bool lookupFunc(string name, vector<DataType> &parameterList); // 0: func return type, 1,2,..:paramerterList
    void print();
    ~SymbolTable();
};

#endif