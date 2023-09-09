#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
        }
        std::sort(a.begin(), a.end());
        auto end = std::unique(a.begin(), a.end());
        for (auto it = a.begin(); it != end; ++it) {
            std::cout << *it << std::endl;
        }
    }
    return 0;
}
