#include "headers.h"

class Solution {
public:
    bool isIdealPermutation(vector<int>& nums) {
        long long part_num = 0;
        for (int i = 1; i < nums.size(); ++i) {
            part_num += nums[i - 1] > nums[i];
        }
        return part_num == global_num(nums);
    }

private:
    int lowbit(int x) { return x - (x & x - 1); }

    int sum(const std::vector<int>& c, int x) {
        int ret = 0;
        for (; x > 0; x -= lowbit(x)) {
            ret += c[x];
        };
        return ret;
    }

    void update(std::vector<int>& c, int x) {
        for (; x < c.size(); x += lowbit(x)) {
            ++c[x];
        }
    }

    long long global_num(std::vector<int>& nums) {
        std::vector<int> c(nums.size() + 1, 0);
        long long ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            ans += i - sum(c, nums[i] + 1);
            update(c, nums[i] + 1);
        }
        return ans;
    }
};
