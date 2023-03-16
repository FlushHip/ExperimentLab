#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            std::string str = std::to_string(i);
            if (i % 7 == 0 || std::any_of(str.begin(), str.end(), [](const auto & c)
            {
                return c == '7';
            }))
                continue;
            sum += i * i;
        }
        std::cout << sum << std::endl;
    }
    return 0;
}