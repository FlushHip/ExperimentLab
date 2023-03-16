#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str; ) {
        std::cout << std::stoi(str, nullptr, 16) << std::endl;
    }
    return 0;
}