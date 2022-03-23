#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    for (long long m, a, b; std::cin >> m && m; ) {
        std::cin >> a >> b;
        long long ans = a + b;
        std::string str;
        while (ans) {
            str.push_back(static_cast<char>(ans % m) + '0');
            ans /= m;
        }
        for (auto it = str.crbegin(); it != str.crend(); ++it)
            std::cout << *it;
        if (str.empty())
            std::cout << "0";
        std::cout << std::endl;
    }
    return 0;
}