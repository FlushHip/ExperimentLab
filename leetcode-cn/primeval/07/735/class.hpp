#include "headers.h"

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        std::vector<int> result;
        std::stack<int> stack;
        for (auto asteroid : asteroids) {
            if (asteroid > 0) {
                stack.push(asteroid);
            } else {
                bool f = false;
                while (!stack.empty()) {
                    int top = stack.top();
                    if (top <= -asteroid) {
                        stack.pop();
                        if (top == -asteroid) {
                            f = true;
                            break;
                        }
                    } else {
                        break;
                    }
                }
                if (!f && stack.empty()) {
                    result.push_back(asteroid);
                }
            }
        }
        auto begin = static_cast<int>(result.size());
        while (!stack.empty()) {
            result.push_back(stack.top());
            stack.pop();
        }
        std::reverse(result.begin() + begin, result.end());

        return result;
    }
};
