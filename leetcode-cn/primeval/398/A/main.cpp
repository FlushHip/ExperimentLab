#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    std::vector<int> v{ 1, 2, 3, 3, 3 };
    auto sol = std::make_unique<Solution>(v);

    std::cout << sol->pick(1) << std::endl;
    std::cout << sol->pick(3) << std::endl;
    std::cout << sol->pick(3) << std::endl;
    std::cout << sol->pick(3) << std::endl;
    std::cout << sol->pick(3) << std::endl;
    std::cout << sol->pick(3) << std::endl;

    return 0;
}
