//
// Created by owner on 09/12/2019.
//

#ifndef HW3_PARSERFUNCTIONS_HPP
#define HW3_PARSERFUNCTIONS_HPP

#include "symbol_table.hpp"
#include "hw3_output.hpp"

using namespace output;
using namespace std;

SymbolTable symbol_table;

void program_enum_funcs();
void AddFunctionSymbolIfNotExists(
        string symbol_name,
        string type,
        vector<string> args_types,
        string ret_type);
void OpenNewScope();
void CloseCurrentScope();
void AddFuncArgsToSymbolTable(vector<pair<string,string>> args);

#endif //HW3_PARSERFUNCTIONS_HPP
