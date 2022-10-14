#include "headers.h"

class Solution {
public:
    int evaluate(string expression) {
        auto begin = expression.begin();
        return evaluate_aux(expression, begin);
    }

private:
    int evaluate_aux(std::string& expression, std::string::iterator& begin) {
        if (*begin == ' ') {  // deal (add and mult)'s space
            return evaluate_aux(expression, ++begin);
        } else if (*begin == '(') {
            struct raii {
                raii(std::string::iterator& begin) : begin(begin) { ++begin; }
                ~raii() { ++begin; }
                std::string::iterator& begin;
            } raii(begin);
            if (*begin == 'l') {  // let
                begin += 3 + 1;

                std::vector<std::string> names;
                int result = 0;
                for (;;) {
                    if (!::islower(*begin)) {
                        result = evaluate_aux(expression, begin);
                        break;
                    }

                    auto name = deal_variable(expression, begin);

                    if (*begin == ')') {
                        result = variables_[name].back();
                        break;
                    }

                    names.push_back(name);

                    ++begin;
                    int value = evaluate_aux(expression, begin);
                    ++begin;

                    variables_[name].push_back(value);
                }
                for (const auto& name : names) {
                    variables_[name].pop_back();
                }
                return result;
            } else if (*begin == 'a') {  // add
                begin += 3 + 1;
                return evaluate_aux(expression, begin) +
                    evaluate_aux(expression, begin);
            } else {  // mult
                begin += 4 + 1;
                return evaluate_aux(expression, begin) *
                    evaluate_aux(expression, begin);
            }
        } else {  // deal expression (variable or value)
            if (::islower(*begin)) {
                auto name = deal_variable(expression, begin);
                return variables_[name].back();
            } else {
                auto result = deal_value(expression, begin);
                return result;
            }
        }

        return 0;
    }

    std::string deal_variable(std::string& expression,
        std::string::iterator& begin) {
        auto iter = std::find_if_not(begin, expression.end(), ::isalnum);
        std::string name(begin, iter);
        begin = iter;
        return name;
    }

    int deal_value(std::string& expression, std::string::iterator& begin) {
        std::size_t pos;
        int result = std::stoi(std::string(begin, expression.end()), &pos);
        begin += pos;
        return result;
    }

private:
    std::map<std::string, std::vector<int>> variables_;
};
