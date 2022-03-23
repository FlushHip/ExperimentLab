#include <iostream>
#include <string>
#include <bitset>

std::string two_string(int n)
{
    if (n == 0)
        return "0";
    auto digits = std::bitset<32>(n).to_string();
    auto first = digits.find_first_of('1');
    std::string ans = 32 - 1 - first == 1 ? "2" : ("2(" + two_string(32 - 1 - first) + ")");
    for (first = digits.find_first_of('1', first + 1); first != std::string::npos; first = digits.find_first_of('1', first + 1))
        ans += "+" +  (32 - 1 - first == 1 ? "2" : ("2(" + two_string(32 - 1 - first) + ")"));
    return ans;
}

int main(int argc, char **argv)
{
    for (int n = 0; std::cin >> n; ) {
        std::cout << two_string(n) << std::endl;
    }
    return 0;
}