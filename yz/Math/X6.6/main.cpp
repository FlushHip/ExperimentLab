#include <iostream>
#include <array>
#include <vector>

int main(int argc, char **argv)
{
    constexpr auto LEN = 104729 + 1;
    constexpr auto INDEX_LEN = 10000 + 1;
    std::array<bool, LEN> primes;
    std::array<int, INDEX_LEN> primes_index;
    primes.fill(true);
    primes[0] = primes[1] = false;

    for (int i = 2; i * i < LEN; ++i) {
        if (!primes[i])
            continue;
        for (int j = i * i; j < LEN; j += i)
            primes[j] = false;
    }
    for (int i = 2, index = 1; i < LEN; ++i)
        if (primes[i])
            primes_index[index++] = i;

    for (int k; std::cin>> k; ) {
        std::cout << primes_index[k] << std::endl;
    }
    return 0;
}