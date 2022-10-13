#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 3;

    auto sol = std::make_unique<Solution>();

    uint32_t n[EN]{
        43261596,
        4294967293,
        0,
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->reverseBits(n[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
