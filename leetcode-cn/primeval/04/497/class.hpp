class Solution {
public:
    Solution(vector<vector<int>>& rects)
        : gen_(std::random_device{}())
        , begin_(rects.begin()) {
        std::transform(rects.begin(), rects.end()
            , std::back_inserter(pre_)
            , [this, sum = 0](const auto & rect) mutable
            {
                return sum += calcArea(rect);
            });
        distrib_ = std::make_unique<std::uniform_int_distribution<>>(1, pre_.back());
    }

    vector<int> pick() {
        auto index = std::lower_bound(pre_.begin(), pre_.end(), distrib_->operator()(gen_)) - pre_.begin();
        auto rect = *(begin_ + index);
        std::uniform_int_distribution<> r_x(rect[0], rect[2]);
        std::uniform_int_distribution<> r_y(rect[1], rect[3]);
        return { r_x(gen_), r_y(gen_) };
    }

    inline int calcArea(const std::vector<int> &rect) {
        return (rect[2] - rect[0] + 1) * (rect[3] - rect[1] + 1);
    }

private:
    std::vector<int> pre_;
    std::mt19937 gen_;
    std::unique_ptr<std::uniform_int_distribution<>> distrib_;
    std::vector<std::vector<int>>::iterator begin_;
};
