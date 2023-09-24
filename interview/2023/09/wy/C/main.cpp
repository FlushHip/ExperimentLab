#include <functional>
#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (int n{}; std::cin >> n;) {
        constexpr long long mod = 1e9 + 7;
        std::function<long long(long long, long long)> mul =
            [&mod, &mul](long long x, long long y) -> long long {
            if (y == 0) {
                return 1;
            }
            auto res = mul(x, y / 2);
            res = res * res % mod;
            return y % 2 == 0 ? res : res * x % mod;
        };
        auto ny = [&mod, &mul](long long a) { return mul(a, mod - 2) % mod; };
        auto C = [&mod, &ny](long long n, long long m) -> long long {
            if (n < m) {
                return 0;
            }
            if (m > n - m) {
                m = n - m;
            }
            long long a = 1, b = 1;
            for (int i = 0; i < m; ++i) {
                a = (a * (n - i)) % mod;
                b = (b * (i + 1)) % mod;
            }
            return a * ny(b) % mod;
        };
        std::function<long long(long long, long long)> lucas =
            [&lucas, &C, &mod](long long n, long long m) -> long long {
            if (m == 0) {
                return 1;
            }
            return lucas(n / mod, m / mod) * C(n % mod, m % mod) % mod;
        };
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            result =
                (result + dbg(lucas(n - 1, i)) * dbg(ny(i + 1)) % mod) % mod;
        }
        dbg(result);
        long long sum = 0;
        for (int i = 0; i < n; ++i) {
            long long a{};
            std::cin >> a;
            sum = (sum + a) % mod;
        }
        auto ans = sum * result % mod;
        std::cout << ans << std::endl;
    }
    return 0;
}
