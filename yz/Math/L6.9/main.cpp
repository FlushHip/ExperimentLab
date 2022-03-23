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
        int ans = 0;
        for (int i = 2; i < LEN && n > i; ++i) {
            if (!primes[i])
                continue;
            while (n % i == 0) {
                n /= i;
                ++ans;
            }
        }
        if (n)
            ++ans;
        std::cout << ans << std::endl;
    }
    return 0;
}