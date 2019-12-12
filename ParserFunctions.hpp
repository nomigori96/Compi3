
#ifndef HW3_PARSERFUNCTIONS_HPP
#define HW3_PARSERFUNCTIONS_HPP

#include <string>
#include <vector>

using namespace std;

void CheckMainExists();
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

#endif //HW3_PARSERFUNCTIONS_HPP
