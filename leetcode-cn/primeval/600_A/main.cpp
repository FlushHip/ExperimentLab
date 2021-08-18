#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    for (int i = 0; i < 1000; ++i) {
        std::cout << std::setw(3) << i << " : " << sol.findIntegers(i) << std::endl;
    }
    return 0;
}
