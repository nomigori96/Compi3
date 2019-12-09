//
// Created by owner on 09/12/2019.
//
#include "ParserFunctions.hpp"

void ProgramEnumFuncs()
{
    if (symbol_table.does_symbol_exists("main")){
        symbolTableRecord main_record = symbol_table.get_symbol_record_by_id("main");
        vector<string> main_record_args = main_record.get_func_arguments_types();
        string ret = main_record.get_func_ret_value_type();
        if (!(main_record_args.empty() && ret == "void")){
            errorMainMissing();
        }
    }
    else {
        errorMainMissing();
    }
}


void AddFunctionSymbolIfNotExists(
        string symbol_name,
        string type,
        vector<string> args_types,
        string ret_type)
{
    if (symbol_table.does_symbol_exists(symbol_name)){
        //error
    }
    else {
        symbol_table.insert_symbol(symbol_name, type, args_types, ret_type,
                                   nullptr);
    }
}

void OpenNewScope()
{
    symbol_table.open_scope();
}

void CloseCurrentScope()
{
    symbol_table.close_current_scope();
}

void AddFuncArgsToSymbolTable(vector<pair<string,string>> args)
{
    int counter = -1;
    for (auto it = args.begin(); it != args.end(); ++it){
        if (symbol_table.does_symbol_exists((*it).second))
        {
            //error
        }
        else {
            symbol_table.insert_function_arg_symbol(
                    (*it).second,
                    (*it).first,
                    counter);
        }
    }
}




