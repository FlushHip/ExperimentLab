class Solution {
public:
    Solution(double radius, double x_center, double y_center)
        : r_(radius), x_(x_center), y_(y_center)
        , distrib_x(x_ - r_, x_ + r_)
        , distrib_y(y_ - r_, y_ + r_)
        , gen_(std::random_device{}()) {
    }

    vector<double> randPoint() {
        std::vector<double> ans{ 0, 0 };
        for ( ; !in(ans[0] = distrib_x(gen_), ans[1] = distrib_y(gen_)); ) {
        }
        return ans;
    }

    inline bool in(double x, double y) {
        double x2 = (x - x_), y2 = (y - y_);
        return x2 * x2 + y2 * y2 <= r_ * r_;
    }
private:
    double r_;
    double x_, y_;

    std::uniform_real_distribution<> distrib_x;
    std::uniform_real_distribution<> distrib_y;
    std::mt19937 gen_;
};
