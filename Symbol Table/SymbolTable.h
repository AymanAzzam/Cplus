#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <unordered_map>
#include <string>
#include <vector>
#include "../constants.h"

using namespace std;

struct Identifier
{
    DataType type;
    bool initialized;
    bool used;
    bool isConstant;
    int line;

    Identifier(int l, DataType t = _TYPE_INT, bool init = false, bool isConst = false, bool use = false)
    {
        line = l;
        type = t;
        initialized = init;
        used = use;
        isConstant = isConst;
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
    int removeId(const string& name); // -1: undeclared, 0: used, ow: line of declaration
    static string dataTypeEnumToString(DataType t);
    static string scopeTypeEnumToString(ScopeType t);
    int scopeMask;

public:
    SymbolTable(SymbolTable &other) = delete;
    void operator=(const SymbolTable &) = delete;
    static SymbolTable *GetInstance();

    /**
     * @brief Start a new scope on an openning curly brace or a function definition.
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
     * @param isConst bool: either constant or not.
     * @return true upon successful insertion (not seen yet).
     * @return false upon failed insertion (seen before).
     */
    bool insertId(const string& name, int line, DataType type, bool init = false, bool isConst = false);

    /**
     * @brief Modify status of identifier upon initialization (LHS) or usage (RHS)
     * 
     * @param name string: name of identifier.
     * @param init bool: true in case of LHS.
     * @param use bool: true in case of RHS.
     * @return true upon sucessful modification (identifier seen before).
     * @return false upon failed modification (identifier not seen before).
     */
    bool modifyId(const string& name, bool init = false, bool use = false);

    /**
     * @brief Lookup for some identifier
     * 
     * @param name string: name of identifier
     * @param type Enum DataType: dummy parameter to return actual dataType of identifier.
     * @param isInitialized bool: dummy parameter to return if identifier is initialized.
     * @param isConst bool: dummy parameter to return if identifier is constant.
     * @return true upon sucessful lookup (identifier seen before).
     * @return false upon failed lookup (identifier not seen before).
     */
    bool lookupId(const string& name, DataType &type, bool &isInitialized, bool &isConst);

    /**
     * @brief Finish a scope on closing a curly brace
     * 
     * @return vector<pair<string, int>> Vector of not used identifiers.
     */
    vector<pair<string, int>> finishScope();

    /**
     * @brief Insert a new function upon declaration.
     * 
     * @param name string: name of the function
     * @param line int: line number of function
     * @param returnType Enum DataType: return type of function
     * @param parameterList vector<pair<string, DataType>>: first: identifier name, second: data type of identifier
     * @return true upon sucessful insertion (not seen before && global scope).
     * @return false upon failed insertion.
     */
    bool insertFunc(const string& name, int line, DataType returnType, const vector<pair<string, DataType>>& parameterList);

    /**
     * @brief Lookup for a function if appeared before and return its related info.
     * 
     * @param name string: name of function.
     * @param parameterList vector<DataType>: dummy parameter holds return type of function in index 0 then parameters type
     * @return true true upon sucessful lookup (function seen before).
     * @return false false upon failed lookup (function not seen before).
     */
    bool lookupFunc(const string& name, vector<DataType> &parameterList); // 0: func return type, 1,2,..:paramerterList

    /**
     * @brief Prints SymbolTable (Name, Type, Scope, Used)
     * 
     */
    void print();

    /**
     * @brief Whether a break can be performed in this scope or not (loops, switch).
     * 
     * @return true breakable
     * @return false not breakable
     */
    bool canBreak() const;

    /**
     * @brief Whether a continue can be performed in this scope or not (loops).
     * 
     * @return true continuable
     * @return false not coninuable
     */
    bool canContinue() const;

    /**
     * @brief Whether it is a global scope or not.
     * 
     * @return true in case of global scope.
     * @return false any nested scope.
     */
    bool isGlobal() const;

    /**
     * @brief Whether a return statement can be performed in this scope (inside a function of same return type).
     * 
     * @param type Enum DataType: type of return we want to do.
     * @return true returnable
     * @return false non returnable
     */
    bool canReturn(DataType type) const;

    ~SymbolTable();
};

#endif