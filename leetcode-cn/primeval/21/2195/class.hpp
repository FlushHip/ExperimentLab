class Solution {
public:
    long long minimalKSum(vector<int>& nums, int k) {
        std::set<int> num_set(nums.begin(), nums.end());

        long long ans = 0;
        int pre = 0;
        for (auto it = num_set.begin(); it != num_set.end() && k; pre = *it, ++it) {
            int cnt = std::min(*it - pre - 1, k);
            k -= cnt;
            ans += (pre + 1ll + pre + cnt) * cnt / 2;
        }
        ans += (pre + 1ll + pre + k ) * k / 2;

        return ans;
    }
};
