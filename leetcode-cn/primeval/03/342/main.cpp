#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 4;

    auto sol = std::make_unique<Solution>();

    int n[EN]{
        16,
        5,
        1,
        8,
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->isPowerOfFour(n[L]);

        std::cout << std::boolalpha << ans
            << std::endl << std::endl;
    }

    return 0;
}
