class Solution {
public:
    long long subArrayRanges(vector<int>& nums) {
        int n = (int)nums.size();
        auto fn = [&nums, n](auto &&op) {
            std::vector<std::pair<int, int>> rangeIndex(n);
            std::stack<int> que;
            for (int i = 0; i < n; ++i) {
                while (!que.empty() && op(nums[que.top()], nums[i])) {
                    auto index = que.top();
                    que.pop();
                    rangeIndex[index].second = i - 1;
                }
                rangeIndex[i].first = que.empty() ? 0 : que.top() + 1;

                que.push(i);
            }
            for (; !que.empty(); que.pop()) {
                rangeIndex[que.top()].second = n - 1;
            }

            return rangeIndex;
        };

        auto minRange = fn(std::greater_equal<int>{});
        auto maxRange = fn(std::less<int>{});

        long long ans = 0ll;
        for (int i = 0; i < n; ++i) {
            ans += (maxRange[i].second - i + 1ll) * (i - maxRange[i].first + 1ll) * nums[i];
            ans -= (minRange[i].second - i + 1ll) * (i - minRange[i].first + 1ll) * nums[i];
        }

        return ans;
    }
};
