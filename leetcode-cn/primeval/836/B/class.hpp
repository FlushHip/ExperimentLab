// TAG : 区间重叠判断
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return std::max(rec1[0], rec2[0]) < std::min(rec1[2], rec2[2])
            && std::max(rec1[1], rec2[1]) < std::min(rec1[3], rec2[3]);
    }
};
