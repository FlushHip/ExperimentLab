#include <iostream>

int main() {
    for (long long x{}, y{}, z{}; std::cin >> x >> y >> z;) {
        auto ans = z / (3 * x + y) * 3;
        auto res = z % (3 * x + y);
        if (res) {
            ++ans;
            if (res > x + y) {
                res -= x + y;
                ++ans;
                if (res > x) {
                    ++ans;
                }
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
