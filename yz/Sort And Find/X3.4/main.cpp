#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <functional>
#include <cmath>

int main(int argc, char **argv)
{
    enum node_index
    {
        kPosition = 0,
        kNumberOfGold,
        kNumberOfGift,
        kNumberOfPersion,
        kRatioOfGold,
        kRatioOfGift,
        kMaybeOrder,
    };
    enum postion_index
    {
        kOrder = 1,
        kMethod,
    };
    for (int n, m; std::cin >> n >> m; ) {
        std::vector<std::tuple<int, int, int, int, double, double, int>> nodes(n);
        for (int i = 0; i < n; ++i) {
            std::get<kPosition>(nodes[i]) = i;
            std::cin >> std::get<kNumberOfGold>(nodes[i])
                >> std::get<kNumberOfGift>(nodes[i])
                >> std::get<kNumberOfPersion>(nodes[i]);
            std::get<kRatioOfGold>(nodes[i]) = !std::get<kNumberOfGold>(nodes[i]) ?
                0 : std::get<kNumberOfGold>(nodes[i]) * 1.0 / std::get<kNumberOfPersion>(nodes[i]);
            std::get<kRatioOfGift>(nodes[i]) = !std::get<kNumberOfGift>(nodes[i]) ?
                0 : std::get<kNumberOfGift>(nodes[i]) * 1.0 / std::get<kNumberOfPersion>(nodes[i]);
        }
        std::vector<std::tuple<int, int, int>> positions(m, std::make_tuple(0, n, 0));
        for (int i = 0; i < m; ++i)
            std::cin >> std::get<kPosition>(positions[i]);

        auto cmp = [](int method, const auto & lhs, const auto & rhs)
        {
            static const double esp = 1e-6;
            switch (method)
            {
            case 0:
                return std::get<kPosition>(lhs) < std::get<kPosition>(rhs);
                break;
            case 1:
                return std::get<kNumberOfGold>(lhs) > std::get<kNumberOfGold>(rhs);
                break;
            case 2:
                return std::get<kNumberOfGift>(lhs) > std::get<kNumberOfGift>(rhs);
                break;
            case 3:
                return std::get<kRatioOfGold>(lhs) > std::get<kRatioOfGold>(rhs)
                    && std::fabs(std::get<kRatioOfGold>(lhs) - std::get<kRatioOfGold>(rhs)) > esp;
                break;
            case 4:
                return std::get<kRatioOfGift>(lhs) > std::get<kRatioOfGift>(rhs)
                    && std::fabs(std::get<kRatioOfGift>(lhs) - std::get<kRatioOfGift>(rhs)) > esp;
                break;
            default:
                break;
            }
            return false;
        };

        // 1
        std::sort(nodes.begin(), nodes.end()
            , std::bind(cmp, 1, std::placeholders::_1, std::placeholders::_2));
        std::get<kMaybeOrder>(nodes[0]) = 1;
        for (int i = 1; i < n; ++i) {
            if (std::get<kNumberOfGold>(nodes[i]) == std::get<kNumberOfGold>(nodes[i - 1]))
                std::get<kMaybeOrder>(nodes[i]) = std::get<kMaybeOrder>(nodes[i - 1]);
            else
                std::get<kMaybeOrder>(nodes[i]) = i + 1;
        }
        std::sort(nodes.begin(), nodes.end()
            , std::bind(cmp, 0, std::placeholders::_1, std::placeholders::_2));
        for (int i = 0; i < m; ++i) {
            if (std::get<kOrder>(positions[i]) > std::get<kMaybeOrder>(nodes[std::get<kPosition>(positions[i])])) {
                std::get<kOrder>(positions[i]) = std::get<kMaybeOrder>(nodes[std::get<kPosition>(positions[i])]);
                std::get<kMethod>(positions[i]) = 1;
            }
        }
        // 2
        std::sort(nodes.begin(), nodes.end()
            , std::bind(cmp, 2, std::placeholders::_1, std::placeholders::_2));
        std::get<kMaybeOrder>(nodes[0]) = 1;
        for (int i = 1; i < n; ++i) {
            if (std::get<kNumberOfGift>(nodes[i]) == std::get<kNumberOfGift>(nodes[i - 1]))
                std::get<kMaybeOrder>(nodes[i]) = std::get<kMaybeOrder>(nodes[i - 1]);
            else
                std::get<kMaybeOrder>(nodes[i]) = i + 1;
        }
        std::sort(nodes.begin(), nodes.end()
            , std::bind(cmp, 0, std::placeholders::_1, std::placeholders::_2));
        for (int i = 0; i < m; ++i) {
            if (std::get<kOrder>(positions[i]) > std::get<kMaybeOrder>(nodes[std::get<kPosition>(positions[i])])) {
                std::get<kOrder>(positions[i]) = std::get<kMaybeOrder>(nodes[std::get<kPosition>(positions[i])]);
                std::get<kMethod>(positions[i]) = 2;
            }
        }
        // 3
        std::sort(nodes.begin(), nodes.end()
            , std::bind(cmp, 3, std::placeholders::_1, std::placeholders::_2));
        std::get<kMaybeOrder>(nodes[0]) = 1;
        for (int i = 1; i < n; ++i) {
            if (std::get<kRatioOfGold>(nodes[i]) == std::get<kRatioOfGold>(nodes[i - 1]))
                std::get<kMaybeOrder>(nodes[i]) = std::get<kMaybeOrder>(nodes[i - 1]);
            else
                std::get<kMaybeOrder>(nodes[i]) = i + 1;
        }
        std::sort(nodes.begin(), nodes.end()
            , std::bind(cmp, 0, std::placeholders::_1, std::placeholders::_2));
        for (int i = 0; i < m; ++i) {
            if (std::get<kOrder>(positions[i]) > std::get<kMaybeOrder>(nodes[std::get<kPosition>(positions[i])])) {
                std::get<kOrder>(positions[i]) = std::get<kMaybeOrder>(nodes[std::get<kPosition>(positions[i])]);
                std::get<kMethod>(positions[i]) = 3;
            }
        }
        // 4
        std::sort(nodes.begin(), nodes.end()
            , std::bind(cmp, 4, std::placeholders::_1, std::placeholders::_2));
        std::get<kMaybeOrder>(nodes[0]) = 1;
        for (int i = 1; i < n; ++i) {
            if (std::get<kRatioOfGift>(nodes[i]) == std::get<kRatioOfGift>(nodes[i - 1]))
                std::get<kMaybeOrder>(nodes[i]) = std::get<kMaybeOrder>(nodes[i - 1]);
            else
                std::get<kMaybeOrder>(nodes[i]) = i + 1;
        }
        std::sort(nodes.begin(), nodes.end()
            , std::bind(cmp, 0, std::placeholders::_1, std::placeholders::_2));
        for (int i = 0; i < m; ++i) {
            if (std::get<kOrder>(positions[i]) > std::get<kMaybeOrder>(nodes[std::get<kPosition>(positions[i])])) {
                std::get<kOrder>(positions[i]) = std::get<kMaybeOrder>(nodes[std::get<kPosition>(positions[i])]);
                std::get<kMethod>(positions[i]) = 4;
            }
        }

        for (int i = 0; i < m; ++i)
            std::cout << std::get<kOrder>(positions[i]) << ":" << std::get<kMethod>(positions[i]) << std::endl;
        std::cout << std::endl;
    }
    return 0;
}