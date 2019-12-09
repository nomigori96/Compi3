#include "symbol_table.hpp"

SymbolTableRecord::SymbolTableRecord(const SymbolTableRecord &to_copy)
{
    name = to_copy.name;
    offset = to_copy.offset;
    type = to_copy.type;
    func_arguments = to_copy.func_arguments;
    func_ret_type = to_copy.func_ret_type;
    enum_values = to_copy.enum_values;
}


void SymbolTable::InsertSymbol(
        string symbol_name,
        string type,
        vector<pair<string,string>> func_arguments,
        string func_return_value_type,
        vector<string> enum_values)
{
    symbol_table->top().push_back(SymbolTableRecord(
            symbol_name,
            offsets_stack->top(),
            type,
            func_arguments,
            func_return_value_type,
            enum_values));
    int previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
}

void SymbolTable::OpenScope()
{
    vector<SymbolTableRecord> new_scope;
    symbol_table->push(new_scope);
}

void SymbolTable::CloseCurrentScope()
{
    symbol_table->pop();
}

SymbolTableRecord SymbolTable::GetSymbolRecordById(string id)
{
    if (symbol_table->empty()){
        return nullptr;
    }
    vector<SymbolTableRecord> scope;
    scope = symbol_table->top();
    for (auto &symbol : scope) {
        if (symbol.GetName() == id){
            return symbol;
        }
    }
    symbol_table->pop();
    SymbolTableRecord result = GetSymbolRecordById(id);
    symbol_table->push(scope);
    return result;
}

bool SymbolTable::DoesSymbolExists(string id)
{
    if (symbol_table->empty()){
        return false;
    }
    vector<SymbolTableRecord> scope;
    scope = symbol_table->top();
    for (auto &symbol : scope) {
        if (symbol.GetName() == id){
            return true;
        }
    }
    symbol_table->pop();
    bool result = DoesSymbolExists(id);
    symbol_table->push(scope);
    return result;
}

SymbolTable::SymbolTable()
{
    symbol_table = new stack<vector<SymbolTableRecord>>();
    offsets_stack = new stack<int>();
    offsets_stack->push(0);
    vector<pair<string,string>> print_argument_types;
    print_argument_types.push_back(pair<string, string>("string", ""));
    SymbolTableRecord print_record = SymbolTableRecord("print", offsets_stack->top(), "function",
                                                       print_argument_types, "void", nullptr);
    int previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
    vector<pair<string,string>> printi_argument_types;
    printi_argument_types.push_back(pair<string, string>("int", ""));
    SymbolTableRecord printi_record = SymbolTableRecord("printi", offsets_stack->top(), "function",
                                                        printi_argument_types, "void", nullptr);
    previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
    vector<SymbolTableRecord> scope = vector<SymbolTableRecord>();
    scope.push_back(print_record);
    scope.push_back(printi_record);
    symbol_table->push(scope);
}

SymbolTable::~SymbolTable()
{
    delete symbol_table;
}

string SymbolTable::GetCurrFunctionReturnType()
{
    vector<SymbolTableRecord> current_scope;
    current_scope = symbol_table->top();
    symbol_table->pop();
    string return_type = (symbol_table->top()).back().GetFuncReturnType();
    symbol_table->push(current_scope);
    return return_type;
}

void SymbolTable::InsertFunctionArgSymbol(
        string symbol_name,
        string type,
        int offset)
{
    symbol_table->top().push_back(SymbolTableRecord(
            symbol_name,
            offset,
            type,
            nullptr,
            nullptr,
            nullptr));
}

