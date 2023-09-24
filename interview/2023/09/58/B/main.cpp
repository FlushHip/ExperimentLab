#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    std::vector<std::tuple<std::vector<int>, int>> vs{
        {{4, 6, 1, 2}, 2},
        {{1, 1, 1, 1}, 0},
    };
    for (auto&& [line, k] : vs) {
        auto sol = std::make_unique<Solution>();
        std::cout << sol->maximumScore(line, k) << std::endl;
    }
    return 0;
}
