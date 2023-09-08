#include <iostream>
#include <memory>

#include "class.hpp"

int main() {
    for (int n{}, x{}; std::cin >> n >> x;) {
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        auto sol = std::make_unique<Solution>();
        std::cout << sol->getSubarrayNum(a, x) << std::endl;
    }
    return 0;
}
