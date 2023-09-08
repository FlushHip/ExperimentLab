#include <iostream>
#include <numeric>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        auto sum = std::accumulate(a.begin(), a.end(), 0LL), ans = sum;
        for (int i = 1; i < n; ++i) {
            ans = std::max(ans, sum - a[i] - a[i - 1] + a[i] * a[i - 1]);
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
