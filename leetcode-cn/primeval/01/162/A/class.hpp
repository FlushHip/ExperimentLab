class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = (int)nums.size(), ans = -1;
        std::vector<long long> nu;
        nu.push_back(std::numeric_limits<long long>::min());
        for (const auto e : nums) {
            nu.push_back(e);
        }
        nu.push_back(std::numeric_limits<long long>::min());
        for (int i = 1; i < n + 1; ++i) {
            if ((nu[i] > nu[i - 1] && nu[i] > nu[i + 1])) {
                ans = i - 1;
                break;
            }
        }
        return ans;
    }
};
