class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        std::vector<int> ans(n + 1, 0);
        for (const auto & tp : bookings) {
            ans[tp[0]] += tp[2];
            if (tp[1] + 1 <= n) {
                ans[tp[1] + 1] -= tp[2];
            }
        }
        std::partial_sum(ans.begin(), ans.end()
            , ans.begin());
        ans.erase(ans.begin());

        return ans;
    }
};
