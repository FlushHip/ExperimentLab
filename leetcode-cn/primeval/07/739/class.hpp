// TAG : 单调栈
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = (int)temperatures.size();
        std::stack<std::pair<int, int>> monotonous_stack;
        std::vector<int> ans(n, 0);
        for (int i = 0; i < n; ++i) {
            while (!monotonous_stack.empty() && monotonous_stack.top().second < temperatures[i]) {
                ans[monotonous_stack.top().first] = i - monotonous_stack.top().first;
                monotonous_stack.pop();
            }
            monotonous_stack.emplace(i, temperatures[i]);
        }

        return ans;
    }
};
