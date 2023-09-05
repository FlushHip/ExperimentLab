#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        std::sort(a.begin(), a.end());
        auto fn = [](auto begin, auto end, long long target) {
            auto down = 0LL, up = 0LL;
            for (auto it = begin; it != end; ++it) {
                if (*it < target) {
                    down += target - *it;
                } else {
                    up += *it - target;
                }
            }
            return std::max(down, up);
        };
        auto sum = std::accumulate(a.begin(), a.end(), 0LL);
        long long base = sum / n, last_offset = sum % n;
        if (last_offset == 0) {
            std::cout << fn(a.begin(), a.end(), base) << std::endl;
        } else {
            std::cout << std::min(std::min(fn(std::next(a.begin()), a.end(),
                                               (sum - a.front()) / (n - 1)),
                                      fn(std::next(a.begin()), a.end(),
                                          (sum - a.front()) / (n - 1) + 1)),
                             std::min(fn(a.begin(), std::prev(a.end()),
                                          (sum - a.back()) / (n - 1)),
                                 fn(a.begin(), std::prev(a.end()),
                                     (sum - a.back()) / (n - 1) + 1)))
                      << std::endl;
        }
    }
    return 0;
}
