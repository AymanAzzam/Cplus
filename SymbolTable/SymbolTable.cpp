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
    scope.emplace_back();
}

bool SymbolTable::insertId(const string& name, int line, DataType type, bool init, bool isConst)
{
    vector<string> &currentScope = scope.back();
    for (const string &id : currentScope)
    {
        if (id == name)
            return false;
    }
    currentScope.push_back(name);
    idTable[name].push_back(Identifier(line, type, init, isConst));
    return true;
}

bool SymbolTable::modifyId(const string& name, bool init, bool use)
{
    if (idTable[name].empty())
        return false;
    Identifier &node = idTable[name].back();
    if (init)
        node.initialized = init;
    if (use)
        node.used = use;
}

bool SymbolTable::lookupId(const string& name, DataType &type, bool &isInitialized, bool &isConst)
{
    if (idTable[name].empty())
        return false;
    const Identifier &node = idTable[name].back();
    type = node.type;
    isInitialized = node.initialized;
    isConst = node.isConstant;
    return true;
}

vector<pair<string, int>> SymbolTable::finishScope()
{
    const vector<string> &currentScope = scope.back();
    vector<pair<string, int>> unusedId;
    try {
        for (const string &id : currentScope) {
            int line = removeId(id);
            if (line == -1)
                throw "Removing Undeclared Variable";
            else if (line > 0) {
                unusedId.emplace_back(id, line);
            }
        }
    } catch (const char* msg) {
        cerr << msg << endl;
    }

    scope.pop_back();
    scopeMask /= 10;
    return unusedId;
}

int SymbolTable::removeId(const string& name)
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

bool SymbolTable::insertFunc(const string& name, int line, DataType returnType, const vector<pair<string, DataType>>& parameterList)
{
    if (!isGlobal()) {
        printf("Error:%i: can't create function in local scope.\n", line);
        return false;
    }
    vector<string> &currentScope = scope.back();
    for (const string &id : currentScope)
    {
        if (id == name) {
            printf("Error:%i: identifier %s is already declared.\n", line, name.c_str());
            return false;
        }
    }
    currentScope.push_back(name);
    startScope(static_cast<ScopeType>(INT_FUNC + returnType));
    funcTable[name].push_back(returnType);
    bool ret = true;
    for (const pair<string, DataType>& p : parameterList)
    {
        if (!insertId(p.first, line, p.second, true)) {
            printf("Error:%i:  multiple parameters with the same name %s.\n", line, p.first.c_str());
            ret = false;
        }
        funcTable[name].push_back(p.second);
    }
    return ret;
}

bool SymbolTable::lookupFunc(const string& name, vector<DataType> &parameterList)
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
    if (t == _SWITCH)
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
    freopen("table.txt","w",stdout);
    
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

    fclose (stdout);
}

bool SymbolTable::canBreak() const
{
    int aux = scopeMask;
    while (aux)
    {
        if (aux % 10 == LOOP || aux % 10 == _SWITCH)
            return true;
        aux /= 10;
    }
    return false;
}

bool SymbolTable::canContinue() const
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

bool SymbolTable::isGlobal() const
{
    return scopeMask == GLOBAL;
}

bool SymbolTable::canReturn(DataType type) const
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
