#include "symbol_table.hpp"

bool EnumSymbolTableRecord::DoesValueExists(const string& value){
    for (auto &enum_value : enum_values){
        if (enum_value == value){
            return true;
        }
    }
    return false;
}

void SymbolTable::InsertSymbol(
        const string& symbol_name,
        const string& type,
        bool is_enum_type)
{
    symbol_table->top().push_back(
            SymbolTableRecord(
                symbol_name,
                offsets_stack->top(),
                type,
                is_enum_type));
    int previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
}

void SymbolTable::InsertFunction(
        const string& symbol_name,
        const vector<tuple<string,string, bool>>& func_arguments,
        const string& func_return_value_type)
{
    symbol_table->top().push_back(
            FunctionSymbolTableRecord(
                    symbol_name,
                    offsets_stack->top(),
                    func_arguments,
                    func_return_value_type));
    int previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
}

void SymbolTable::InsertEnum(
        const string& symbol_name,
        const vector<string>& enum_values)
{
    symbol_table->top().push_back(
            EnumSymbolTableRecord(
                    symbol_name,
                    offsets_stack->top(),
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

SymbolTableRecord* SymbolTable::GetSymbolRecordById(const string& id)
{
    if (symbol_table->empty()){
        return nullptr;
    }
    vector<SymbolTableRecord> scope;
    scope = symbol_table->top();
    for (auto &symbol : scope) {
        if (symbol.GetName() == id){
            return new SymbolTableRecord(symbol);
        }
    }
    symbol_table->pop();
    SymbolTableRecord* result = GetSymbolRecordById(id);
    symbol_table->push(scope);
    return result;
}

bool SymbolTable::DoesSymbolExists(const string& id)
{
    if (symbol_table->empty()){
        return false;
    }
    vector<SymbolTableRecord> scope;
    scope = symbol_table->top();
    for (auto &symbol : scope) {
        if (symbol.GetName() == id ||
                (symbol.GetType() == "enum" &&
                        dynamic_cast<EnumSymbolTableRecord>(symbol).DoesValueExists(id) )){
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
    vector<tuple<string,string, bool>> print_arguments;
    print_arguments.push_back(tuple<string, string, bool>("string", "", false));
    SymbolTableRecord print_record = FunctionSymbolTableRecord("print",
                                                               offsets_stack->top(),
                                                               print_arguments,
                                                               "void");
    int previous_offset = offsets_stack->top();
    offsets_stack->pop();
    offsets_stack->push(previous_offset + 1);
    vector<tuple<string,string, bool>> printi_arguments;
    printi_arguments.push_back(tuple<string, string, bool>("int", "", false));
    SymbolTableRecord printi_record = FunctionSymbolTableRecord("printi",
                                                                offsets_stack->top(),
                                                                printi_arguments,
                                                                "void");
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
    string return_type = (dynamic_cast<FunctionSymbolTableRecord>(
            (symbol_table->top()).back()))
            .GetFuncReturnType();
    symbol_table->push(current_scope);
    return return_type;
}

void SymbolTable::InsertFunctionArgSymbol(
        const string& symbol_name,
        const string& type,
        int offset,
        bool is_enum_type)
{
    symbol_table->top().push_back(SymbolTableRecord(
            symbol_name,
            offset,
            type,
            is_enum_type));
}

string SymbolTable::FindEnumTypeByGivenValue(const string& value){
    if (symbol_table->empty()){
        return nullptr;
    }
    vector<SymbolTableRecord> scope;
    scope = symbol_table->top();
    for (auto &symbol : scope) {
        if (symbol.GetType() == "enum"){
            vector<string> enumValues = dynamic_cast<EnumSymbolTableRecord>(symbol).GetEnumValues();
            for (auto &enumVal : enumValues){
                if (enumVal == value){
                    return symbol.GetName();
                }
            }
        }
    }
    symbol_table->pop();
    string result = FindEnumTypeByGivenValue(value);
    symbol_table->push(scope);
    return result;
}

