#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char **argv)
{
    auto from_char = [] (const char c) -> int
    {
        if (std::isdigit(c))
            return c - '0';
        return c - 'A' + 10;
    };
    auto to_char = [] (const int n ) -> char
    {
        if (n < 10)
            return '0' + n;
        return n - 10 + 'A';
    };
    int a = 0, b = 0;
    for (std::string n; std::cin >> a >> n >> b; ) {
        std::transform(n.begin(), n.end(), n.begin(), [](const auto c)
        {
            return std::toupper(c);
        });
        long sum = 0;
        for (auto i = 0u; i < n.size(); ++i) {
            sum *= a;
            sum += from_char(n[i]);
        }
        std::string ans;
        while (sum) {
            ans.push_back(to_char(sum % b));
            sum /= b;
        }
        if (ans.empty())
            ans.push_back(to_char(0));
        std::reverse(ans.begin(), ans.end());
        std::cout << ans << std::endl;
    }
    return 0;
}