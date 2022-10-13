#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 5;

    auto sol = std::make_unique<Solution>();

    std::pair<std::string, std::string> str[EN]{
        { "1.01", "1.001" },
        { "1.0", "1.0.0" },
        { "0.1", "1.1" },
        { "1.0.1", "1" },
        { "7.5.2.4", "7.5.3" },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        std::cout << sol->compareVersion(str[L].first, str[L].second)
            << std::endl << std::endl;
    }

    return 0;
}
