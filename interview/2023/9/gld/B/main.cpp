#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        int target = a.back(), ans = 0, L = 0;
        for (int i = n - 1; i >= 0 && a[i] == target; --i) {
            ++L;
        }
        for (; L * 2 <= n; L *= 2) {
            if (!std::all_of(a.begin() + n - 2 * L, a.begin() + n - L,
                    [target](int val) { return target == val; })) {
                ++ans;
            }
        }
        if (n != L) {
            if (!std::all_of(a.begin(), a.begin() + n - L,
                    [target](int val) { return target == val; })) {
                ++ans;
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
