#include <iostream>
#include <vector>

// #include <dbg.h>

int main() {
    int T{};
    std::cin >> T;
    while (T--) {
        int n{}, q{};
        std::cin >> n >> q;
        std::vector<long long> diff(n + 1, 0);
        while (q--) {
            long long a{}, b{};
            std::cin >> a >> b;

            long long base = a / n;
            diff[0] += base;
            diff[n] -= base;

            long long rest = a % n;
            if (b + rest <= n) {
                diff[b] += 1;
                diff[b + rest] -= 1;
            } else {
                diff[0] += 1;
                diff[b + rest - n] -= 1;

                diff[b] += 1;
                diff[n] -= 1;
            }
        }
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += diff[i];
            std::cout << sum << " \n"[i + 1 == n];
        }
    }
    return 0;
}
