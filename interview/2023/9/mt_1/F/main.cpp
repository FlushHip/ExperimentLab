#include <iostream>
#include <numeric>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<int> interval(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> interval[i];
        }
        int x{}, y{};
        std::cin >> x >> y;
        if (--x > --y) {
            std::swap(x, y);
        }
        auto sum = std::accumulate(interval.begin(), interval.end(), 0LL);
        auto part =
            std::accumulate(interval.begin() + x, interval.begin() + y, 0LL);
        std::cout << std::min(part, sum - part) << std::endl;
    }
    return 0;
}
