class Solution {
public:
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int ans = (ax2 - ax1) * (ay2 - ay1) + (bx2 - bx1) * (by2 - by1);
        int resX = std::min(ax2, bx2) - std::max(ax1, bx1);
        int resY = std::min(ay2, by2) - std::max(ay1, by1);
        if (resX < 0 || resY < 0) {
            return ans;
        }
        return ans - resX * resY;
    }
};
