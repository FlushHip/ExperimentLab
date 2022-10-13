class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        return std::max_element(nums.begin(), nums.end()) - nums.begin();
    }
};
