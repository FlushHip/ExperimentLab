#include "headers.h"

class Solution {
public:
    int maximumRemovals(string s, string p, vector<int>& removable) {
        int s_length = static_cast<int>(s.size()),
            p_length = static_cast<int>(p.size());
        int n = static_cast<int>(removable.size());
        std::vector<bool> is_remove(s_length, false);
        int lhs = 0, rhs = n;
        while (lhs < rhs) {
            int mid = (lhs + rhs + 1) / 2;
            is_remove.assign(s_length, false);
            for (int i = 0; i < mid; ++i) {
                is_remove[removable[i]] = true;
            }
            int p_index = 0;
            for (int s_index = 0; s_index < s_length && p_index < p_length;
                 ++s_index) {
                if (!is_remove[s_index] && s[s_index] == p[p_index]) {
                    ++p_index;
                }
            }
            if (p_index == p_length) {
                lhs = mid;
            } else {
                rhs = mid - 1;
            }
        }
        return rhs;
    }
};
