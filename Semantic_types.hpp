#ifndef HW3SOL_SEMANTIC_TYPES_HPP
#define HW3SOL_SEMANTIC_TYPES_HPP

#include <string>
#include <vector>
#include <utility>

using namespace std;

struct exp_t{
    string* type;
};

struct type_t{
    string* type;
};

struct enumType_t{
    vector<string>* values;
    string* typeName;
};

struct call_t{
    string* type;
};

struct expList_t{
    vector<string>* types;
};

struct dummy_t{
};

struct formals_t{
    vector<pair<string, string>>* args;
};

struct formalList_t{
    vector<pair<string, string>>* args;
};

struct formalDecl_t{
    string* type;
    string* argName;
};

struct retType_t{
    string* type;
};

#endif //HW3SOL_SEMANTIC_TYPES_HPP
