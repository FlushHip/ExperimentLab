#include <iostream>
#include <string>
#include <cmath>

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str; ) {
        int n = (int)str.size();
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += (str[i] - '0') * (static_cast<int>(std::pow(2, n - i)) - 1);
        }
        std::cout << ans << std::endl;
    }
    return 0;
}