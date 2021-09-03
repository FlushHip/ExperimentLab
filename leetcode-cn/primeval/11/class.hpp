class Solution {
public:
    int maxArea(vector<int>& height) {
        int ans = 0;
        for (int l = 0, r = ((int)height.size()) - 1; l != r; ) {
            ans = std::max(ans, (r - l) * std::min(height[l], height[r]));
            if (height[l] < height[r]) {
                ++l;
            } else {
                --r;
            }
        }
        return ans;
    }
};
