#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 100;

    auto sol = std::make_unique<Solution>();

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        std::cout << sol->fib(L) << std::endl;
    }

    return 0;
}
