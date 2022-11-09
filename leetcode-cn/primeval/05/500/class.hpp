#include "headers.h"

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        std::vector<std::string> ans;
        auto line_num = [](char c) {
            c = std::tolower(c);
            std::array<std::string_view, 3> lines{
                "qwertyuiop",
                "asdfghjkl",
                "zxcvbnm",
            };
            for (int i = 0; i < 3; ++i) {
                if (std::any_of(lines[i].begin(), lines[i].end(),
                        [c](char cc) { return cc == c; })) {
                    return i;
                }
            }
            return -1;
        };
        for (std::string_view word : words) {
            if (std::all_of(word.begin() + 1, word.end(),
                    [line = line_num(word.front()), &line_num](
                        char c) { return line_num(c) == line; })) {
                ans.emplace_back(word);
            }
        }
        return ans;
    }
};
