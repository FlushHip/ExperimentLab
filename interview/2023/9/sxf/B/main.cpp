#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    for (int T{}; std::cin >> T;) {
        while (T--) {
            int n{};
            std::cin >> n;
            std::vector<int> lines(n + 1);
            std::unordered_map<int, int> ump;
            for (int i = 1; i <= n; ++i) {
                int h{};
                std::cin >> lines[i] >> h;
                ump[h] = i;
            }
            std::vector<int> ans(n);
            for (int idx = ump[0], i = 0; idx != 0 && i < n; ++i) {
                ans[i] = lines[idx];
                if (!ump.count(idx)) {
                    break;
                }
                idx = ump[idx];
            }
            for (auto it = ans.begin(); it != ans.end(); ++it) {
                std::cout << *it << " \n"[std::next(it) == ans.end()];
            }
        }
    }
    return 0;
}
