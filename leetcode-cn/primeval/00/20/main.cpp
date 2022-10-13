#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 6;

    auto sol = std::make_unique<Solution>();

    std::string s[EN]{
        "()",
        "()[]{}",
        "(]",
        "([)]",
        "{[]}",
        "(",
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        bool ans = sol->isValid(s[L]);

        std::cout << std::boolalpha << ans
            <<  std::endl << std::endl;
    }

    return 0;
}
