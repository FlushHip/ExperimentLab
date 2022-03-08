class Solution {
public:
    long long interchangeableRectangles(vector<vector<int>>& rectangles) {
        std::map<std::pair<int, int>, int> mp;
        for (const auto & rectangle : rectangles) {
            int g = std::gcd(rectangle[0], rectangle[1]);
            ++mp[{ rectangle[0] / g, rectangle[1] / g }];
        }

        long long ans = 0ll;
        for (const auto &[_, cnt] : mp) {
            ans += (0ll + cnt) * (cnt - 1) / 2;
        }

        return ans;
    }
};
