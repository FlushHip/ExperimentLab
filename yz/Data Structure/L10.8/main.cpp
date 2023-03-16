#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>

int main(int argc, char **argv)
{
    std::unordered_map<std::string ,std::string> q, h;
    std::string line;
    for (; std::getline(std::cin, line) && line != "@END@"; ) {
        auto mid = line.find(']');
        auto a = line.substr(0, mid + 1);
        auto b = line.substr(mid + 2, line.size() - mid - 2);
        q[a] = b;
        h[b] = a;
    }

    int m;
    std::cin >> m;
    std::getline(std::cin, line);
    for (; std::getline(std::cin, line) && m--; ) {
        if (line.front() == '[') {
            auto it = q.find(line);
            if (q.end() == it)
                std::cout << "what?";
            else
                std::cout << it->second;
        } else {
            auto it = h.find(line);
            if (h.end() == it)
                std::cout << "what?";
            else
                std::cout << it->second.substr(1, it->second.size() - 2);
        }
        std::cout << std::endl;
    }
    return 0;
}