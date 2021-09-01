class Solution {
public:
    Solution(int n, vector<int>& blacklist)
        : n_(n)
        , gen_(std::random_device{}()) {
        std::sort(blacklist.begin(), blacklist.end());
        for (; !blacklist.empty() && blacklist.back() >= n
            ; blacklist.pop_back()) {
        }
        begin_ = blacklist.begin();
        end_ = blacklist.end();
    }

    int pick() {
        int res = std::uniform_int_distribution<>(1, n_ - (end_ - begin_))(gen_);
        int ans = 0;
        // TODO : 二分查找替代顺序查找

        if (res) {
            ans += res - 1;
        }
        return ans;
    }
private:
    int n_;
    std::vector<int>::iterator begin_, end_;
    std::mt19937 gen_;
};
