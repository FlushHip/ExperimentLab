#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    for (int n{}, m{}, x{}; std::cin >> n >> m >> x;) {
        auto sol = std::make_unique<Solution>();
        std::cout << sol->numsOfGoodMatrix(n, m, x) << std::endl;
    }
    return 0;
}
