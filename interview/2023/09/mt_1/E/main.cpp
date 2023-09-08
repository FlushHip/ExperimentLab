#include <iostream>

int main() {
    for (int n{}; std::cin >> n;) {
        int rhs = n, lhs = 1;
        for (; lhs <= n / 2; --rhs, ++lhs) {
            std::cout << (rhs == n ? "" : " ") << rhs << " " << lhs;
        }
        if (n % 2) {
            std::cout << " " << rhs << std::endl;
        } else {
            std::cout << std::endl;
        }
    }
    return 0;
}
