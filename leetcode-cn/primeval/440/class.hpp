class Solution {
    inline int get_cnt(int len)
    {
        static int NUM[] = {1, 11, 111, 1111, 11111, 111111, 1111111, 11111111, 111111111};
        return NUM[len];
    };

    void dfs(int index, int k, int len, int &ans) {
        if (k == 0) {
            //ans = ans * 10 + index;
            return ;
        }
        int num = (ans == 0), sum = 0, cnt = get_cnt(len);
        for ( --k; num < 10; ++num) {
            if (sum + cnt > k) {
                break;
            } else {
                sum += cnt;
            }
        }
        dfs(num, k - sum, len - 1, ans = ans * 10 + num);
    }
public:
    int findKthNumber(int n, int k) {
        int len = static_cast<int>(std::to_string(n).size()), ans = 0;
        dfs(1, k, len - 1, ans);
        return ans;
    }
};
