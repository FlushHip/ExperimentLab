#include <iostream>
#include <vector>
#include <array>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::vector<int> things(n);
        for (int i = 0; i < n; ++i)
            std::cin >> things[i];
        std::array<int, 40 + 1> dp = { 1, 0 };
        for (int i = 0; i < n; ++i) {
            for (int j = 40; j >= things[i]; j--)
                dp[j] += dp[j - things[i]];
        }
        std::cout << dp[40] << std::endl;
    }
    return 0;
}