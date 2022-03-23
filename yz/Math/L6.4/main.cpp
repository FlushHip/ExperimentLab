#include <iostream>
#include <algorithm>
#include <cctype>

int main(int argc, char **argv)
{
    freopen("in.dat", "r", stdin);

    auto from_char = [](char c) -> int
    {
        if (std::isdigit(c))
            return c - '0';
        return c - 'A' + 10;
    };
    auto to_char = [](int n) -> char
    {
        if (n < 10)
            return n + '0';
        return n - 10 + 'a';
    };
    for (int m, n; std::cin >> m >> n; ) {
        std::string digit_m;
        std::cin >> digit_m;

        std::string digits("0");
        for (auto L = 0u; L < digit_m.size(); ++L) {
            int up = 0;
            for (auto i = 0u; i < digits.size(); ++i) {
                int t = m * from_char(digits[i]) + up;
                digits[i] = to_char(t % 10);
                up = t / 10;
            }
            if (up) {
                digits.push_back(to_char(up % 10));
                if (up / 10)
                    digits.push_back(to_char(up / 10));
            }
            up = from_char(digit_m[L]);
            for (auto i = 0u; i < digits.size() && up; ++i) {
                int t = from_char(digits[i]) + up;
                digits[i] = to_char(t % 10);
                up = t / 10;
            }
            if (up) {
                digits.push_back(to_char(up % 10));
                if (up / 10)
                    digits.push_back(to_char(up / 10));
            }
        }
        std::reverse(digits.begin(), digits.end());
        
        std::string digit_n;
        while (!digits.empty()) {
            int up = 0;
            for (auto i = 0u; i < digits.size(); ++i) {
                int t = from_char(digits[i]) + up * 10;
                digits[i] = to_char(t / n);
                up = t % n;
            }
            digit_n.push_back(to_char(up));
            while (!digits.empty() && digits.front() == '0')
                digits.erase(0, 1);
        }
        std::reverse(digit_n.begin(), digit_n.end());

        std::cout << digit_n << std::endl;
    }
    return 0;
}