
#ifndef HW3_PARSERFUNCTIONS_HPP
#define HW3_PARSERFUNCTIONS_HPP

#include <string>
#include <vector>

using namespace std;

void CheckMainExists();
void AddFunctionSymbolIfNotExists(
        string symbol_name,
        string type,
        vector<string> args_types,
        string ret_type);
void OpenNewScope();
void CloseCurrentScope();
void AddFuncArgsToSymbolTable(vector<pair<string,string>> args);

#endif //HW3_PARSERFUNCTIONS_HPP
