#include <iostream>
#include <string>
#include <algorithm>

int main(int argc, char **argv)
{
    for (std::string a, b; std::getline(std::cin, a) && a != "#"; ) {
        std::getline(std::cin, b);
        for (auto i = 0u; i < a.size(); ++i) {
            std::cout << a[i] << " " << std::count(b.begin(), b.end(), a[i]) << std::endl;
        }
    }
    return 0;
}