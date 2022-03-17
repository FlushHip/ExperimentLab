class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        int n = (int)arr.size();
        std::queue<int> que({ start });
        std::vector<bool> used(n, false);
        used[start] = true;
        for (; !que.empty(); ) {
            auto now = que.front();
            que.pop();

            if (!arr[now]) {
                return true;
            }

            if (now + arr[now] < n && !used[now + arr[now]]) {
                used[now + arr[now]] = true;
                que.push(now + arr[now]);
            }
            if (now - arr[now] >= 0 && !used[now - arr[now]]) {
                used[now - arr[now]] = true;
                que.push(now - arr[now]);
            }
        }
        return false;
    }
};
