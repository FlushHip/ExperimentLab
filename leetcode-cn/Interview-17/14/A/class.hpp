class Solution {
public:
    vector<int> smallestK(vector<int>& arr, int k) {
        std::sort(arr.begin(), arr.end());
        return std::vector<int>(arr.begin(), arr.begin() + k);
    }
};
