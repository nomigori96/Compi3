#include "symbol_table.hpp"

symbolTableRecord::symbolTableRecord(const symbolTableRecord &to_copy){
    name = to_copy.name;
    offset = to_copy.offset;
    type = to_copy.type;
    func_arguments_types = to_copy.func_arguments_types;
    func_ret_value_type = to_copy.func_ret_value_type;
    enum_values = to_copy.enum_values;
}


void SymbolTable::insert_symbol(string symbol_name, string type,
                   vector<string> func_argument_types,
                   string func_return_value_type,
                   vector<string> enum_values){
    symbol_table->top().push_back(symbolTableRecord(symbol_name, offsets_stack->top(), type, func_argument_types, func_return_value_type, enum_values));
    int previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
}

void SymbolTable::open_scope(){
    vector<symbolTableRecord> new_scope;
    symbol_table->push(new_scope);
}

void SymbolTable::close_current_scope(){
    symbol_table->pop();
}

symbolTableRecord SymbolTable::get_symbol_record_by_id(string id){
    if (symbol_table->empty()){
        return nullptr;
    }
    vector<symbolTableRecord> scope;
    scope = symbol_table->top();
    for(vector <symbolTableRecord> :: iterator it = scope.begin(); it != scope.end(); ++it){
        if ((*it).get_name() == id){
            return *it;
        }
    }
    symbol_table->pop();
    symbolTableRecord result = get_symbol_record_by_id(id);
    symbol_table->push(scope);
    return result;
}

bool SymbolTable::does_symbol_exists(string id){
    if (symbol_table->empty()){
        return false;
    }
    vector<symbolTableRecord> scope;
    scope = symbol_table->top();
    for(vector <symbolTableRecord> :: iterator it = scope.begin(); it != scope.end(); ++it){
        if ((*it).get_name() == id){
            return true;
        }
    }
    symbol_table->pop();
    bool result = does_symbol_exists(id);
    symbol_table->push(scope);
    return result;
}

SymbolTable::SymbolTable(){
    symbol_table = new stack<vector<symbolTableRecord>>();
    offsets_stack = new stack<int>();
    offsets_stack->push(0);
    vector<string> print_argument_types;
    print_argument_types.push_back("string");
    symbolTableRecord print_record = symbolTableRecord("print", offsets_stack->top(), "function",
                                                       print_argument_types, "void", nullptr);
    int previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
    vector<string> printi_argument_types;
    printi_argument_types.push_back("int");
    symbolTableRecord printi_record = symbolTableRecord("printi", offsets_stack->top(), "function",
                                                        printi_argument_types, "void", nullptr);
    previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
    vector<symbolTableRecord> scope = vector<symbolTableRecord>();
    scope.push_back(print_record);
    scope.push_back(printi_record);
    symbol_table->push(scope);
}

SymbolTable::~SymbolTable(){
    delete symbol_table;
}

string SymbolTable::get_current_function_return_type(){
    vector<symbolTableRecord> current_scope;
    current_scope = symbol_table->top();
    symbol_table->pop();
    string return_type = (symbol_table->top()).back().get_func_ret_value_type();
    symbol_table->push(current_scope);
    return return_type;
}

