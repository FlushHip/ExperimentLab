#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>

int main(int argc, char **argv)
{
    for (std::string str; std::cin >> str; ) {
        std::unordered_set<char> mp;
        for (auto i = 0u; i < str.size(); ++i) {
            if (mp.find(str[i]) != mp.end())
                continue;
            mp.emplace(str[i]);
            auto start = str.find(str[i], i + 1);
            if (start == std::string::npos)
                continue;
            std::cout << str[i] << ":" << i;
            for (; start != std::string::npos; start = str.find(str[i], start + 1))
                std::cout << "," << str[i] << ":" << start;
            std::cout << std::endl;
        }
    }
    return 0;
}