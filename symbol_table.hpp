#ifndef HW3_SYMBOL_TABLE_HPP
#define HW3_SYMBOL_TABLE_HPP


#include <stack>
#include <vector>
#include <string>

using namespace std;

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
            string name_p,
            int offset_p,
            string type_p,
            vector<pair<string,string>> func_arguments_p,
            string func_ret_value_type_p,
            vector<string> enum_values_p) : name(name_p),
                                            offset(offset_p),
                                            type(type_p),
                                            func_arguments(func_arguments_p),
                                            func_ret_type(func_ret_value_type_p),
                                            enum_values(enum_values_p){}
    ~SymbolTableRecord(){};
    SymbolTableRecord(const SymbolTableRecord &to_copy);
    string GetName() {return name;}
    string GetType(){return type;}
    int GetOffset(){return offset;}
    vector<pair<string,string>> GetFuncArgs() {return func_arguments;}
    string GetFuncReturnType() {return func_ret_type;}
    vector<string> GetEnumValues() {return enum_values;}

};

class SymbolTable{
private:
    stack<vector<SymbolTableRecord>>* symbol_table;
    stack<int>* offsets_stack;

public:
    void InsertSymbol(
            string symbol_name,
            string type,
            vector<pair<string,string>> func_arguments,
            string func_return_value_type,
            vector<string> enum_values);
    void InsertFunctionArgSymbol(
            string symbol_name,
            string type,
            int offset);
    void OpenScope();
    void CloseCurrentScope();
    string GetCurrFunctionReturnType();
    SymbolTableRecord GetSymbolRecordById(string id);
    bool DoesSymbolExists(string id);
    SymbolTable();
    ~SymbolTable();
};

#endif //HW3_SYMBOL_TABLE_HPP
