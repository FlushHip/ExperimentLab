#include "headers.h"

class Solution {
public:
    bool parseBoolExpr(string expression) {
        int index = 0;
        return dfs(index, expression);
    }

private:
    bool dfs(int& index, std::string_view expression) {
        switch (expression[index++]) {
        case '!':
            return !exp_not(index, expression);
        case '|':
            return exp_logic<std::logical_or<>>(index, expression);
        case '&':
            return exp_logic<std::logical_and<>>(index, expression);
        case 'f':
            return false;
        case 't':
            return true;
        }
        return false;
    }

    bool exp_not(int& index, std::string_view expression) {
        ++index;
        bool ans = dfs(index, expression);
        ++index;
        return ans;
    }

    template <typename Op>
    bool exp_logic(int& index, std::string_view expression) {
        bool ans = !Op{}(true, false);
        do {
            ++index;
            ans = Op{}(ans, dfs(index, expression));
        } while (expression[index] == ',');
        ++index;
        return ans;
    }
};
