#include <iostream>
#include <string>
#include <cctype>

int main(int argc, char **argv)
{
    std::string str;
    while (std::getline(std::cin, str) && str != "ENDOFINPUT") {
        std::getline(std::cin, str);
        for (auto i = 0u; i < str.size(); ++i) {
            if (!std::isalpha(str[i]))
                std::cout << str[i];
            else
                std::cout << static_cast<char>(((str[i] - 'A' - 5 + 26) % 26) + 'A');
        }
        std::cout << std::endl;

        std::getline(std::cin, str);
    }
    return 0;
}