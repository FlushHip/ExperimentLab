#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 5;

    auto sol = std::make_unique<Solution>();

    std::pair<int, std::string> v[EN]{
        { 3, "PAYPALISHIRING" },
        { 4, "PAYPALISHIRING" },
        { 1, "A" },
        { 1, "ABCD" },
        { 2, "ABCD" },
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->convert(v[L].second, v[L].first);

        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
