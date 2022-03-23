#include <iostream>
#include <array>
#include <vector>

int main(int argc, char **argv)
{
    constexpr auto LEN = 31633;
    std::array<bool, LEN> primes;
    primes.fill(true);
    primes[0] = primes[1] = false;

    for (int i = 2; i * i < LEN; ++i) {
        if (!primes[i])
            continue;
        for (int j = i * i; j < LEN; j += i)
            primes[j] = false;
    }
    
    for (int n; std::cin >> n; ) {
        for (int L = 0, m; L < n; ++L) {
            std::cin >> m;
            int ans = 1;
            for (int i = 2; i < LEN && m > i; ++i) {
                if (!primes[i])
                    continue;
                int q = 1;
                while (m % i == 0) {
                    m /= i;
                    ++q;
                }
                ans *= q;
            }
            if (m > 1)
                ans *= 2;
            std::cout << ans << std::endl;
        }
    }
    return 0;
}