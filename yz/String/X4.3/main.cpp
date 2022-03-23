#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

int main(int argc, char **argv)
{
    for (std::string str; std::getline(std::cin, str); ) {
        if (std::isalpha(str[0]))
            str[0] = std::toupper(str[0]);
        for (auto i = 1u; i < str.size(); ++i) {
            if (std::isspace(str[i - 1]) && std::isalpha(str[i]))
                str[i] = toupper(str[i]);
        }
        std::cout << str << std::endl;
    }
    return 0;
}