#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

enum DataType
{
    _TYPE_INT,
    _TYPE_FLOAT,
    _TYPE_CHAR,
    _TYPE_BOOL,
    _TYPE_VOID
};

enum ScopeType
{
    GLOBAL = 1,
    BLOCK,
    LOOP,
    SWITCH,
    INT_FUNC,
    FLOAT_FUNC,
    CHAR_FUNC,
    BOOL_FUNC,
    VOID_FUNC
};
struct Identifier
{
    DataType type;
    bool initialized;
    bool used;
    int line;

    Identifier(int l, DataType t = _TYPE_INT, bool init = false, bool use = false)
    {
        line = l;
        type = t;
        initialized = init;
        used = use;
    }
};

/**
 * @brief Singleton Class for all symbol table opearations.
 * 
 */
class SymbolTable
{
private:
    SymbolTable();
    static SymbolTable *symbolTable;

    unordered_map<string, vector<Identifier>> idTable;
    unordered_map<string, vector<DataType>> funcTable;
    vector<vector<string>> scope;
    int removeId(string name); // -1: undeclared, 0: used, ow: line of declaration
    string dataTypeEnumToString(DataType t);
    string scopeTypeEnumToString(ScopeType t);
    int scopeMask;

public:
    SymbolTable(SymbolTable &other) = delete;
    void operator=(const SymbolTable &) = delete;
    static SymbolTable *GetInstance();

    /**
     * @brief Start a new scope {}
     * 
     * @param type Enum ScopeType: [GLOBAL, BLOCK, SWITCH, LOOP, INT_FUNC, ..etc]
     */
    void startScope(ScopeType type);

    /**
     * @brief Insert a new identifier upon initialization or declaration.
     * 
     * @param name string: name of identifier. 
     * @param line int: line number
     * @param type Enum DataType: [_TYPE_INT, _TYPE_FLOAT, ..]
     * @param init bool: either initialized or not.
     * @return true upon successful insertion (not seen yet).
     * @return false upon failed insertion (seen before).
     */
    bool insertId(string name, int line, DataType type, bool init);

    /**
     * @brief Modify status of identifier upon initialization (LHS) or usage (RHS)
     * 
     * @param name string: name of identifier.
     * @param init bool: true in case of LHS.
     * @param use bool: true in case of RHS.
     * @return true upon sucessful modification (identifier seen before).
     * @return false upon failed modification (identifier not seen before).
     */
    bool modifyId(string name, bool init = false, bool use = false);

    /**
     * @brief Look up for some identifier
     * 
     * @param name string: name of identifier
     * @param type Enum DataType: dummy parameter to return actual dataType of identifier.
     * @return int -1: undeclared, 0: uninitialized, 1: initialized
     */
    int lookupId(string name, DataType &type);

    /**
     * @brief Finish a scope on closing a curly brace
     * 
     * @return vector<pair<string, int>> Vector of not used identifiers.
     */
    vector<pair<string, int>> finishScope();

    bool insertFunc(string name, int line, DataType returnType, vector<pair<string, DataType>> parameterList);
    bool lookupFunc(string name, vector<DataType> &parameterList); // 0: func return type, 1,2,..:paramerterList
    void print();

    bool canBreak();
    bool canContinue();
    bool isGlobal();
    bool canReturn(DataType type);
    ~SymbolTable();
};

#endif