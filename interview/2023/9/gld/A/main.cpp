#include <iostream>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<long long> s(n), t(n), a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> s[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> t[i];
        }
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        auto ans = 0LL;
        for (int i = 0; i < n;) {
            auto sum = 0LL;
            int j{};
            for (j = i + 1; j < n; ++j) {
                if (s[i] + t[i] > s[j]) {
                    sum += a[j];
                } else {
                    break;
                }
            }
            if (sum >= a[i]) {
                i = j;
            } else {
                ans += a[i];
                ++i;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
