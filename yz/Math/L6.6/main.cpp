#include <iostream>
#include <numeric>

int main(int argc, char **argv)
{
    for (unsigned int a, b; std::cin >> a >> b; ) {
        std::cout << std::lcm(a, b) << std::endl;
    }
    return 0;
}