#include <iostream>
#include <array>
#include <vector>

int main(int argc, char **argv)
{
    constexpr auto LEN = 10000 + 1;
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
        std::vector<int> ans;
        for (int i = 2; i < n; ++i) {
            if (primes[i] && i % 10 == 1)
                ans.push_back(i);
        }
        if (ans.empty())
            ans.push_back(-1);

        std::cout << ans.front();
        for (auto it = std::next(ans.begin()); it != ans.end(); ++it)
            std::cout << " " << *it;
        std::cout << std::endl;
    }
    return 0;
}