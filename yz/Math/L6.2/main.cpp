#include <iostream>
#include <algorithm>

int main(int argc, char **argv)
{
    for (std::string digits; std::cin >> digits; ) {
        std::string ans;
        while (!digits.empty()) {
            int up = 0;
            for (auto i = 0u; i < digits.size(); ++i) {
                int n = digits[i] - '0' + up * 10;
                digits[i] = n / 2 + '0';
                up = n % 2;
            }
            ans.push_back(up + '0');
            if (digits.front() == '0')
                digits.erase(0, 1);
        }
        std::reverse(ans.begin(), ans.end());
        std::cout << ans << std::endl;
    }
    return 0;
}