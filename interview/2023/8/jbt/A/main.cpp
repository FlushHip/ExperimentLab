#include <algorithm>
#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        struct context {
            char c;
            std::array<int, 26> lp;
        };
        std::unordered_map<char, std::array<int, 26>> ump;
        for (int L = 0; L < n; ++L) {
            std::string line;
            std::cin >> line;
            for (int i = 0; i < static_cast<int>(line.size()); ++i) {
                ++ump[line[i]][i];
            }
        }
        dbg(ump);
        std::vector<context> arrs;
        for (auto&& [c, arr] : ump) {
            arrs.emplace_back(context{c, arr});
        }
        std::sort(arrs.begin(), arrs.end(), [](auto&& lhs, auto&& rhs) {
            for (int i = 0; i < 26; ++i) {
                if (lhs.lp[i] == rhs.lp[i]) {
                    continue;
                }
                return lhs.lp[i] > rhs.lp[i];
            }
            return lhs.c < rhs.c;
        });
        for (auto&& [c, _] : arrs) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    return 0;
}
