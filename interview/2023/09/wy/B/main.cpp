#include <array>
#include <iostream>
#include <unordered_map>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        struct hash {
            std::size_t operator()(const std::array<int, 26>& arr) const {
                constexpr long long mod = 1e9 + 7;
                long long base = 10, m = 1;
                std::size_t result = 0;
                for (int i = 0; i < 26; ++i) {
                    result = (result + m * (arr[i] - 1) % mod) % mod;
                    m = (m * base) % mod;
                }
                return result;
            }
        };
        std::unordered_map<std::array<int, 26>, long long, hash> ump;
        for (int i = 0; i < n; ++i) {
            std::string str;
            std::cin >> str;
            std::array<int, 26> arr{0};
            for (char c : str) {
                ++arr[c - 'a'];
            }
            dbg(arr);
            ++ump[arr];
        }
        long long result = 0;
        for (auto&& [_, cnt] : ump) {
            result += cnt * (cnt - 1) / 2;
        }
        std::cout << result << std::endl;
    }
    return 0;
}
