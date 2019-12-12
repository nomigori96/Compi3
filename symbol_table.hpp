#ifndef HW3_SYMBOL_TABLE_HPP
#define HW3_SYMBOL_TABLE_HPP


#include <stack>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

class SymbolTableRecord {
protected:
    string name;
    int offset;
    string type;
    bool is_enum_type;

public:
    SymbolTableRecord(
            const string& name_p,
            int offset_p,
            const string& type_p,
            bool is_enum_type_p) : name(name_p),
                                    offset(offset_p),
                                    type(type_p),
                                    is_enum_type(is_enum_type_p){}
    virtual ~SymbolTableRecord() = default;
    SymbolTableRecord(const SymbolTableRecord &to_copy) = default;
    virtual SymbolTableRecord& operator=(const SymbolTableRecord &to_copy) = default;
    string GetName() const {return name;}
    string GetType() const {return type;}
    int GetOffset() const {return offset;}
    int IsEnumType() const {return is_enum_type;}
};


class FunctionSymbolTableRecord : public SymbolTableRecord {
private:
    vector<tuple<string, string, bool>> func_arguments;
    string func_ret_type;

public:
    FunctionSymbolTableRecord(
            const string& name_p,
            int offset_p,
            const vector<tuple<string,string, bool>>& func_arguments_p,
            const string& func_ret_value_type_p) : SymbolTableRecord(name_p,
                                                                     offset_p, "function", false),                                                          func_arguments(func_arguments_p),
                                                   func_ret_type(func_ret_value_type_p){}
    ~FunctionSymbolTableRecord() = default;
    FunctionSymbolTableRecord(const SymbolTableRecord &to_copy) = default;
    FunctionSymbolTableRecord& operator=(const SymbolTableRecord &to_copy) = default;
    vector<tuple<string,string, bool>> GetFuncArgs() const {return func_arguments;}
    string GetFuncReturnType() const {return func_ret_type;}

};

class EnumSymbolTableRecord : public SymbolTableRecord {
private:
    vector<string> enum_values;

public:
    EnumSymbolTableRecord(
            const string& name_p,
            int offset_p,
            const vector<string>& enum_values_p) : SymbolTableRecord(name_p,
                                                                     offset_p, "enum", false),
                                                   enum_values(enum_values_p){}
    ~EnumSymbolTableRecord() = default;
    EnumSymbolTableRecord(const SymbolTableRecord &to_copy) = default;
    EnumSymbolTableRecord& operator=(const SymbolTableRecord &to_copy) = default;
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
            bool is_enum_type);
    void InsertFunction(
            const string& symbol_name,
            const vector<tuple<string,string, bool>>& func_arguments,
            const string& func_return_value_type);
    void InsertEnum(
            const string& symbol_name,
            const vector<string>& enum_values);
    void InsertFunctionArgSymbol(
            const string& symbol_name,
            const string& type,
            int offset,
            bool is_enum_type);
    void OpenScope();
    void CloseCurrentScope();
    string GetCurrFunctionReturnType();
    SymbolTableRecord GetSymbolRecordById(const string& id);
    bool DoesSymbolExists(const string& id);
    SymbolTable();
    ~SymbolTable();
};

#endif //HW3_SYMBOL_TABLE_HPP
