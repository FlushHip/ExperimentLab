#include <cmath>
#include <iostream>
#include <vector>

int main() {
    for (int T{}; std::cin >> T;) {
        for (int n{}, x{}; T--;) {
            std::cin >> n >> x;
            std::vector<int> a(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> a[i];
            }
            int ans = 0, cnt_top = std::ceil((0.0 + n) / 2);
            for (int L = 0; L < (1 << n); ++L) {
                int sum = 0, cnt = 0;
                for (int i = 0; i < n; ++i) {
                    if (L & (1 << i)) {
                        sum += a[i];
                        ++cnt;
                    }
                }
                ans += cnt == cnt_top && sum >= x;
            }
            std::cout << ans << std::endl;
        }
    }
    return 0;
}
