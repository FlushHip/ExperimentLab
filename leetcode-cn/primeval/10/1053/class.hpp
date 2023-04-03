#include "headers.h"

class Solution {
public:
    vector<int> prevPermOpt1(vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        int pos = n - 2;
        for (; pos >= 0 && arr[pos] <= arr[pos + 1]; --pos) {
        }
        if (pos < 0) {
            return arr;
        }
        int last = n - 1;
        for (; last > pos && arr[last] >= arr[pos]; --last) {
        }
        for (; last - 1 > pos && arr[last] == arr[last - 1]; --last) {
        }
        std::swap(arr[pos], arr[last]);
        return arr;
    }
};
