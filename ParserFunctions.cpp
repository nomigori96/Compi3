
#include "ParserFunctions.hpp"
#include "symbol_table.hpp"
#include "hw3_output.hpp"

using namespace output;

SymbolTable symbol_table;
extern int yylineno;

void CheckMainExists()
{
    if (symbol_table.DoesSymbolExists("main") == SYMBOL){
        FunctionSymbolTableRecord* main_record =
                dynamic_cast<FunctionSymbolTableRecord*>(symbol_table.GetSymbolRecordById("main"));
        vector<tuple<string,string, bool>> main_record_args = main_record->GetFuncArgs();
        string ret = main_record->GetFuncReturnType();
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
    if (symbol_table.DoesSymbolExists(symbol_name) != DOESNT_EXIST){
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
    if (symbol_table.DoesSymbolExists(symbol_name) != DOESNT_EXIST){
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
        if (symbol_table.DoesSymbolExists(get<1>(arg)) != DOESNT_EXIST)
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

string GetExpressionTypeById(string& id){
    if (symbol_table.DoesSymbolExists(id) == SYMBOL){
        SymbolTableRecord* wantedRecord = symbol_table.GetSymbolRecordById(id);
        return wantedRecord->GetType();
    }
    if (symbol_table.DoesSymbolExists(id) == ENUM_VALUE){
        return symbol_table.FindEnumTypeByGivenValue(id);
    }
    //error
    exit(0);
}


bool AreArgsEqual(vector<string> expListTypes, vector<tuple<string, string, bool>> fromRecord){
    if (expListTypes.size() != fromRecord.size()){
        return false;
    }
    vector<string>::iterator expListTypeIterator = expListTypes.begin();
    vector<tuple<string, string, bool>>::iterator fromRecordIterator = fromRecord.begin();
    while (expListTypeIterator != expListTypes.end()){
        if(*expListTypeIterator != get<0>(*fromRecordIterator)){
            return false;
        }
    }
    return true;
}

vector<string> MapArgsToTypes(vector<tuple<string, string, bool>> fromRecord){
    vector<string> onlyTypes;
    for(auto &currArg : fromRecord){
        string argType;
        tie(argType, ignore, ignore) = currArg;
        onlyTypes.push_back(argType);
    }
    return onlyTypes;
}

string CheckFunction(string& id, vector<string> expListTypes){
    if (symbol_table.DoesSymbolExists(id) == SYMBOL){
       SymbolTableRecord* wantedRecord = symbol_table.GetSymbolRecordById(id);
        if (wantedRecord->GetType() != "function"){
            errorUndefFunc(yylineno, id);
            exit(0);
        }
        vector<tuple<string, string, bool>> fromRecord = dynamic_cast<FunctionSymbolTableRecord*>(wantedRecord)->GetFuncArgs();
        if (!AreArgsEqual(expListTypes, fromRecord)){
            vector<string> expectedTypes = MapArgsToTypes(fromRecord);
            errorPrototypeMismatch(yylineno, id, expectedTypes);
            exit(0);
        }
        return dynamic_cast<FunctionSymbolTableRecord*>(wantedRecord)->GetFuncReturnType();
    }
    errorUndefFunc(yylineno, id);
    exit(0);
}




