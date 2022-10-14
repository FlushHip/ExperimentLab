#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    auto sol = std::make_unique<Solution>();

    std::pair<int, int> p[EN]{
        { 6, 10 },
        { 10, 15 },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->countPrimeSetBits(p[L].first, p[L].second);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
