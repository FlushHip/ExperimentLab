#include <iostream>
#include <tuple>
#include <unordered_map>
#include <string>

int main(int argc, char **argv)
{
    for (int n, m; std::cin >> n; ) {
        std::unordered_map<std::string, std::tuple<std::string, std::string, std::string>> database;
        while (n--) {
            std::string a, b, c, d;
            std::cin >> a >> b >> c >> d;
            database.emplace(a, std::make_tuple(b, c, d));
        }
        for (std::cin >> m; m--; ) {
            std::string a;
            std::cin >> a;
            auto it = database.find(a);
            if (database.end() == it)
                std::cout << "No Answer!";
            else
                std::cout << it->first << " " << std::get<0>(it->second) << " " << std::get<1>(it->second) << " " << std::get<2>(it->second);
            std::cout << std::endl;
        }
    }
    return 0;
}