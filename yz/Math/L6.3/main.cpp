#include <iostream>
#include <algorithm>

int main(int argc, char **argv)
{
    for (std::string digits; std::cin >> digits; ) {
        std::string binary, ans("0");
        while (!digits.empty()) {
            int up = 0;
            for (auto i = 0u; i < digits.size(); ++i) {
                int n = digits[i] - '0' + up * 10;
                digits[i] = n / 2 + '0';
                up = n % 2;
            }
            binary.push_back(up + '0');
            if (digits.front() == '0')
                digits.erase(0, 1);
        }
        for (auto i = 0u; i < binary.size(); ++i) {
            int up = 0;
            for (auto i = 0u; i < ans.size(); ++i) {
                int n = (ans[i] - '0') * 2 + up;
                ans[i] = n % 10 + '0';
                up = n / 10;
            }
            if (up)
                ans.push_back(up + '0');
            
            up = binary[i] - '0';
            for (auto i = 0u; i < ans.size() && up; ++i) {
                int n = ans[i] - '0' + up;
                ans[i] = n % 10 + '0';
                up = n / 10;
            }
            if (up)
                ans.push_back(up + '0');
        }
        std::reverse(ans.begin(), ans.end());
        std::cout << ans << std::endl;
    }
    return 0;
}