#include "test.h"
#include <iostream>

std::vector<std::pair<void (*)(), std::string>> &tests() {
    static std::vector<std::pair<void (*)(), std::string>> _tests;
    return _tests;
}

std::vector<std::string> &names() {
    static std::vector<std::string> _names;
    return _names;
}

int main() {
    std::cout << "Total: " << tests().size() << " tests" << std::endl;
    const std::string sep = "----------";
    for (auto &testpair: tests()) {
        std::cout << "Running test: " << testpair.second << std::endl;
        std::cout << sep << std::endl;
        testpair.first();
        std::cout << sep << std::endl;
    }
    return 0;
}