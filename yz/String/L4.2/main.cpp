#include <iostream>
#include <string>
#include <cctype>

int main(int argc, char **argv)
{
    std::string str;
    std::getline(std::cin, str);
    for (auto i = 0u; i < str.size(); ++i) {
        if (!std::isalpha(str[i]))
            std::cout << str[i];
        else if (std::isupper(str[i]))
            std::cout << static_cast<char>(((str[i] - 'A' + 1) % 26) + 'A');
        else
            std::cout << static_cast<char>(((str[i] - 'a' + 1) % 26) + 'a');
    }
    std::cout << std::endl;
    return 0;
}