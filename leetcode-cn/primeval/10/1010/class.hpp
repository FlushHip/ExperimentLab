#include "headers.h"

class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        std::array<int, 60> line{0};
        for (int num : time) {
            ++line[num % 60];
        }
        int ans = (line[0] / (line[0] % 2 ? 1 : 2) * (line[0] - 1) /
                      (line[0] % 2 ? 2 : 1)) +
            (line[30] / (line[30] % 2 ? 1 : 2) * (line[30] - 1) /
                (line[30] % 2 ? 2 : 1));
        for (int i = 1; i < 30; ++i) {
            ans += line[i] * line[60 - i];
        }
        return ans;
    }
};
