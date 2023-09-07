#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        int target = a.back(), ans = 0, L = 1;
        for (int i = n - 2; L < n && i >= 0;) {
            if (a[i] == target) {
                ++L;
                --i;
            } else {
                ++ans;
                i -= L;
                L *= 2;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
