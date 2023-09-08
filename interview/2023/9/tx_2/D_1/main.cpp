#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    for (std::string str; std::cin >> str;) {
        auto sol = std::make_unique<Solution>();
        std::cout << sol->minOperations(str) << std::endl;
    }
    return 0;
}
