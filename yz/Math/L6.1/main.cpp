#include <iostream>
#include <bitset>

int main(int argc, char **argv)
{
    for (unsigned int n; std::cin >> n; ) {
        auto str = std::bitset<32>(n).to_string();
        std::cout << str.erase(0, str.find_first_not_of('0')) << std::endl;
    }
    return 0;
}