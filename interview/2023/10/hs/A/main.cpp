#include <iostream>
#include <vector>

#include <dbg.h>

int main() {
    for (std::string input; std::cin >> input;) {
        // input.push_back(',');
        std::vector<int> nums;
        for (int begin = 0;;) {
            auto end = input.find(',', begin);
            if (end != std::string::npos) {
                nums.emplace_back(std::stoi(input.substr(begin, end - begin)));
                begin = end + 1;
            } else {
                nums.emplace_back(std::stoi(input.substr(begin)));
                break;
            }
        }
        dbg(nums);

        int n = static_cast<int>(nums.size());
        auto fn = [&](int lhs, int rhs) {
            int ret = 0, min_value = nums[lhs];
            for (int i = lhs + 1; i < rhs; ++i) {
                ret = std::max(ret, nums[i] - min_value);
                min_value = std::min(min_value, nums[i]);
            }
            return ret;
        };

        int ans = 0;
        // 1
        ans = std::max(ans, fn(0, n));
        // 2
        for (int mid = 1; mid < n - 1; ++mid) {
            ans = std::max(ans, fn(0, mid) + fn(mid, n));
        }
        // 3
        for (int mid1 = 1; mid1 < n - 2; ++mid1) {
            for (int mid2 = mid1 + 1; mid2 < n - 1; ++mid2) {
                ans = std::max(ans, fn(0, mid1) + fn(mid1, mid2) + fn(mid2, n));
            }
        }
        std::cout << ans << std::endl;
    }
    return 0;
}
