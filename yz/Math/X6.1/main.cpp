#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::cout << std::oct << n << std::endl;
    }
    return 0;
}