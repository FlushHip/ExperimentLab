class Solution {
public:
    vector<int> smallestK(vector<int>& arr, int k) {
        std::nth_element(arr.begin(), arr.begin() + k, arr.end());
        return std::vector<int>(arr.begin(), arr.begin() + k);
    }
};
