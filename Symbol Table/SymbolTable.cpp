#include "SymbolTable.h"
#include <iostream>
#include <iomanip>

using namespace std;

SymbolTable *SymbolTable::symbolTable = nullptr;

SymbolTable::SymbolTable()
{
    scopeMask = 0;
    startScope(GLOBAL);
}

SymbolTable *SymbolTable::GetInstance()
{
    if (symbolTable == nullptr)
    {
        symbolTable = new SymbolTable();
    }
    return symbolTable;
}

void SymbolTable::startScope(ScopeType val)
{
    scopeMask = scopeMask * 10 + val;
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
    Identifier &node = idTable[name].back();
    if (init)
        node.initialized = init;
    if (use)
        node.used = use;
}

int SymbolTable::lookupId(string name, DataType &type)
{
    if (idTable[name].empty())
        return -1;
    const Identifier &node = idTable[name].back();
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
        else if (line > 0)
        {
            unusedId.push_back({id, line});
        }
    }
    scope.pop_back();
    scopeMask /= 10;
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
    const Identifier &node = idTable[name].back();
    int line = (!node.used) * node.line;
    return line;
}

bool SymbolTable::insertFunc(string name, int line, DataType returnType, vector<pair<string, DataType>> parameterList)
{
    if (scopeMask != GLOBAL)
        return false;
    vector<string> &currentScope = scope.back();
    for (const string &id : currentScope)
    {
        if (id == name)
            return false;
    }
    currentScope.push_back(name);
    startScope(static_cast<ScopeType>(INT_FUNC + returnType));
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

string SymbolTable::dataTypeEnumToString(DataType t)
{
    if (t == _TYPE_INT)
        return "int";
    if (t == _TYPE_FLOAT)
        return "float";
    if (t == _TYPE_CHAR)
        return "char";
    if (t == _TYPE_BOOL)
        return "bool";
    return "void";
}

string SymbolTable::scopeTypeEnumToString(ScopeType t)
{
    if (t == GLOBAL)
        return "GLOBAL";
    if (t == BLOCK)
        return "BLOCK";
    if (t == LOOP)
        return "LOOP";
    if (t == SWITCH)
        return "SWITCH";
    if (t == INT_FUNC)
        return "INT_FUNC";
    if (t == FLOAT_FUNC)
        return "FLOAT_FUNC";
    if (t == CHAR_FUNC)
        return "CHAR_FUNC";
    if (t == BOOL_FUNC)
        return "BOOL_FUNC";
    return "VOID_FUNC";
}

void SymbolTable::print()
{
    cout << "--------------------------------------------------------------" << endl;
    cout << "|          |  Name          |  Type |    Scope       | Used  |" << endl;
    cout << "--------------------------------------------------------------" << endl;
    unordered_map<string, int> idx;
    string scopeString = to_string(scopeMask);
    for (int i = 0; i < scope.size(); i++)
    {
        for (int j = 0; j < scope[i].size(); j++)
        {
            const string &name = scope[i][j];
            const string &scopeType = to_string(i) + " - " + scopeTypeEnumToString(static_cast<ScopeType>(scopeString[i] - '0'));
            string identifier, dataType, used = "-";
            if (i == 0 && funcTable.count(name))
            {
                identifier = "Function";
                dataType = dataTypeEnumToString(funcTable[name][0]);
            }
            else
            {
                int idIdx = idx[name]++;
                identifier = "Variable";
                dataType = dataTypeEnumToString(idTable[name][idIdx].type);
                used = idTable[name][idIdx].used ? "True" : "False";
            }
            cout << "| " << left << setw(9) << identifier;
            cout << "| " << left << setw(15) << name;
            cout << "| " << left << setw(6) << dataType;
            cout << "| " << left << setw(15) << scopeType;
            cout << "| " << left << setw(6) << used << "|\n";
        }
    }
    cout << "--------------------------------------------------------------" << endl;
}

bool SymbolTable::canBreak()
{
    int aux = scopeMask;
    while (aux)
    {
        if (aux % 10 == LOOP || aux % 10 == SWITCH)
            return true;
        aux /= 10;
    }
    return false;
}

bool SymbolTable::canContinue()
{
    int aux = scopeMask;
    while (aux)
    {
        if (aux % 10 == LOOP)
            return true;
        aux /= 10;
    }
    return false;
}

bool SymbolTable::isGlobal()
{
    return scopeMask == GLOBAL;
}

bool SymbolTable::canReturn(DataType type)
{
    int aux = scopeMask;
    while (aux)
    {
        if (aux % 10 >= INT_FUNC)
            return ((aux % 10) - INT_FUNC) == type;
        aux /= 10;
    }
    return false;
}
