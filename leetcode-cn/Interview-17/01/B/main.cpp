#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    std::cout << sol.add(0, 0) << std::endl;
    std::cout << sol.add(1, 0) << std::endl;
    std::cout << sol.add(12, 35) << std::endl;
    std::cout << sol.add(12, -35) << std::endl;

    return 0;
}
