#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 4;

    auto sol = std::make_unique<Solution>();

    int x[EN]{
        121,
        -121,
        10,
        -101,
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->isPalindrome(x[L]);

        std::cout << std::boolalpha << ans << std::endl << std::endl;
    }

    return 0;
}
