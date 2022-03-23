#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    for (int h; std::cin >> h; ) {
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < h + 2 * (h - 1) - (h + 2 * i); ++j)
                std::cout << " ";
            for (int j = 0; j < h + 2 * i; ++j)
                std::cout << "*";
            std::cout << std::endl;
        }
    }
    return 0;
}