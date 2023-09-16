#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    std::vector<std::tuple<int, int, std::vector<int>>> vs{
        {2, 3, {1, 2, 3, 4, 5, 6}},
        {2, 3, {1, 2, 3, 4, 5, 6, 7, 8}},
    };
    for (auto&& [m, n, line] : vs) {
        auto sol = std::make_unique<Solution>();
        std::cout << sol->calculate(m, n, line) << std::endl;
    }
    return 0;
}
