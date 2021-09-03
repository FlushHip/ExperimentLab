class Solution {
public:
    vector<int> smallestK(vector<int>& arr, int k) {
        f(arr.begin(), arr.end(), k);
        return std::vector<int>(arr.begin(), arr.begin() + k);
    }
    void f(std::vector<int>::iterator begin, std::vector<int>::iterator end, int k) {
        if (begin == end) {
            return ;
        }
        auto mid = std::partition(begin, end, [pivot = *begin](const auto em)
        {
            return em < pivot;
        });
        auto num = mid - begin;
        if (num < k) {
            if (!num) {
                f(begin + 1, end, k - 1);
            } else {
                f(mid, end, k - num);
            }
        } else if (num > k) {
            f(begin, mid, k);
        }
    }
};
