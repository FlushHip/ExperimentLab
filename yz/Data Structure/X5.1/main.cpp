#include <iostream>
#include <stack>

int main(int argc, char **argv)
{
    for (int n; std::cin >> n; ) {
        std::stack<int> s;
        for (int i = 0; i < n; ++i) {
            std::string str;
            int num = 0;
            std::cin >> str;
            if (str == "P") {
                std::cin >> num;
                s.push(num);
            } else if (str == "O") {
                if (!s.empty())
                    s.pop();
            } else {
                if (s.empty())
                    std::cout << "E";
                else
                    std::cout << s.top();
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}