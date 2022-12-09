#pragma once

#include <vector>
#include <string>
#include "ThirdParty/hedley.h"

std::vector<std::pair<void (*)(), std::string>> &tests();

#define ADD_TEST(name, test_body)                                            \
    void HEDLEY_CONCAT(_test, __LINE__)()                              \
    {                                                                  \
        test_body                                                      \
    }                                                                  \
    static int HEDLEY_CONCAT(_init, __LINE__) = []() {                 \
        tests().emplace_back(HEDLEY_CONCAT(_test, __LINE__), HEDLEY_STRINGIFY(name)); \
        return 0;                                                      \
    }();
