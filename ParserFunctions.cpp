
#include "ParserFunctions.hpp"
#include "symbol_table.hpp"
#include "hw3_output.hpp"

using namespace output;

SymbolTable symbol_table;

void CheckMainExists()
{
    if (symbol_table.DoesSymbolExists("main")){
        SymbolTableRecord main_record = symbol_table.GetSymbolRecordById("main");
        vector<pair<string,string>> main_record_args = main_record.GetFuncArgs();
        string ret = main_record.GetFuncReturnType();
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
        vector<pair<string,string>> args_types,
        string ret_type)
{
    if (symbol_table.DoesSymbolExists(symbol_name)){
        //error
    }
    else {
        symbol_table.InsertSymbol(symbol_name, type, args_types, ret_type,
                                   nullptr);
    }
}

void OpenNewScope()
{
    symbol_table.OpenScope();
}

void CloseCurrentScope()
{
    symbol_table.CloseCurrentScope();
}

void AddFuncArgsToSymbolTable(vector<pair<string,string>> args)
{
    int counter = -1;
    for (auto &arg : args) {
        if (symbol_table.DoesSymbolExists(arg.second))
        {
            //error
        }
        else {
            symbol_table.InsertFunctionArgSymbol(
                    arg.second,
                    arg.first,
                    counter);
        }
        counter--;
    }
}




