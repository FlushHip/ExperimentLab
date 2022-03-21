class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int lhs = 0, rhs = (int)(numbers.size()) - 1;
        while (lhs < rhs) {
            if (numbers[lhs] + numbers[rhs] == target) {
                return { lhs + 1, rhs + 1 };
            } else if (numbers[lhs] + numbers[rhs] > target) {
                --rhs;
            } else {
                ++lhs;
            }
        }
        return { 0, 0 };
    }
};
