class Solution {
public:
    Solution() : arr_(38) {
        arr_[0] = 0;
        arr_[1] = arr_[2] = 1;
        for (int i = 3; i < 38; ++i) {
            arr_[i] = arr_[i - 1] + arr_[i - 2] + arr_[i - 3];
        }
    }
    int tribonacci(int n) {
        return arr_[n];
    }
private:
    std::vector<int> arr_;
};
