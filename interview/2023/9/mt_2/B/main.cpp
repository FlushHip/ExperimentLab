#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        std::sort(a.begin(), a.end());
        auto sum = std::accumulate(a.begin(), a.end(), 0LL);
        long long base = sum / n, last_offset = sum % n;
        std::vector<int> b(n, base);
        b.back() += last_offset;
        dbg(a, b);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] < b[i]) {
                ans += b[i] - a[i];
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
