class Solution {
    enum { MAX_LEN = 100000 + 1};
public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = (int)parents.size();
        std::vector<int>ans(n, 1);
        auto it = std::find(nums.begin(), nums.end(), 1);
        if (it == nums.end()) {
            return ans;
        }
        auto index = it - nums.begin();

        std::vector<std::vector<int>> trees(n);
        for (int i = 1; i < n; ++i) {
            trees[parents[i]].push_back(i);
        }

        std::vector<bool> used(MAX_LEN, false);

        for (int index = (int)(it - nums.begin()), ptr = 1, pre = -1
            ; index != -1; index = parents[index]) {
            for (const auto cld : trees[index]) {
                if (cld == pre) {
                    continue;
                }
                std::queue<int> que;
                que.push(cld);
                while (!que.empty()) {
                    int now = que.front();
                    que.pop();
                    used[nums[now]] = true;
                    for (const auto c : trees[now]) {
                        que.push(c);
                    }
                }
            }
            for (used[nums[index]] = true; used[ptr]; ++ptr) {}
            ans[index] = ptr;
            pre = index;
        }

        return ans;
    }
};
