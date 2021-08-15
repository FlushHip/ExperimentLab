class Solution {
public:
    int missingNumber(vector<int>& nums) {
        std::vector<int> digits(nums.size() + 1, 0);
        for (const auto item : nums) {
            digits[item] = 1;
        }
        for (int i = 0; i <= (int)digits.size(); ++i) {
            if (!digits[i]) {
                return i;
            }
        }
        return 0;
    }
};
