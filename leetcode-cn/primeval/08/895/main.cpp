#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    VTList<std::vector<int>, int> v{
        {{5, 7, 5, 7, 4, 5}, 4},
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto sol = std::make_unique<FreqStack>();
        for (int ele : std::get<0>(v[L])) {
            sol->push(ele);
        }
        std::vector<int> ans;
        for (int i = 0; i < std::get<1>(v[L]); ++i) {
            ans.push_back(sol->pop());
        }

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
