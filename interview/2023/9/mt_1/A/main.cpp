#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

int main() {
    for (int n{}; std::cin >> n;) {
        std::vector<std::pair<double, double>> lines(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> lines[i].first >> lines[i].second;
        }
        double x{}, y{};
        std::cin >> x >> y;
        if (x <= 0 || y <= 0 || y > x ||
            std::any_of(lines.begin(), lines.end(), [](const auto& pr) {
                return pr.first <= 0 || pr.second <= 0 || pr.second > pr.first;
            })) {
            std::cout << "error" << std::endl;
            continue;
        }
        auto ans_1 = std::accumulate(lines.begin(), lines.end(), 0.0,
            [](double init, const auto& pr) { return init + pr.second; });
        auto ans_2 = std::accumulate(lines.begin(), lines.end(), 0.0,
            [](double init, const auto& pr) { return init + pr.first; });
        ans_2 = ans_2 >= x ? ans_2 - y : ans_2;
        std::cout << std::fixed << std::setprecision(2)
                  << std::min(ans_1, ans_2) << std::endl;
    }
    return 0;
}
