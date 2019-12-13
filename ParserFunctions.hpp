//
// Created by owner on 13/12/2019.
//

#ifndef HW3_PARSERFUNCTIONNEW_HPP
#define HW3_PARSERFUNCTIONNEW_HPP
//
// Created by owner on 13/12/2019.
//


#include <algorithm>
#include "symbol_table.hpp"
#include "hw3_output.hpp"



void CheckMainExists();

void CloseCurrentScope();

vector<string> MapArgsToTypes(vector<tuple<string, string, bool>> fromRecord);


void AddFunctionSymbolIfNotExists(
        const string& symbol_name,
        const string& ret_type);

void UpdateCurrFunctionRetType(string& retType);

void AddFuncArgsToSymbolTable(vector<tuple<string,string,bool>>& args);

void UpdateFunctionSymbolArgs(vector<tuple<string,string,bool>>& args, string func_id);

void CheckIfIdIsShadowing(string& id);

void CheckIfEnumTypeIsDefined(string& enumTypeName, string& id);

void AddEnumSymbolIfNotExists(
        const string& symbol_name);

void UpdateEnumSymbolValues(vector<string>& values, string enum_id);

void CheckNoDuplicatesEnumList(vector<string>& enumValues, string& newValue);

void CheckNoDuplicatesFormalList(vector<tuple<string, string, bool>>& args, string& newArgId);

void AddVariableSymbolIfNotExists(string& symbol_name,
                                  string& type,
                                  bool is_enum_type);

void CheckIfAssignmentAllowed(string& lType, string& expType);

void CheckIfAssignmentAllowedEnum(string& enumType, string& expEnumType, string& varId);

string GetExpressionTypeById(string& id);

void HandleAssignmentForExistingVar(string& id, string& expType);

void CheckReturnValid(string& givenType);

void CheckTypesMatch(vector<string>& expected, string& given);

void FlipLoopStatus();

void CheckIfBreakInLoop();

void CheckIfContinueInLoop();


bool AreArgsEqual(vector<string> expListTypes, vector<tuple<string, string, bool>> fromRecord);

string CheckFunction(string& id, vector<string> expListTypes);

void CheckNumValidity(int byteNum);

string DetermineBinopReturnType(string& first, string& second);

void isExplicitCastAllowed(string& castToType, string& castFromType);



#endif //HW3_PARSERFUNCTIONNEW_HPP
