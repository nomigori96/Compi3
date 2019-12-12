
#include "ParserFunctions.hpp"
#include "symbol_table.hpp"
#include "hw3_output.hpp"

using namespace output;

SymbolTable symbol_table;
bool is_in_loop = false;
string curr_function_return_type = "";

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
            exit(0);
        }
    }
    else {
        errorMainMissing();
        exit(0);
    }
}


void AddFunctionSymbolIfNotExists(
        const string& symbol_name,
        const vector<tuple<string,string,bool>>& args,
        const string& ret_type)
{
    if (symbol_table.DoesSymbolExists(symbol_name) != DOESNT_EXIST){
        errorDef(yylineno, symbol_name);
        exit(0);
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
        errorDef(yylineno, symbol_name);
        exit(0);
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
    endScope();
    vector<SymbolTableRecord*> currentScope = symbol_table.GetCurrentScope();
    for (auto &symbol : currentScope){
        if (symbol->IsEnumType()){
            string enum_str("enum ");
            printID(symbol->GetName(), symbol->GetOffset(), enum_str + symbol->GetType());
        } else if (symbol->GetType() == "function"){
            string retType = dynamic_cast<FunctionSymbolTableRecord*>(symbol)->GetFuncReturnType();
            vector<string> argTypes = MapArgsToTypes(dynamic_cast<FunctionSymbolTableRecord*>(symbol)->GetFuncArgs());
            string type = makeFunctionType(retType, argTypes);
            printID(symbol->GetName(), 0, type);
        }
        else {
            printID(symbol->GetName(), symbol->GetOffset(), symbol->GetType());
        }
    }
    symbol_table.CloseCurrentScope();
}

void AddFuncArgsToSymbolTable(vector<tuple<string,string,bool>>& args)
{
    int counter = -1;
    for (auto &arg : args) {
        if (symbol_table.DoesSymbolExists(get<1>(arg)) != DOESNT_EXIST)
        {
            errorDef(yylineno, get<1>(arg));
            exit(0);
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
        string recordType = wantedRecord->GetType();
        if (recordType == "function" || recordType == "enum"){
            errorUndef(yylineno, id);
            exit(0);
        }
        return recordType;
    }
    if (symbol_table.DoesSymbolExists(id) == ENUM_VALUE){
        return symbol_table.FindEnumTypeByGivenValue(id);
    }

    errorUndef(yylineno, id);
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

bool IsVarTypeValid(string& type){
    if(type == "byte" || type == "int" || type == "bool"){
        return true;
    }
    return symbol_table.DoesSymbolExists(type) == SYMBOL &&
            symbol_table.GetSymbolRecordById(type)->GetType() == "enum";
}

void AddVariableSymbolIfNotExists(string& symbol_name,
                                  string& type,
                                  bool is_enum_type){
    if (symbol_table.DoesSymbolExists(symbol_name) != DOESNT_EXIST){
        errorDef(yylineno, symbol_name);
        exit(0);
    }
    if (IsVarTypeValid(type)){
        symbol_table.InsertSymbol(symbol_name, type, is_enum_type);
    }
    else {
        errorUndefEnum(yylineno, symbol_name);
        exit(0);
    }
}

bool IsImplicitCastAllowed(string& lType, string& expType){
    return lType == "int" && expType == "byte";
}

void HandleAssignment(string& lType, string& expType, string& id){
    if (lType != expType && !IsImplicitCastAllowed(lType, expType)){
        errorMismatch(yylineno);
        exit(0);
    }
    AddVariableSymbolIfNotExists(id, lType, false);
}

void HandleAssignmentForExistingVar(string& id, string& expType){
    if (symbol_table.DoesSymbolExists(id) != SYMBOL){
        errorUndef(yylineno, id);
        exit(0);
    }
    string wanted_type = symbol_table.GetSymbolRecordById(id)->GetType();
    if (wanted_type != expType && !IsImplicitCastAllowed(wanted_type, expType)){
        if(wanted_type == "byte" || wanted_type == "int" || wanted_type == "bool" ||
                symbol_table.GetSymbolRecordById(id)->IsEnumType()){
            errorMismatch(yylineno);
        }
        else {
            errorUndef(yylineno, id);
        }
        exit(0);
    }
}

void FlipLoopStatus(){
    is_in_loop = !is_in_loop;
}

void CheckIfBreakInLoop(){
    if (!is_in_loop){
        errorUnexpectedBreak(yylineno);
        exit(0);
    }
}

void CheckIfContinueInLoop(){
    if (!is_in_loop){
        errorUnexpectedContinue(yylineno);
        exit(0);
    }
}

void UpdateCurrFunctionRetType(string& retType){
    curr_function_return_type = retType;
}

void CheckReturnValid(string& givenType){
    if (curr_function_return_type != givenType && !IsImplicitCastAllowed(curr_function_return_type, givenType)){
        errorMismatch(yylineno);
        exit(0);
    }
}

void ExplicitCast(string& castToType, string& castFromType){
    if (!(castToType == "int" && castFromType == "enum")){
        errorMismatch(yylineno);
        exit(0);
    }
}

void CheckNumValidity(int byteNum){
    if (byteNum > 255){
        errorByteTooLarge(yylineno, to_string(byteNum));
        exit(0);
    }
}





