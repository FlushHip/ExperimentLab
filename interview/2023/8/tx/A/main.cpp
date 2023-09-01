#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

int main() {
    std::vector<std::string> strs{
        "ycyzyz",
        "ahkaakkkbb",
    };
    struct context {
        char c = 0;
        int cnt = 0;
    };
    for (const auto& str : strs) {
        std::unordered_map<char, int> mp;
        for (char c : str) {
            ++mp[c];
        }
        std::vector<context> ctxs;
        for (auto&& [c, cnt] : mp) {
            ctxs.emplace_back(context{c, cnt});
        }
        std::sort(ctxs.begin(), ctxs.end(),
            [](const auto& lhs, const auto& rhs) { return lhs.cnt < rhs.cnt; });
        int n = static_cast<int>(ctxs.size());
        if (n % 2) {
            std::cout << ctxs[n / 2].cnt << std::endl;
        } else {
            std::cout << (0.0 + ctxs[n / 2].cnt + ctxs[n / 2 - 1].cnt) / 2
                      << std::endl;
        }
    }
    return 0;
}
