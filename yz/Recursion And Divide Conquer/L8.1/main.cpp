#include <iostream>

int main(int argc, char **argv)
{
    for (unsigned long long n; std::cin >> n; ) {
        unsigned long long ans = 1ull;
        for (auto i = 1ull; i <= n; ++i)
            ans *= i;
        std::cout << ans << std::endl;
    }
    return 0;
}