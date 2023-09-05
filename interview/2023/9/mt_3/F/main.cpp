#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
    for (int q{}; std::cin >> q;) {
        for (int L = 0; L < q; ++L) {
            int n{}, m{};
            std::cin >> n >> m;
            std::vector<int> a(n), b(n);
            for (int i = 0; i < n; ++i) {
                std::cin >> a[i];
            }
            for (int i = 0; i < n; ++i) {
                std::cin >> b[i];
            }
            std::sort(a.begin(), a.end(), std::less<>{});
            std::sort(b.begin(), b.end(), std::greater<>{});
            bool f = true;
            for (int i = 0; i < n; ++i) {
                if (auto sum = a[i] + b[i];
                    sum != std::clamp(a[i] + b[i], 1, m)) {
                    f = false;
                    break;
                }
            }
            std::cout << (f ? "Yes" : "No") << std::endl;
        }
    }
    return 0;
}
