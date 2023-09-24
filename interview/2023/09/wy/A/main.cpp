#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#include <dbg.h>

int main() {
    for (int T{}; std::cin >> T;) {
        while (T--) {
            int n{};
            std::cin >> n;
            std::vector<int> a_0, a_1;
            for (int i = 0; i < n; ++i) {
                int a{};
                std::cin >> a;
                if (i % 2) {
                    a_1.emplace_back(a);
                } else {
                    a_0.emplace_back(a);
                }
            }
            if (n % 2) {
                std::cout << "YES" << std::endl;
                continue;
            }
            std::sort(a_0.begin(), a_0.end());
            std::sort(a_1.begin(), a_1.end());
            dbg(a_0, a_1);
            int m = static_cast<int>(a_1.size()), sum = 0;
            a_0.emplace_back(std::numeric_limits<int>::max());
            for (int i = 0; i < m; ++i) {
                if (a_0[i] <= a_1[i] && a_1[i] <= a_0[i + 1]) {
                    ++sum;
                }
            }
            std::cout << (sum == m ? "YES" : "NO") << std::endl;
        }
    }
    return 0;
}
