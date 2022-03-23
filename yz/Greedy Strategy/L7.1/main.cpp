#include <iostream>

int main(int argc, char **argv)
{
    for (int a; std::cin >> a; ) {
        if (a % 2)
            std::cout << "0 0";
        else {
            std::cout << (a / 4 + ((a % 4) / 2)) << " " << a / 2;
        }
        std::cout << std::endl;
    }
    return 0;
}