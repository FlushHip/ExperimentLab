#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 6;

    auto sol = std::make_unique<Solution>();

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        int n[EN]{
            5,
            7,
            11,
            10,
            3,
            4,
        };

        auto ans = sol->hasAlternatingBits(n[L]);

        std::cout << std::boolalpha << ans
            << std::endl << std::endl;
    }

    return 0;
}
