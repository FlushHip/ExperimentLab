#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        std::sort(a.begin(), a.end());
        int rhs = n - 1, lhs = 0;
        long long ans = 0, x = 0;
        for (; lhs <= rhs;) {
            ans += a[rhs] - x;
            x = a[lhs];
            ++lhs;
            --rhs;
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
