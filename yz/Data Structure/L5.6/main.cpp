#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <iomanip>

int main(int argc, char **argv)
{
    std::freopen("in.dat", "r", stdin);

    auto get_prior = [](const char c) -> int
    {
        if (c == '+' || c == '-')
            return 0;
        return 1;
    };

    for (std::string expression; std::getline(std::cin, expression) && expression != "0"; ) {
        expression.push_back(' ');

        std::stack<double> answers;
        std::stack<char> operators;
        int num = 0;
        bool pre = false;
        for (auto i = 0u; i < expression.size(); ++i) {
            if (std::isdigit(expression[i])) {
                num = num * 10 + expression[i] - '0';
                pre = true;
                continue;
            }
            if (pre) {
                answers.push(num);
                num = 0;
            }
            pre = false;

            if (std::isspace(expression[i]))
                continue;
            while (!operators.empty() && get_prior(expression[i]) <= get_prior(operators.top())) {
                auto a = answers.top();
                answers.pop();
                auto b = answers.top();
                answers.pop();
                if (operators.top() == '*') {
                    answers.push(a * b);
                } else if (operators.top() == '/'){
                    answers.push(b / a);
                } else if (operators.top() == '+') {
                    answers.push(a + b);
                } else {
                    answers.push(b - a);
                }
                operators.pop();
            }
            operators.push(expression[i]);
        }
        while (!operators.empty()) {
            auto a = answers.top();
            answers.pop();
            auto b = answers.top();
            answers.pop();
            if (operators.top() == '+') {
                answers.push(a + b);
            } else if (operators.top() == '-') {
                answers.push(b - a);
            } else if (operators.top() == '*') {
                answers.push(a * b);
            } else {
                answers.push(b / a);
            }
            operators.pop();
        }

        std::cout << std::fixed << std::setprecision(2) << answers.top() << std::endl;
    }
    return 0;
}