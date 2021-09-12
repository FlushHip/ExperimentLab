#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    for (int i = 1; i < 1100; ++i) {
        auto ans = sol->findIntegers(i);
        std::cout << i << " : " << ans << std::endl;
    }

    return 0;
}
