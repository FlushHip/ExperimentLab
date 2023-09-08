#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    std::vector<std::tuple<std::vector<int>, std::vector<int>>> v{
        {
            {1, 1, 2},
            {1, 2, 1},
        },
    };
    for (auto&& [pre, in] : v) {
        auto sol = std::make_unique<Solution>();
        dbg(sol->getBinaryTrees(pre, in));
    }
    return 0;
}
