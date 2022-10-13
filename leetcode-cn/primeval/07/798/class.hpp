class Solution {
public:
    int bestRotation(vector<int>& nums) {
        int n = (int)nums.size();
        std::vector<int> line(n + 1, 0);

        for (int i = 0; i < n; ++i) {
            int lhs = (i - (n - 1) + n) % n;
            int rhs = (i - nums[i] + n) % n;

            ++line[lhs];
            --line[rhs + 1];
            if (lhs > rhs) {
                ++line[0];
                --line[n];
            }
        }
        int ans = 0, max_ = -1, sum = 0;
        for (int i = 0; i < n; ++i) {
            sum += line[i];
            if (max_ < sum) {
                max_ = sum;
                ans = i;
            }
        }
        return ans;
    }
};
