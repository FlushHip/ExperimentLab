#include "headers.h"

class Solution {
public:
    string multiply(string num1, string num2) {
        std::reverse(num1.begin(), num1.end());
        std::reverse(num2.begin(), num2.end());
        for (auto& c : num1) {
            c -= '0';
        }
        for (auto& c : num2) {
            c -= '0';
        }
        std::vector<int> arr(num1.size() + num2.size() + 1, 0);
        for (int i = 0; i < num1.size(); ++i) {
            for (int j = 0; j < num2.size(); ++j) {
                int res = num1[i] * num2[j];
                arr[i + j] += res % 10;
                arr[i + j + 1] += res / 10;
            }
        }
        for (int i = 0; i < arr.size() - 1; ++i) {
            arr[i + 1] += arr[i] / 10;
            arr[i] %= 10;
        }
        while (arr.size() > 1U && arr.back() == 0) {
            arr.pop_back();
        }
        std::string ans(arr.begin(), arr.end());
        for (auto& c : ans) {
            c += '0';
        }
        std::reverse(ans.begin(), ans.end());
        return ans;
    }
};
