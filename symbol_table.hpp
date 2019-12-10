#ifndef HW3_SYMBOL_TABLE_HPP
#define HW3_SYMBOL_TABLE_HPP


#include <stack>
#include <vector>
#include <string>

using namespace std;

//TODO add interface (class that symbol table inherits) to solve the fact there are irrelevant fields in the record

class SymbolTableRecord {
private:
    string name;
    int offset;
    string type;
    vector<pair<string, string>> func_arguments;
    string func_ret_type;
    vector<string> enum_values;

public:
    SymbolTableRecord(
            const string& name_p,
            int offset_p,
            const string& type_p,
            const vector<pair<string,string>>& func_arguments_p,
            const string& func_ret_value_type_p,
            const vector<string>& enum_values_p) : name(name_p),
                                            offset(offset_p),
                                            type(type_p),
                                            func_arguments(func_arguments_p),
                                            func_ret_type(func_ret_value_type_p),
                                            enum_values(enum_values_p){}
    ~SymbolTableRecord() = default;
    SymbolTableRecord(const SymbolTableRecord &to_copy) = default;
    SymbolTableRecord& operator=(const SymbolTableRecord &to_copy) = default;
    string GetName() const {return name;}
    string GetType() const {return type;}
    int GetOffset() const {return offset;}
    vector<pair<string,string>> GetFuncArgs() const {return func_arguments;}
    string GetFuncReturnType() const {return func_ret_type;}
    vector<string> GetEnumValues() const {return enum_values;}

};

class SymbolTable{
private:
    stack<vector<SymbolTableRecord>>* symbol_table;
    stack<int>* offsets_stack;

public:
    void InsertSymbol(
            const string& symbol_name,
            const string& type,
            const vector<pair<string,string>>& func_arguments,
            const string& func_return_value_type,
            const vector<string>& enum_values);
    void InsertFunctionArgSymbol(
            const string& symbol_name,
            const string& type,
            int offset);
    void OpenScope();
    void CloseCurrentScope();
    string GetCurrFunctionReturnType();
    SymbolTableRecord GetSymbolRecordById(const string& id);
    bool DoesSymbolExists(const string& id);
    SymbolTable();
    ~SymbolTable();
};

#endif //HW3_SYMBOL_TABLE_HPP
