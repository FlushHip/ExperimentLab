#include <iostream>
#include <array>
#include <vector>
#include <limits>

int main(int argc, char **argv)
{
    std::freopen("in.dat", "r", stdin);

    constexpr auto LEN = 32 + 1;
    std::array<bool, LEN> primes;
    primes.fill(true);
    primes[0] = primes[1] = false;

    for (int i = 2; i * i < LEN; ++i) {
        if (!primes[i])
            continue;
        for (int j = i * i; j < LEN; j += i)
            primes[j] = false;
    }
    
    for (int n, a; std::cin >> n >> a; ) {
        std::array<int, LEN * LEN> qs;
        qs.fill(0);
        for (int ii = 2; ii <= n; ++ii) {
            int m = ii;
            for (int i = 2; i < LEN && m > i; ++i) {
                if (!primes[i])
                    continue;
                while (m % i == 0) {
                    m /= i;
                    ++qs[i];
                }
            }
            if (m)
                ++qs[m];
        }

        std::vector<std::pair<int, int>> aq;
        for (int i = 2; i < LEN && a > i; ++i) {
            if (!primes[i] || a % i)
                continue;
            int cnt = 0;
            while (a % i == 0) {
                a /= i;
                ++cnt;
            }
            aq.emplace_back(i, cnt);
        }
        if (a > 1)
            aq.emplace_back(a, 1);
        
        int ans = std::numeric_limits<int>::max();
        for (auto it = aq.begin(); it != aq.end(); ++it)
            ans = std::min(ans, qs[it->first] / it->second);

        std::cout << ans << std::endl;
    }
    return 0;
}