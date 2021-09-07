#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    int n[EN]{
        2,
        5,
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->countBits(n[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
