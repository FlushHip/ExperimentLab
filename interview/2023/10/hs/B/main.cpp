#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    const int N = 10000 + 1;
    std::vector<bool> is_prime(N, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * 2 <= N; ++i) {
        if (is_prime[i]) {
            for (int j = 2; i * j <= N; ++j) {
                is_prime[i * j] = false;
            }
        }
    }
    dbg(is_prime);
    for (int n{}; std::cin >> n;) {
        int sum = 0;
        for (int i = 1; i < n; ++i) {
            if (is_prime[i]) {
                sum += i;
            }
        }
        dbg(sum);
        std::cout << std::fixed << std::setprecision(4) << std::sqrt(sum)
                  << std::endl;
    }
    return 0;
}
