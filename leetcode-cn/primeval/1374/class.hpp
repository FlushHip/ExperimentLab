#include "headers.h"

class Solution {
public:
    string generateTheString(int n) {
        if ((n % 2) != 0) {
            return std::string(n, 'a');
        }
        return std::string(n - 1, 'a') + "b";
    }
};
