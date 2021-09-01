#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    const int EN = 2;

    std::unique_ptr<Solution> sol[EN] {
        std::make_unique<Solution>(1, 0, 0),
        std::make_unique<Solution>(10, 5, -7.5),
    };

    for (int L = 0; L < EN; ++L) {
        std::cout << "Example " << L + 1 << " :" << std::endl;
        std::vector<std::vector<double>> ans;
        for (int i = 0; i < 10; ++i) {
            ans.emplace_back(sol[L]->randPoint());
        }
        std::cout << ans << std::endl << std::endl;
    }

    return 0;
}
