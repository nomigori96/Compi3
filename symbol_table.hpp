#ifndef HW3_SYMBOL_TABLE_HPP
#define HW3_SYMBOL_TABLE_HPP


#include <stack>
#include <vector>
#include <string>

using namespace std;

class symbolTableRecord {
private:
    string name;
    int offset;
    string type;
    vector<string> func_arguments_types;
    string func_ret_value_type;
    vector<string> enum_values;
public:
    symbolTableRecord(string name_p, int offset_p, string type_p,
                      vector<string> func_arguments_types_p,
                      string func_ret_value_type_p,
                      vector<string> enum_values_p): name(name_p),
                                                     offset(offset_p),
                                                     type(type_p),
                                                     func_arguments_types(func_arguments_types_p),
                                                     func_ret_value_type(func_ret_value_type_p),
                                                     enum_values(enum_values_p){}
    ~symbolTableRecord(){};
    symbolTableRecord(const symbolTableRecord &to_copy);
    string get_name() {return name;}
    string get_type(){return type;}
    int get_offset(){return offset;}
    vector<string> get_func_arguments_types() {return func_arguments_types;}
    string get_func_ret_value_type() {return func_ret_value_type;}
    vector<string> get_enum_values() {return enum_values;}

};

class SymbolTable{
private:
    stack<vector<symbolTableRecord>>* symbol_table;
    stack<int>* offsets_stack;

public:
    void insert_symbol(string symbol_name, string type,
                       vector<string> func_argument_types,
                       string func_return_value_type,
                        vector<string> enum_values);
    void open_scope();
    void close_current_scope();
    string get_current_function_return_type();
    symbolTableRecord get_symbol_record_by_id(string id);
    bool does_symbol_exists(string id);
    SymbolTable();
    ~SymbolTable();
};

#endif //HW3_SYMBOL_TABLE_HPP
