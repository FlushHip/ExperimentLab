#include "headers.h"

#include "class.hpp"

int main(int argc, char **argv)
{
    auto sol = std::make_unique<Solution>();

    VList<std::string> v{
        "K1:L2",
        "A1:F1",
        "A1:Z9",
        "A1:A1",
    };

    for (auto L = 0u; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->cellsInRange(v[L]);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
                            (std::chrono::steady_clock::now() - start_epoch);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m"
            << std::boolalpha << ans << std::endl
            << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                << duration.count() << "ms\x1b[0m"
            << std::endl << std::endl;
    }

    return 0;
}
