#include "headers.h"

class Solution {
public:
    vector<int> diffWaysToCompute(string expression) { return dfs(expression); }

private:
    std::vector<int> dfs(std::string_view expression) {
        std::vector<int> res;
        for (int i = 0; i < expression.size(); ++i) {
            if (expression[i] == '+' || expression[i] == '-' ||
                expression[i] == '*') {
                auto lhs = dfs(expression.substr(0, i));
                auto rhs =
                    dfs(expression.substr(i + 1, expression.size() - i - 1));
                for (int left : lhs) {
                    for (int right : rhs) {
                        res.push_back(expression[i] == '+' ? left + right
                                : expression[i] == '-'     ? left - right
                                                           : left * right);
                    }
                }
            }
        }
        if (res.empty()) {
            res.push_back(std::stoi(std::string(expression)));
        }
        return res;
    }
};
