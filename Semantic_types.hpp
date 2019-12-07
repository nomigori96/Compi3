#ifndef HW3SOL_SEMANTIC_TYPES_HPP
#define HW3SOL_SEMANTIC_TYPES_HPP

#include <string>
#include <vector>

using namespace std;

struct exp_t{
    string type;
};

struct type_t{
    string type;
};

struct enumType_t{
    vector<string> values;
};

struct call_t{
    string type;
};

struct expList_t{
    vector<string> types;
};

struct dummy_t{
};

#endif //HW3SOL_SEMANTIC_TYPES_HPP
