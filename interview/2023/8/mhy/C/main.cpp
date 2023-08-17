#include <iostream>

#include <dbg.h>

int main() {
    for (double p{}; std::cin >> p;) {
        std::vector<double> dp(90 * 2 + 1, 0.0);
        for (int i = 1; i <= 90; ++i) {
            dp[i] = std::pow(1 - p, i - 1) * (i == 90 ? 1.0 / 2 : p / 2);
        }
        for (int i = 1; i <= 90; ++i) {
            double a = std::pow(1 - p, i - 1) * (i == 90 ? 1.0 / 2 : p / 2);
            for (int j = 1; j <= 90; ++j) {
                dp[i + j] += a * std::pow(1 - p, j - 1) * (j == 90 ? 1 : p);
            }
        }
        double ans = 0.0;
        for (int i = 1; i <= 180; ++i) {
            ans += i * dp[i];
        }
        std::cout << dbg(p, ans) << std::endl;
    }
    return 0;
}
