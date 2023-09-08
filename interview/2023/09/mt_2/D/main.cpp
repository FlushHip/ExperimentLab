#include <iostream>

int main() {
    for (int q{}; std::cin >> q;) {
        for (int i = 0; i < q; ++i) {
            int m{}, x{};
            std::cin >> m >> x;
            std::cout << 1 + (x - 1) % m << std::endl;
        }
    }
    return 0;
}
