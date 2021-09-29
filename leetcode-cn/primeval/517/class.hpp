class Solution {
public:
    int findMinMoves(vector<int>& machines) {
        int sum = std::accumulate(machines.begin(), machines.end(), 0)
            , n = machines.size();
        if (sum % n) {
            return -1;
        }
        int e = sum / n, res = 0, ans = -1;
        for (int i = 0; i < n; ++i) {
            int d = machines[i] - e;
            res += d;
            ans = std::max(ans, std::max(std::abs(res), d));
        }
        return ans;
    }
};
