#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 6;

    auto sol = std::make_unique<Solution>();

    std::string s[EN]{
        "42",
        "         -42",
        "4193 with words",
        "words and 987",
        "-91283472332",
        "+1",
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->myAtoi(s[L]);

        std::cout << ans
            << std::endl << std::endl;
    }

    return 0;
}
