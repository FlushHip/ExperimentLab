#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    std::vector<std::tuple<std::string, std::string>> vs{
        {"ABC", "A"},
        {"AABC", "AC"},
        {"AABC", "ACD"},
    };
    for (auto&& [a, b] : vs) {
        auto sol = std::make_unique<Solution>();
        std::cout << sol->subsequence(a, b) << std::endl;
    }
    return 0;
}
