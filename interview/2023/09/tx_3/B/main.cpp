#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <vector>

#include <dbg.h>

int main() {
    for (int t{}; std::cin >> t;) {
        while (t--) {
            int n{};
            std::cin >> n;
            std::vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> a[i];
            }
            std::vector<int> b(n - 1);
            for (int i = 0; i < n - 1; ++i) {
                std::cin >> b[i];
                --b[i];
            }
            std::vector<std::pair<int, int>> prs;
            for (int i = 0; i < n; ++i) {
                prs.emplace_back(a[i], i);
            }
            std::sort(prs.begin(), prs.end());
            std::unordered_map<int, int> ump;
            for (int i = 0; i < n; ++i) {
                ump[prs[i].second] = i;
            }
            int lhs = n / 2, rhs = lhs;
            if (n % 2 == 0) {
                --lhs;
            }
            std::vector<int> ans;
            std::vector<bool> visit(n, false);
            int res = n;
            for (int i = 0; i < n - 1; ++i) {
                dbg(b[i], prs, visit, lhs, rhs);
                ans.emplace_back(prs[lhs].first + prs[rhs].first);
                auto idx = ump[b[i]];
                if (idx >= rhs) {
                    if (res % 2 == 0) {
                        for (--rhs; lhs <= rhs && visit[rhs]; --rhs) {
                        }
                    } else {
                        for (--lhs; lhs >= 0 && visit[lhs]; --lhs) {
                        }
                    }
                } else {
                    if (res % 2 == 0) {
                        for (++lhs; lhs <= rhs && visit[lhs]; ++lhs) {
                        }
                    } else {
                        for (++rhs; rhs < n && visit[rhs]; ++rhs) {
                        }
                    }
                }
                visit[idx] = true;
                --res;
            }
            ans.emplace_back(prs[lhs].first * 2);
            for (int i = 0; i < n; ++i) {
                std::cout << (0.0 + ans[i]) / 2 << " \n"[i + 1 == n];
            }
        }
    }
    return 0;
}
