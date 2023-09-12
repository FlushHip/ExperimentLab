#include <iostream>

int main() {
    for (int n{}; std::cin >> n;) {
        int idx = 1;
        for (int x{}, i = 0; i < n; ++i) {
            std::cin >> x;
            if (x == idx) {
                ++idx;
            }
        }
        if (idx == 1) {
            std::cout << -1 << std::endl;
        } else {
            std::cout << n - idx + 1 << std::endl;
        }
    }
    return 0;
}
