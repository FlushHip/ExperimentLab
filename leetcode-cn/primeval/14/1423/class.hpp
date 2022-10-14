class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = (int)cardPoints.size();
        auto sum = std::accumulate(cardPoints.begin(), std::next(cardPoints.begin(), n - k), 0);
        auto pre = sum, ans = sum;
        for (auto i = (unsigned int)(n - k); i < cardPoints.size(); ++i) {
            int now = sum + cardPoints[i] - cardPoints[i - (n - k)];
            ans = std::min(ans, now);
            sum = now;
        }
        return std::accumulate(cardPoints.begin(), cardPoints.end(), 0) - ans;
    }
};
