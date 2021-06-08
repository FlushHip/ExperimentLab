#include <iostream>

int main(int argc, char **argv)
{
    for (int i = 0; i < 10; ++i) {
        std::cout << i << " | ~  : " << ~i << std::endl;
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; /*++i*/) {
        std::cout << i;
        std::cout << " | -~ : " << (i = -~i) << std::endl;
    }
    std::cout << std::endl;
    for (int i = 9; i >= 0; /*--i*/) {
        std::cout << i;
        std::cout << " | ~- : " << (i = ~-i) << std::endl;
    }
    return 0;
}