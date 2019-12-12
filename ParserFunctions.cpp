
#include "ParserFunctions.hpp"
#include "symbol_table.hpp"
#include "hw3_output.hpp"

using namespace output;

SymbolTable symbol_table;
extern int yylineno;

void CheckMainExists()
{
    if (symbol_table.DoesSymbolExists("main")){
        FunctionSymbolTableRecord main_record =
                dynamic_cast<FunctionSymbolTableRecord>(symbol_table.GetSymbolRecordById("main"));
        vector<tuple<string,string, bool>> main_record_args = main_record.GetFuncArgs();
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
        const string& symbol_name,
        const vector<tuple<string,string,bool>>& args,
        const string& ret_type)
{
    if (symbol_table.DoesSymbolExists(symbol_name)){
        //error
    }
    else {
        symbol_table.InsertFunction(symbol_name, args, ret_type);
    }
}

void AddEnumSymbolIfNotExists(
        const string& symbol_name,
        const vector<string>& enum_values)
{
    if (symbol_table.DoesSymbolExists(symbol_name)){
        //error
    }
    else {
        symbol_table.InsertEnum(symbol_name, enum_values);
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

void AddFuncArgsToSymbolTable(vector<tuple<string,string,bool>>& args)
{
    int counter = -1;
    for (auto &arg : args) {
        if (symbol_table.DoesSymbolExists(get<1>(arg)))
        {
            //error
        }
        else {
            symbol_table.InsertFunctionArgSymbol(
                    get<1>(arg),
                    get<0>(arg),
                    counter,
                    get<2>(arg));
        }
        counter--;
    }
}

void CheckTypesMatch(vector<string>& expected, string& given){
    for (string &expected_option : expected){
        if (given == expected_option){
            return;
        }
    }
    errorMismatch(yylineno);
    exit(0);
}

string DetermineBinopReturnType(string& first, string& second){
    if(first == "byte" && second == "byte"){
        return "byte";
    }
    return "int";
}
/*
string GetSymbolTypeIfExists(string& symbolName){
    if (symbol_table.DoesSymbolExists(symbolName)){
        SymbolTableRecord wantedRecord = symbol_table.GetSymbolRecordById(symbolName);
        return wantedRecord.GetType();
    }
    return nullptr;
}*/

string GetExpressionTypeById(string& id){
    if (symbol_table.DoesSymbolExists(id)){
        SymbolTableRecord wantedRecord = symbol_table.GetSymbolRecordById(id);
        if (wantedRecord){

        }
        return wantedRecord.GetType();
    }
    return nullptr;
}




