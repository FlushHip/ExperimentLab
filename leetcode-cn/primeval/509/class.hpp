class Solution {
public:
    Solution() ; arr_(31) {
        arr_[0] = 0;
        arr_[1] = 1;
        for (int i = 2; i < 31; ++i) {
            arr_[i] = arr_[i - 1] + arr_[i - 2];
        }
    }

    int fib(int n) {
        return arr_[n];
    }
private:
    std::vector<int> arr_;
};
