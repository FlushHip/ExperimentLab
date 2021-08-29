class Solution {
public:
    Solution(vector<int>& w) : w_(w), gen_(std::random_device{}()) {
        std::partial_sum(w.begin(), w.end()
            , std::back_inserter(pre_));
        distrib_ = std::make_unique<std::uniform_int_distribution<int>>(1, pre_.back());
    }

    int pickIndex() {
        int num = distrib_->operator()(gen_);
        return std::lower_bound(pre_.begin(), pre_.end(), num) - pre_.begin();
    }

private:
    std::vector<int> w_, pre_;
    std::unique_ptr<std::uniform_int_distribution<int>> distrib_;
    std::mt19937 gen_;
};
