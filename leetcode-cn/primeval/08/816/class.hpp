#include "headers.h"

class Solution {
public:
    vector<string> ambiguousCoordinates(string s) {
        std::vector<std::string> ans;
        for (int i = 1 + 1; i < s.size() - 1; ++i) {
            auto lhs = enum_digit({s.c_str() + 1,
                static_cast<std::string_view::size_type>(i - 1)});
            auto rhs = enum_digit({s.c_str() + i,
                static_cast<std::string_view::size_type>(s.size() - 1 - i)});
            for (const auto& l : lhs) {
                for (const auto& r : rhs) {
                    ans.emplace_back("(" + l + ", " + r + ")");
                }
            }
        }
        return ans;
    }

private:
    std::vector<std::string> enum_digit(std::string_view digits) {
        std::vector<std::string> ans;
        if (digits.size() == 1 || digits.front() != '0') {
            ans.emplace_back(digits);
        }
        for (int i = 1; i < digits.size(); ++i) {
            if (digits[0] == '0' && i != 1) {
                break;
            }
            if (digits.back() == '0') {
                break;
            }
            ans.emplace_back(std::string(digits.begin(), digits.begin() + i) +
                "." + std::string(digits.begin() + i, digits.end()));
        }
        return ans;
    }
};
