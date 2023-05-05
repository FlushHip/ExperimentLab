#include "headers.h"

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        std::unordered_map<int, int> ump;
        for (int num : nums) {
            ++ump[num];
        }
        std::vector<std::pair<int, int>> line;
        for (auto&& [num, cnt] : ump) {
            line.emplace_back(cnt, num);
        }
        dfs(line.begin(), line.end(), k);
        std::vector<int> ans;
        for (int i = 0; i < k; ++i) {
            ans.emplace_back(line[i].second);
        }
        return ans;
    }

private:
    template <typename Iter>
    void dfs(Iter begin, Iter end, int k) {
        if (begin == end || k == 0) {
            return;
        }
        auto pivot = std::next(begin, std::distance(begin, end) / 2)->first;
        auto mid1 = std::partition(
            begin, end, [pivot](auto& pr) { return pr.first > pivot; });
        std::partition(
            mid1, end, [pivot](auto& pr) { return !(pr.first < pivot); });
        if (mid1 - begin > k - 1) {
            dfs(begin, mid1, k);
        } else if (mid1 - begin < k - 1) {
            dfs(std::next(mid1), end, k - (int)(mid1 - begin) - 1);
        }
    }
};
