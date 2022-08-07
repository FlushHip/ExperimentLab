#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VList<std::pair<int, std::vector<std::string>>> v{
        {2,
            {
                "0:start:0",
                "1:start:2",
                "1:end:5",
                "0:end:6",
            }},
        {1,
            {
                "0:start:0",
                "0:start:2",
                "0:end:5",
                "0:start:6",
                "0:end:6",
                "0:end:7",
            }},
        {2,
            {
                "0:start:0",
                "0:start:2",
                "0:end:5",
                "1:start:6",
                "1:end:6",
                "0:end:7",
            }},
        {2,
            {
                "0:start:0",
                "0:start:2",
                "0:end:5",
                "1:start:7",
                "1:end:7",
                "0:end:8",
            }},
        {1,
            {
                "0:start:0",
                "0:end:0",
            }},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->exclusiveTime(v[L].first, v[L].second);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            (std::chrono::steady_clock::now() - start_epoch) * 1000);

        std::cout << "  |-   \x1b[31mans -> \x1b[0m" << std::boolalpha << ans
                  << std::endl
                  << "    |- " << (duration > 1s ? "\x1b[31m" : "\x1b[36m")
                  << duration.count() << "ms\x1b[0m" << std::endl
                  << std::endl;
    }

    return 0;
}
