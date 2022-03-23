#include <iostream>
#include <array>
#include <cassert>

int main(int argc, char **argv)
{
    constexpr auto LEN = 10000;
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
        assert(n < LEN);
        std::cout << (primes[n] ? "yes" : "no") << std::endl;
    }
    return 0;
}