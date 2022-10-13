#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 11;

    auto sol = std::make_unique<Solution>();

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->readBinaryWatch(L);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
