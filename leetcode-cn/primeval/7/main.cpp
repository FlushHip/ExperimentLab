#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 5;

    auto sol = std::make_unique<Solution>();

    int x[EN]{
        123,
        -123,
        120,
        0,
        1123456789,
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->reverse(x[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
