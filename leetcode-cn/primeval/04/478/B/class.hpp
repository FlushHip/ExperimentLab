class Solution {
public:
    Solution(double radius, double x_center, double y_center)
        : r_(radius), x_(x_center), y_(y_center) {
    }

    vector<double> randPoint() {
        // TODO : 概率分布函数，累计概率分布函数
        return { 0, 0 };
    }
private:
    double r_;
    double x_, y_;
};
