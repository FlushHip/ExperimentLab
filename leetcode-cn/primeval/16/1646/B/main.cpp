#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    Solution sol{};

    for (int i = 0; i < 10; ++i) {
        std::cout << i << " : " << sol.getMaximumGenerated(i) << std::endl;
    }
    return 0;
}
