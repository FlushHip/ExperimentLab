#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::tuple<std::vector<std::vector<int>>, std::vector<int>, std::vector<int>>> v{
        { {
            {691938,300406},
            {710196,624190},
            {858790,609485},
            {268029,225806},
            {200010,188664},
            {132599,612099},
            {329444,633495},
            {196657,757958},
            {628509,883388},
            }, {655988,180910}, {267728,840949} },
        { {
            { 0, 1 },
            { 1, 0 },
            }
            , { 0, 0 }, { 0, 2 } },
        { {
            }
            , { 0, 0 }, { 999999, 999999 } },
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;

        auto ans = sol->isEscapePossible(std::get<0>(v[L]), std::get<1>(v[L]), std::get<2>(v[L]));

        std::cout << std::boolalpha << ans
            << std::endl << std::endl;
    }

    return 0;
}
