#include <iostream>
#include <numeric>
#include <unordered_map>

int main() {
    for (int n{}, m{}; std::cin >> n >> m;) {
        std::string line;
        std::cin >> line;
        std::unordered_map<char, long long> ump;
        long long w = 0;
        for (auto it = line.begin(); std::next(it) != line.end(); ++it) {
            if (*it != '?') {
                ++ump[*it];
            } else {
                ++w;
            }
        }
        auto sum = std::accumulate(ump.begin(), ump.end(), 0LL,
            [](long long init, const auto& pr) { return init + pr.second; });
        auto fn = [&](char last) {
            auto it = ump.find(last);
            if (it == ump.end()) {
                return m == 1 ? 0 : sum + w;
            }
            return m == 1 ? 0 : sum - it->second + w;
        };
        long long ans = 0;
        if (line.back() != '?') {
            ans = fn(line.back());
        } else {
            for (char c = 'a'; c <= m - 1 + 'a'; ++c) {
                ans = std::max(ans, fn(c));
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
