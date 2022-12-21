#include "headers.h"

class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        struct node {
            std::string str;
            int index;
        };
        std::queue<node> que;
        que.emplace(node{""s, 0});
        while (true) {
            auto [str, index] = que.front();
            if (index == s.size()) {
                break;
            }
            que.pop();
            if (std::isalpha(s[index])) {
                que.emplace(
                    node{str + static_cast<char>(std::tolower(s[index])),
                        index + 1});

                str.push_back(std::toupper(s[index]));
                que.emplace(node{std::move(str), index + 1});
            } else {
                str.push_back(s[index]);
                que.emplace(node{std::move(str), index + 1});
            }
        }
        std::vector<std::string> ans;
        for (; !que.empty(); que.pop()) {
            ans.emplace_back(std::move(que.front().str));
        }
        return ans;
    }
};
