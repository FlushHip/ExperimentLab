#include <iostream>

int main(int argc, char **argv)
{
    for (std::string a, b; std::cin >> a >> b; ) {
        int ans = 0;
        for (auto i = 0u; i < a.size(); ++i) {
            for (auto j = 0u; j < b.size(); ++j) {
                ans += (a[i] - '0') * (b[j] - '0');
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}