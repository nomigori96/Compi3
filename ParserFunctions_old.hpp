
#ifndef HW3_PARSERFUNCTIONS_HPP
#define HW3_PARSERFUNCTIONS_HPP

#include <string>
#include <vector>

using namespace std;

void CheckMainExists();
void AddVariableSymbolIfNotExists(
        string& symbol_name,
        string& type,
        bool is_enum_type);
void AddFunctionSymbolIfNotExists(
        string& symbol_name,
        vector<tuple<string,string,bool>>& args,
        string& ret_type);
void AddEnumSymbolIfNotExists(
        const string& symbol_name,
        const vector<string>& enum_values);
void OpenNewScope();
void CloseCurrentScope();
void AddFuncArgsToSymbolTable(vector<pair<string,string>>& args);
void CheckTypesMatch(string& expected, string& given);
string DetermineBinopReturnType(string& first, string& second);
string CheckFunction(string& id, vector<string> expListTypes);
void HandleAssignment(string& lType, string& expType, string& id);
void HandleAssignmentForExistingVar(string& id, string& expType);
void FlipLoopStatus();
void CheckIfBreakInLoop();
void CheckIfContinueInLoop();
void UpdateCurrFunctionRetType(string& retType);
void CheckReturnValid(string& givenType);
void IsExplicitCastAllowed(string& castToType, string& castFromType);
void CheckNumValidity(int byteNum);
vector<string> MapArgsToTypes(vector<tuple<string, string, bool>> fromRecord);

#endif //HW3_PARSERFUNCTIONS_HPP
