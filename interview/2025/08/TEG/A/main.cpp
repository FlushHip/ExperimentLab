#include <iostream>
#include <vector>

// #include <dbg.h>

int main() {
    int T{};
    std::cin >> T;
    while (T--) {
        int k{}, n{}, m{};
        std::cin >> k;
        std::cin >> n;
        std::vector<int> vec(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> vec[i];
        }
        std::cin >> m;
        std::sort(vec.begin(), vec.end());
        int sum = 0;
        for (int i = 0; i < n && vec[i] < m; ++i) {
            if (vec[i] > k && vec[i] < m) {
                ++sum;
            }
        }
        int ans = m - k - sum + 1;
        std::cout << ans << "\n";
    }
    return 0;
}
