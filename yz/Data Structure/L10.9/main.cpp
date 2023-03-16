#include <iostream>
#include <map>
#include <string>

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str; ) {
        std::map<std::string, int> database;
        for (auto i = 0u; i < str.size(); ++i)
            for (auto j = i + 1; j <= str.size(); ++j)
                ++database[str.substr(i, j - i)];
        for (const auto &element : database)
            if (element.second > 1)
                std::cout << element.first << " " << element.second << std::endl;
    }
    return 0;
}