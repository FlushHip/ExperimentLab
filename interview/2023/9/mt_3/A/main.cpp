#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

int main() {
    for (long long n{}, k{}; std::cin >> n >> k;) {
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            a[i] -= k;
        }
        if (std::all_of(a.begin(), a.end(), [](auto val) { return val < 0; }) ||
            std::all_of(a.begin(), a.end(), [](auto val) { return val > 0; })) {
            std::cout << -1 << std::endl;
            continue;
        }
        std::unordered_map<long long, int> ump;
        ump.emplace(0LL, -1);
        long long sum = 0LL;
        int ans = -1;
        for (int i = 0; i < n; ++i) {
            sum += a[i];
            if (auto it = ump.find(sum); it != ump.end()) {
                ans = std::max(ans, i - it->second);
            } else {
                ump.emplace(sum, i);
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
