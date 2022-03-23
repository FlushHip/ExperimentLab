#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str; ) {
        std::sort(str.begin(), str.end());
        do {
            std::cout << str << std::endl;
        } while (std::next_permutation(str.begin(), str.end()));
    }
    return 0;
}