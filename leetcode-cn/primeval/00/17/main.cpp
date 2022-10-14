#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 5;

    auto sol = std::make_unique<Solution>();

    std::string s[EN]{
        "23",
        "",
        "2",
        "9876",
        "258",
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->letterCombinations(s[L]);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
