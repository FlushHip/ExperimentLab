#include <iostream>
#include <map>
#include <vector>

int main(int argc, char **argv)
{
    for (int n, m; std::cin >> n >> m; ) {
        std::map<int, int> database;
        std::vector<int> peoples(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> peoples[i];
            ++database[peoples[i]];
        }
        for (int i = 0; i < n; ++i) {
            if (1 == database[peoples[i]])
                std::cout << "BeiJu";
            else
                std::cout << database[peoples[i]] - 1;
            std::cout << std::endl;
        }
    }
    return 0;
}