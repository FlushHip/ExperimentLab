#include <sstream>
#include <stdexcept>
#include "headers.h"

class Solution {
public:
    bool areNumbersAscending(string s) {
        std::istringstream sin(s);
        std::string word;
        int pre = -1;
        while (sin >> word) {
            try {
                int num = std::stoi(word);
                if (num <= pre) {
                    return false;
                }
                pre = num;
            } catch (std::invalid_argument) {
            }
        }
        return true;
    }
};
