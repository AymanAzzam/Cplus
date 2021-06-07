#include "SymbolTable.h"
#include <iostream>
using namespace std;
SymbolTable::SymbolTable()
{
    startScope();
}

void SymbolTable::startScope()
{
    scope.push_back(vector<string>{});
}

bool SymbolTable::insertId(string name, int line, DataType type, bool init)
{
    vector<string> &currentScope = scope.back();
    for (const string &id : currentScope)
    {
        if (id == name)
            return false;
    }
    currentScope.push_back(name);
    idTable[name].push_back(Identifier(line, type, init));
    return true;
}

bool SymbolTable::modifyId(string name, bool init, bool use)
{
    if (idTable[name].empty())
        return false;
    Identifier & node = idTable[name].back();
    if (init)
        node.initialized = init;
    if (use)
        node.used = use;
}

int SymbolTable::lookupId(string name, DataType &type)
{
    if (idTable[name].empty())
        return -1;
    const Identifier & node = idTable[name].back();
    type = node.type;
    return node.initialized;
}

vector<pair<string, int>> SymbolTable::finishScope()
{
    const vector<string> &currentScope = scope.back();
    vector<pair<string, int>> unusedId;
    for (const string &id : currentScope)
    {
        int line = removeId(id);
        if (line == -1)
            throw "Removing Undeclared Variable";
        else if (line == 0)
        {
            unusedId.push_back({id, line});
        }
    }
    scope.pop_back();
    return unusedId;
}

int SymbolTable::removeId(string name)
{
    if (idTable[name].empty())
    {
        if (!funcTable.count(name))
            return -1;
        return -2;
    }
    const Identifier & node = idTable[name].back();
    int line = (node.used) * node.line;
    return line;
}

bool SymbolTable::insertFunc(string name, int line, DataType returnType, vector<pair<string, DataType>> parameterList)
{
    if (scope.size() > 1)
        return false;
    vector<string> &currentScope = scope.back();
    for (const string &id : currentScope)
    {
        if (id == name)
            return false;
    }
    currentScope.push_back(name);
    startScope();
    funcTable[name].push_back(returnType);
    for (pair<string, DataType> p : parameterList)
    {
        insertId(p.first, line, p.second, true);
        funcTable[name].push_back(p.second);
    }
    return true;
}

bool SymbolTable::lookupFunc(string name, vector<DataType> &parameterList)
{
    if (!funcTable.count(name))
        return false;
    parameterList = funcTable[name];
    return true;
}

SymbolTable::~SymbolTable()
{
     finishScope();
}

string SymbolTable::enumToString(DataType t) {
    if (t == INTEGER)
        return "int";
    if (t == FLOAT)
        return "float";
    if (t == CHAR)
        return "char";
    if (t == BOOL)
        return "bool";
    return "void";
}

void SymbolTable::print() {
    cout << "Symbol Table: " << endl;
    unordered_map<string, int> idx;
    for (int i = 0; i < scope.size(); i++) {
        for (int j = 0; j < scope[i].size(); j++) {
            for (int k = 0; k < i; k++) cout << '\t';
            if (i == 0 && funcTable.count(scope[i][j])) {
                DataType type = funcTable[scope[i][j]][0];
                cout << "Function: " + scope[i][j] << ", return type: " << enumToString(type) << "\n";
            } else {
                int id_idx = idx[scope[i][j]]++;
                cout << "Variable: " << scope[i][j] << ", Type: " << enumToString(idTable[scope[i][j]][id_idx].type) << "\n";
            }
        }
    }
}
