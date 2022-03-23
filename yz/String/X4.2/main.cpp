#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char **argv)
{
    for (std::string str, a, b; std::getline(std::cin, str); ) {
        std::getline(std::cin, a);
        std::getline(std::cin, b);
        std::stringstream sin(str);
        for (std::string word; sin >> word; ) {
            if (word == a)
                std::cout << b;
            else
                std::cout << word;
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}