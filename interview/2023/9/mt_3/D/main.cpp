#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    constexpr long long mod = 1e9 + 7;
    for (int n{}, k{}; std::cin >> n >> k;) {
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        std::sort(a.begin(), a.end(), std::greater<>{});
        if (n == 1) {
            std::cout << a[0] << std::endl;
            continue;
        }
        int top = std::min(n - 1, k);
        for (int i = 0; i < top; ++i) {
            a[i + 1] = (a[i + 1] * a[i]) % mod;
            a[i] = 1;
        }
        std::cout << std::accumulate(a.begin(), a.end(), 0LL,
                         [mod](auto init, auto val) {
                             return (init + val) % mod;
                         })
                  << std::endl;
    }
    return 0;
}
