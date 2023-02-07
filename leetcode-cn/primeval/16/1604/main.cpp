#include "headers.h"

#include "class.hpp"

int main(int argc, char** argv) {
    auto sol = std::make_unique<Solution>();

    VTList<std::vector<std::string>, std::vector<std::string>> v{
        {
            {"daniel", "daniel", "daniel", "luis", "luis", "luis", "luis"},
            {"10:00", "10:40", "11:00", "09:00", "11:00", "13:00", "15:00"},
        },
        {
            {"alice", "alice", "alice", "bob", "bob", "bob", "bob"},
            {"12:01", "12:00", "18:00", "21:00", "21:20", "21:30", "23:00"},
        },
        {
            {"john", "john", "john"},
            {"23:58", "23:59", "00:01"},
        },
        {
            {"leslie", "leslie", "leslie", "clare", "clare", "clare", "clare"},
            {"13:00", "13:20", "14:00", "18:00", "18:51", "19:30", "19:49"},
        },
    };

    for (auto L = 0U; L < v.size(); ++L) {
        std::cout << "\x1b[32mExample " << L + 1 << " :\x1b[0m" << std::endl;

        std::cout << "  |-   \x1b[33mdata-> \x1b[0m" << v[L] << std::endl;

        auto start_epoch = std::chrono::steady_clock::now();

        auto ans = sol->alertNames(UNPACK_2(v[L]));

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
