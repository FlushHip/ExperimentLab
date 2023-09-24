#include <cmath>
#include <iostream>
#include <limits>
#include <tuple>
#include <vector>

#include <dbg.h>

int main() {
    for (std::string line; std::cin >> line;) {
        auto prase = [](std::string_view line) {
            std::vector<int> ret;
            for (auto begin = 0; begin != std::string::npos;) {
                auto pos = line.find(',', begin);
                std::string num;
                if (pos != std::string::npos) {
                    num = line.substr(begin, pos - begin);
                    begin = pos + 1;
                } else {
                    num = line.substr(begin);
                    begin = pos;
                }
                ret.emplace_back(std::stoi(num));
            }
            return ret;
        };
        auto v_p = prase(line);
        int n = v_p[0], r = v_p[1];
        int min_x = std::numeric_limits<int>::max(), min_y = min_x;
        int max_x = std::numeric_limits<int>::min(), max_y = max_x;

        std::vector<std::tuple<int, int, int>> towers;
        for (int i = 0; i < n; ++i) {
            std::cin >> line;
            v_p = prase(line);
            min_x = std::min(min_x, v_p[0]);
            max_x = std::max(max_x, v_p[0]);
            min_y = std::min(min_y, v_p[1]);
            max_y = std::max(max_y, v_p[1]);
            towers.emplace_back(v_p[0], v_p[1], v_p[2]);
        }
        dbg(towers);
        int ans_value = std::numeric_limits<int>::min();
        int ans_x{}, ans_y{};
        for (int x = min_x; x <= max_x; ++x) {
            for (int y = min_y; y <= max_y; ++y) {
                int sum = 0;
                for (auto&& [_x, _y, q] : towers) {
                    sum += q /
                        (1 +
                            std::sqrt(
                                (_x - x) * (_x - x) + (_y - y) * (_y - y)));
                }
                if (sum > ans_value) {
                    ans_value = sum;
                    ans_x = x;
                    ans_y = y;
                }
            }
        }
        std::cout << ans_x << "," << ans_y << std::endl;
    }
    return 0;
}
