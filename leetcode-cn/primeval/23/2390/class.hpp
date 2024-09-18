#include "headers.h"

class Solution {
public:
    string removeStars(string s) {
        struct node_t {
            uint32_t index;
            int alpha;
            int star;
        };
        std::vector<node_t> line;
        for (auto i = 0U; i < s.size();) {
            auto node = node_t{i, 0, 0};
            for (auto& j = i; j < s.size() && ::isalnum(s[j]); ++j) {
                ++node.alpha;
            }
            for (auto& j = i; j < s.size() && s[j] == '*'; ++j) {
                ++node.star;
            }
            line.emplace_back(node);
        }
        // std::for_each(line.begin(), line.end(), [](const auto& e) {
        //     std::cout << e.index << ", " << e.alpha << ", " << e.star
        //               << std::endl;
        // });

        for (auto it = line.rbegin(); it != line.rend(); ++it) {
            if (it->star <= it->alpha) {
                it->alpha -= it->star;
            } else {
                auto pre = std::next(it);
                assert(pre != line.rend());
                pre->alpha -= it->star - it->alpha;
                it->alpha = 0;
            }
        }

        // std::cout << "--------" << std::endl;

        // std::for_each(line.begin(), line.end(), [](const auto& e) {
        //     std::cout << e.index << ", " << e.alpha << ", " << e.star
        //               << std::endl;
        // });

        std::string result;
        for (const auto& node : line) {
            if (node.alpha > 0) {
                result.append(s, node.index, node.alpha);
            }
        }
        return result;
    }
};
