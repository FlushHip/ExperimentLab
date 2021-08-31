class Solution {
public:
    Solution(vector<int>& nums) : gen_(std::random_device{}()) {
        for (int i = 0; i < (int)nums.size(); ++i) {
            maps_[nums[i]].push_back(i);
        }
    }

    int pick(int target) {
        std::uniform_int_distribution<int> distrib(0, maps_[target].size() - 1);
        return maps_[target][distrib(gen_)];
    }
private:
    std::unordered_map<int, std::vector<int>> maps_;
    std::mt19937 gen_;
};
