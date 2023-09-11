#include <iostream>

int main() {
    for (int n{}; std::cin >> n && n != 0;) {
        int ans = 0;
        if (n == 1) {
            std::cout << "0" << std::endl;
            continue;
        }
        for (; n > 2;) {
            ans += n / 3;
            n = n % 3 + n / 3;
        }
        if (n == 2) {
            ++ans;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
