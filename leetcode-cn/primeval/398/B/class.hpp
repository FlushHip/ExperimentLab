class Solution {
public:
    Solution(vector<int>& nums)
        : begin_(nums.begin())
        , end_(nums.end())
        , gen_(std::random_device{}()) {
    }

    int pick(int target) {
        int index = 0, ans = -1;
        for (auto it = begin_; it != end_; ++it) {
            if (*it != target) {
                continue;
            }

            ++index;
            if (index == 1) {
                ans =  it - begin_;
                continue;
            }

            int random_index =
                std::uniform_int_distribution<int>(1, index)(gen_);
            if (random_index == 1) {
                ans = it - begin_;
            }
        }
        return ans;
    }
private:
    std::vector<int>::iterator begin_, end_;
    std::mt19937 gen_;
};
