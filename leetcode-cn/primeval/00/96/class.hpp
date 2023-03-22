#include "headers.h"

class Solution {
public:
    int numTrees(int n) {
        static auto f = [] {
            std::array<int, 20> f{0};
            f[0] = f[1] = 1;
            for (int i = 2; i < 20; ++i) {
                for (int mid = 1; mid <= i; ++mid) {
                    f[i] += f[mid - 1] * f[i - mid];
                }
            }
            return f;
        }();
        return f[n];
    }
};
